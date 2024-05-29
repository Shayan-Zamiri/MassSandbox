/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CoreMinimal.h"
#include "MassVisualizationTrait.h"
#include "MEVisualizationTrait.generated.h"

UCLASS(ClassGroup= "MassExtender", DisplayName= "ME Visualization Trait")
class MASSEXTENDER_API UMEVisualizationTrait : public UMassVisualizationTrait
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UMEVisualizationTrait();

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const override;
};
