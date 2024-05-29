/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "MassEntityTypes.h"
#include "MEUnitFragments.generated.h"

// FRAGMENTS

// SHARED FRAGMENTS

USTRUCT()
struct MASSEXTENDER_API FMEUnitsGroupInfoSharedFragment : public FMassSharedFragment
{
	GENERATED_BODY()

	FMEUnitsGroupInfoSharedFragment() : XGap(0.0f), YGap(0.0f), UnitsNum(1), Width(1), Height(1)
	{
	}

	UPROPERTY(EditAnywhere)
	float XGap; // X-Distance between units in group

	UPROPERTY(EditAnywhere)
	float YGap; // Y-Distance between units in group

	UPROPERTY(EditAnywhere)
	int32 UnitsNum; // Number of units in group

	UPROPERTY(EditAnywhere)
	int32 Width; // Number of units along square's width

	UPROPERTY(EditAnywhere)
	int32 Height; // Number of units along square's height

	UPROPERTY(EditAnywhere)
	FVector Center; // Center's location of a unit group
};

// TAGS
