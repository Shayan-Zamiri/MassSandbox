/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "MassEntityTypes.h"
#include "METypes.h"
#include "MEHashGridFragments.generated.h"

// FRAGMENTS

// SHARED FRAGMENTS

USTRUCT()
struct MASSEXTENDER_API FMEHashGridSharedFragment : public FMassSharedFragment
{
	GENERATED_BODY()

	FMEHashGridSharedFragment()
		: CellSize{0.0f},
		  Collision(FVector::ZeroVector, FVector{50.0f, 50.0f, 50.0f}),
		  HashGrid(0.0f, FBox{}, nullptr)
	{
	}

	UPROPERTY(EditAnywhere)
	double CellSize;

	UPROPERTY(EditAnywhere)
	FBox Collision;

	FMEHashGrid HashGrid;
};

// TAGS
