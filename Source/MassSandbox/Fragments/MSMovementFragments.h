/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "MSMovementFragments.generated.h"

// FRAGMENTS

USTRUCT()
struct MASSSANDBOX_API FMSLocationFragment : public FMassFragment
{
	GENERATED_BODY()

	FVector Location{FVector::ZeroVector};
};

USTRUCT()
struct MASSSANDBOX_API FMSVelocityFragment : public FMassFragment
{
	GENERATED_BODY()

	FVector Velocity = FVector{1.0f, 0.0f, 0.0f};
};

// SHARED FRAGMENTS

USTRUCT()
struct MASSSANDBOX_API FMSMovementParams : public FMassSharedFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Speed = 10.0f;
};

// TAGS

USTRUCT()
struct MASSSANDBOX_API FMSMoverTag : public FMassTag
{
	GENERATED_BODY()
};