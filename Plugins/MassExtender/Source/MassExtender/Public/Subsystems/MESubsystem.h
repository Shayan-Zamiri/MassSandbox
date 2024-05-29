/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CoreMinimal.h"
#include "MassEntityConfigAsset.h"
#include "MESubsystem.generated.h"

class UMassSpawnerSubsystem;
class UMassEntitySubsystem;
class UMEDeveloperSettings;

UCLASS()
class MASSEXTENDER_API UMESubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// FUNCTIONS
public:
	UFUNCTION(BlueprintCallable, Category= "Functions")
	void GetEntitiesInsideRect(TMap<int32, int32>& OutEntities, FVector Point1, FVector Point2);
	
	FMassEntityHandle CreateEntity(FName ConfigName, AActor* Owner);
	
	TArray<FMassEntityHandle> CreateEntities(FName ConfigName, AActor* Owner, int32 Num);

	UFUNCTION(BlueprintCallable, Category= "Functions")
	bool SpawnEntity(FName ConfigName, AActor* Owner, FVector Location);

	UFUNCTION(BlueprintCallable, Category= "Functions")
	bool SpawnEntities(FName ConfigName, AActor* Owner, int32 Num, TArray<FVector> Locations);

	void UpdateConfigs();

private:
	const FMassEntityTemplate* UMESubsystem::GetOrCreateEntityTemplate(FName ConfigName, AActor& Owner);

	// PROPERTIES
public:
	UPROPERTY(Transient)
	UMassEntitySubsystem* EntitySubsystem;

	UPROPERTY(Transient)
	UMassSpawnerSubsystem* EntitySpawnerSubsystem;

	UPROPERTY()
	TObjectPtr<UMEDeveloperSettings> DevSettings;

	UPROPERTY()
	TMap<FName, FMassEntityConfig> EntityConfigs;

	UPROPERTY()
	TMap<FName, TObjectPtr<UMassEntityConfigAsset>> EntityConfigAssets;

	TMap<FName, TArray<FMassEntityHandle>> Entities;

private:
	FMassExecutionContext ExecutionContext;

	FMassEntityQuery EntitiesInsideRectQuery;
};
