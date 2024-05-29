/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "MEHealthModifierProcessor.generated.h"

UCLASS(ClassGroup= "MassExtenderProcessor")
class MASSEXTENDER_API UMEHealthModifierProcessor : public UMassProcessor
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UMEHealthModifierProcessor();
protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context) override;

	// PROPERTIES
private:
	FMassEntityQuery EntityQuery;
};
