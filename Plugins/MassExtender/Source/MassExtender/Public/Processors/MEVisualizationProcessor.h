/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CoreMinimal.h"
#include "MassRepresentationProcessor.h"
#include "MEVisualizationProcessor.generated.h"

UCLASS(ClassGroup= "MassExtender")
class MASSEXTENDER_API UMEVisualizationProcessor : public UMassVisualizationProcessor
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UMEVisualizationProcessor();
};
