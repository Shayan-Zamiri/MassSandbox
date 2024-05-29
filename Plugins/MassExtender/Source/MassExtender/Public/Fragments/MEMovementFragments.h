/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "MassEntityTypes.h"
#include "MEMovementFragments.generated.h"

// FRAGMENTS

USTRUCT()
struct MASSEXTENDER_API FMETargetLocationFragment : public FMassFragment
{
	GENERATED_BODY()

	bool bIsLocationSet;
	FVector Location;
};

// SHARED FRAGMENTS

USTRUCT()
struct MASSEXTENDER_API FMEMovementParamsSharedFragment : public FMassSharedFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Speed;
};

// TAGS

USTRUCT()
struct MASSEXTENDER_API FMEMoveToLocationTag : public FMassTag
{
	GENERATED_BODY()
};
