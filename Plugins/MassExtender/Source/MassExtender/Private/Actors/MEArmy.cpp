/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "Actors/MEArmy.h"
#include "MassCommonFragments.h"
#include "MassEntityConfigAsset.h"
#include "MassEntityTemplate.h"
#include "MassEntityView.h"
#include "MassSpawnerSubsystem.h"
#include "Fragments/MEHashGridFragments.h"
#include "Fragments/MEMovementFragments.h"
#include "Fragments/MEUnitFragments.h"
#include "Subsystems/MESubsystem.h"
#include "Traits/MEVisualizationTrait.h"

AMEArmy::AMEArmy()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMEArmy::BeginPlay()
{
	SCOPE_LOG_TIME_FUNC();

	Super::BeginPlay();

	EntitySubsystem = GetWorld()->GetSubsystem<UMassEntitySubsystem>();
	UMESubsystem* MESubsystem = GetWorld()->GetSubsystem<UMESubsystem>();

	UMassEntityConfigAsset* LoadedEntityConfigAsset = EntityConfigAsset.LoadSynchronous();
	if (LoadedEntityConfigAsset)
	{
		EntityConfig = &LoadedEntityConfigAsset->GetMutableConfig();
		const FMassEntityTemplate* EntityTemplate = EntityConfig->GetOrCreateEntityTemplate(*this, *EntityConfigAsset);
		check(EntityTemplate);
		UMassSpawnerSubsystem* MassSpawnerSubsystem = GetWorld()->GetSubsystem<UMassSpawnerSubsystem>();
		check(MassSpawnerSubsystem);
		MassSpawnerSubsystem->SpawnEntities(*EntityTemplate, UnitsNum, Entities);

		FMEHashGridSharedFragment& HashGridSharedFragment = FMassEntityView(*EntitySubsystem, Entities.Last()).GetSharedFragmentData<
			FMEHashGridSharedFragment>();

		FMEUnitsGroupInfoSharedFragment& UnitsGroupInfo = FMassEntityView(*EntitySubsystem, Entities.Last()).GetSharedFragmentData<
			FMEUnitsGroupInfoSharedFragment>();

		const int32 Width = FMath::Sqrt(static_cast<float>(UnitsNum));
		UnitsGroupInfo.Width = Width;
		UnitsGroupInfo.Height = Width;
		UnitsGroupInfo.XGap = XGap;
		UnitsGroupInfo.YGap = YGap;

		int Row = 0;
		for (const auto& It : Entities)
		{
			FTransformFragment& TransformFragment = FMassEntityView(*EntitySubsystem, It).GetFragmentData<
				FTransformFragment>();

			FVector Location = GetActorLocation() - FVector{((Width - 1) * XGap) / 2, ((Width - 1) * YGap) / 2, 0.0f};
			const int32 Index = It.Index - 1;
			if (Index % Width == 0)
				Row++;
			FBox Space{Location,Location + FVector{10000.0f, 10000.0f, 0.0f}};
			Location = FMath::RandPointInBox(Space);
			TransformFragment.GetMutableTransform().SetLocation(Location);
			HashGridSharedFragment.HashGrid.InsertValue(It, Location);
		}

		// TODO: Get traits, problem is entity config returns copy of traits?

		EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite, EMassFragmentPresence::All);
		EntityQuery.AddRequirement<FMETargetLocationFragment>(EMassFragmentAccess::ReadOnly, EMassFragmentPresence::All);
		EntityQuery.AddSharedRequirement<FMEUnitsGroupInfoSharedFragment>(EMassFragmentAccess::ReadOnly, EMassFragmentPresence::All);
		EntityQuery.AddSharedRequirement<FMEMovementParamsSharedFragment>(EMassFragmentAccess::ReadOnly, EMassFragmentPresence::All);
	}
}

void AMEArmy::SetArmyCenter(FVector Location)
{
	FMEUnitsGroupInfoSharedFragment& UnitsGroupInfoSharedFragment = FMassEntityView(*EntitySubsystem, Entities.Last()).GetSharedFragmentData
	<
		FMEUnitsGroupInfoSharedFragment>();

	UnitsGroupInfoSharedFragment.Center = Location;
}

void AMEArmy::ShouldMoveToLocation(bool bShouldMoveToLocation)
{
	if (bShouldMoveToLocation)
	{
		for (int32 i = 0; i < Entities.Num(); i++)
		{
			EntitySubsystem->AddTagToEntity(Entities[i], FMEMoveToLocationTag::StaticStruct());
		}
	}
	else
	{
		for (int32 i = 0; i < Entities.Num(); i++)
		{
			EntitySubsystem->RemoveTagFromEntity(Entities[i], FMEMoveToLocationTag::StaticStruct());
		}
	}
}
