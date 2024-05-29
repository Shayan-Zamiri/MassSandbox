/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "Subsystems/MESubsystem.h"
#include "MassActorSubsystem.h"
#include "MassCommonFragments.h"
#include "MassEntitySubsystem.h"
#include "MassEntityView.h"
#include "MassSpawnerSubsystem.h"
#include "Settings/MEDeveloperSettings.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

void UMESubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	const UWorld* World = GetWorld();
	EntitySubsystem = World->GetSubsystem<UMassEntitySubsystem>();
	EntitySpawnerSubsystem = World->GetSubsystem<UMassSpawnerSubsystem>();
	DevSettings = GetMutableDefault<UMEDeveloperSettings>();

	UpdateConfigs();

	ExecutionContext = FMassExecutionContext{0};
	EntitiesInsideRectQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly, EMassFragmentPresence::All);
}

void UMESubsystem::GetEntitiesInsideRect(TMap<int32, int32>& OutEntities, FVector Point1, FVector Point2)
{
	FBox Box{Point1, Point2};

	EntitiesInsideRectQuery.ForEachEntityChunk
	(*EntitySubsystem, ExecutionContext, [this,&Point1,&Point2,&OutEntities](FMassExecutionContext& Context)
	{
		const TConstArrayView<FTransformFragment>& TransformList = Context.GetFragmentView<
			FTransformFragment>();

		for (int32 i = 0; i < Context.GetNumEntities(); i++)
		{
			const FVector& EntityLocation = TransformList[i].GetTransform().GetLocation();
			if (/*TODO */ false)
				OutEntities.Add(Context.GetEntity(i).Index, Context.GetEntity(i).SerialNumber);
		}
	});
}

// FUNCTIONS

FMassEntityHandle UMESubsystem::CreateEntity(FName ConfigName, AActor* Owner)
{
	check(Owner);
	const FMassEntityTemplate* EntityTemplate = GetOrCreateEntityTemplate(ConfigName, *Owner);
	if (!EntityTemplate)
		return FMassEntityHandle{};

	const FMassEntityHandle CreatedEntity = EntitySubsystem->CreateEntity(EntityTemplate->GetArchetype());
	TArray<FMassEntityHandle>& ReturnedEntities = Entities.FindOrAdd(ConfigName);
	ReturnedEntities.Add(CreatedEntity);
	return CreatedEntity;
}

TArray<FMassEntityHandle> UMESubsystem::CreateEntities(FName ConfigName, AActor* Owner, int32 Num)
{
	check(Owner);
	const FMassEntityTemplate* EntityTemplate = GetOrCreateEntityTemplate(ConfigName, *Owner);
	if (!EntityTemplate)
		return TArray<FMassEntityHandle>{};

	TArray<FMassEntityHandle> CreatedEntities;
	EntitySubsystem->BatchCreateEntities(EntityTemplate->GetArchetype(), Num, CreatedEntities);
	TArray<FMassEntityHandle>& ReturnedEntities = Entities.FindOrAdd(ConfigName);
	ReturnedEntities.Append(CreatedEntities);
	return CreatedEntities;
}

bool UMESubsystem::SpawnEntity(FName ConfigName, AActor* Owner, FVector Location)
{
	check(Owner);
	const FMassEntityTemplate* EntityTemplate = GetOrCreateEntityTemplate(ConfigName, *Owner);
	if (!EntityTemplate || !EntityTemplate->HasFragment(*FTransformFragment::StaticStruct()))
		return false;
	TArray<FMassEntityHandle> CreatedEntities;
	EntitySpawnerSubsystem->SpawnEntities(*EntityTemplate, 1, CreatedEntities);
	FMassEntityView{*EntitySubsystem, CreatedEntities.Last()}.GetFragmentData<FTransformFragment>().GetMutableTransform().
	                                                          SetLocation(Location);
	TArray<FMassEntityHandle>& EntityHandles = Entities.FindOrAdd(ConfigName);
	EntityHandles.Add(CreatedEntities.Last());

	return true;
}

bool UMESubsystem::SpawnEntities(FName ConfigName, AActor* Owner, int32 Num, TArray<FVector> Locations)
{
	check(Owner);
	const FMassEntityTemplate* EntityTemplate = GetOrCreateEntityTemplate(ConfigName, *Owner);
	if (!EntityTemplate)
		return false;

	TArray<FMassEntityHandle> CreatedEntities;
	EntitySpawnerSubsystem->SpawnEntities(*EntityTemplate, Num, CreatedEntities);

	TArray<FMassEntityHandle>& EntityHandles = Entities.FindOrAdd(ConfigName);
	for (const auto& It : CreatedEntities)
	{
		EntityHandles.Add(It);

		FVector Location{};
		if (!Locations.IsEmpty())
			Location = Locations.Pop();

		FMassEntityView{*EntitySubsystem, It}.GetFragmentData<FTransformFragment>().GetMutableTransform().SetLocation(Location);
	}

	return true;
}

void UMESubsystem::UpdateConfigs()
{
	EntityConfigAssets.Empty();
	EntityConfigs.Empty();

	for (const auto& It : DevSettings->MassEntityConfigAssets)
	{
		UMassEntityConfigAsset* LoadedEntityConfigAsset = It.Value.LoadSynchronous();
		check(LoadedEntityConfigAsset);
		FMassEntityConfig& EntityConfig = LoadedEntityConfigAsset->GetMutableConfig();
		EntityConfigs.Add(It.Key, EntityConfig);
		EntityConfigAssets.Add(It.Key, LoadedEntityConfigAsset);
	}
}

const FMassEntityTemplate* UMESubsystem::GetOrCreateEntityTemplate(FName ConfigName, AActor& Owner)
{
	const FMassEntityConfig* EntityConfig = EntityConfigs.Find(ConfigName);
	if (!EntityConfig)
		return nullptr;
	return EntityConfig->GetOrCreateEntityTemplate(Owner, *EntityConfigAssets.Find(ConfigName)->Get());
}
