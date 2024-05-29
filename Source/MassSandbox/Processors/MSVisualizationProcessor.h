/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CoreMinimal.h"
#include "MassRepresentation/Public/MassRepresentationProcessor.h"
#include "MSVisualizationProcessor.generated.h"

UCLASS()
class MASSSANDBOX_API UMSVisualizationProcessor : public UMassVisualizationProcessor
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UMSVisualizationProcessor();
};
