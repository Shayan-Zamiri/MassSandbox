/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "MassEntityTypes.h"
#include "MEHealthFragments.generated.h"

// FRAGMENTS

USTRUCT()
struct MASSEXTENDER_API FMEHealthFragment : public FMassFragment
{
	GENERATED_BODY()

	float Health;
};

/*
 * Applying damage or healing
 */
USTRUCT()
struct MASSEXTENDER_API FMEModifyHealthFragment : public FMassFragment
{
	GENERATED_BODY()
	
	float Amount; // ex: -5.0f, 60.0f
	float Timer; // Goes from 1.0f to 0.0f, -1.0f means instant damage
	int32 Time; // Time in seconds
};

// SHARED FRAGMENTS

USTRUCT()
struct MASSEXTENDER_API FMEHealthParamsFragment : public FMassSharedFragment
{
	GENERATED_BODY()

	FMEHealthParamsFragment GetValidated() const
	{
		const FMEHealthParamsFragment Copy = *this;
		return Copy;
	}
	
	UPROPERTY(EditAnywhere)
	float MaxHealth;
};

// TAGS

USTRUCT()
struct MASSEXTENDER_API FMEShouldModifyHealthTag : public FMassTag
{
	GENERATED_BODY()
};