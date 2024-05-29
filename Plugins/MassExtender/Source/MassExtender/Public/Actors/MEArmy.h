/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CoreMinimal.h"
#include "MassEntityConfigAsset.h"
#include "GameFramework/Actor.h"
#include "MassEntityQuery.h"
#include "Spatial/PointHashGrid3.h"
#include "Traits/MEMovementTrait.h"
#include "MEArmy.generated.h"

class UMEVisualizationTrait;
class UMassEntityConfigAsset;

UCLASS(ClassGroup= "MassExtender")
class MASSEXTENDER_API AMEArmy : public AActor
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AMEArmy();

protected:
	virtual void BeginPlay() override;

	// FUNCTIONS
public:
	UFUNCTION(BlueprintCallable, Category= "Functions")
	void SetArmyCenter(FVector Location);

	UFUNCTION(BlueprintCallable, Category= "Functions")
	void ShouldMoveToLocation(bool bShouldMoveToLocation);

private:
	void UpdateHashGrid();

	// PROPERTIES
public:
	UPROPERTY(EditAnywhere, Category= "Properties")
	int32 UnitsNum;
	
	UPROPERTY(EditAnywhere, Category= "Properties")
	float XGap;

	UPROPERTY(EditAnywhere, Category= "Properties")
	float YGap;

protected:
	UPROPERTY(EditAnywhere, Category= "Properties|Mass")
	TSoftObjectPtr<UMassEntityConfigAsset> EntityConfigAsset;

private:
	UPROPERTY()
	TObjectPtr<UMassEntitySubsystem> EntitySubsystem;

	TObjectPtr<FMassEntityConfig> EntityConfig;

	UPROPERTY()
	TArray<FMassEntityHandle> Entities;

	FMassEntityQuery EntityQuery;
};
