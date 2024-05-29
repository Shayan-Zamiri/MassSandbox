/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
* You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "MSSubsystem.h"
#include "MassCommonFragments.h"
#include "MassEntitySubsystem.h"
#include "MassMovementFragments.h"
#include "MassRepresentationFragments.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

void UMSSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	const UWorld* World = GetWorld();
	EntitySystem = World->GetSubsystem<UMassEntitySubsystem>();

	MoverArchetype = EntitySystem->CreateArchetype(
		{
			FTransformFragment::StaticStruct(),
			FMassVelocityFragment::StaticStruct(),
			FMassRepresentationFragment::StaticStruct()
		}
	);
}

// FUNCTIONS

int32 UMSSubsystem::SpawnEntity()
{
	// Create and store a handle to our new entity
	FMassEntityHandle NewEntity = EntitySystem->CreateEntity(MoverArchetype);
	
	// How about changing data on a fragment?
	EntitySystem->GetFragmentDataChecked<FMassVelocityFragment>(NewEntity).Value = FMath::VRand() * 100.0f;
	
	return NewEntity.Index;
}
