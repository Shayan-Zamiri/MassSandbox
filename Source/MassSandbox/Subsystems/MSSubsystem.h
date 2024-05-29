/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CoreMinimal.h"
#include "MassArchetypeTypes.h"
#include "MSSubsystem.generated.h"

class UMassEntitySubsystem;

UCLASS()
class MASSSANDBOX_API UMSSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// FUNCTIONS
private:
	UFUNCTION(BlueprintCallable)
	int32 SpawnEntity();
	
	// PROPERTIES
public:
	UPROPERTY(Transient)
	UMassEntitySubsystem* EntitySystem;
	
	FMassArchetypeHandle MoverArchetype;
};
