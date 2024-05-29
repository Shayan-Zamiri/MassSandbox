/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "MassEntityTraitBase.h"
#include "MEAssortedTags.generated.h"

UCLASS(ClassGroup= "Mass Extender", DisplayName= "ME Assorted Tags")
class MASSEXTENDER_API UMEAssortedTags : public UMassEntityTraitBase
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const override;

	// PROPERTIES
public:
	UPROPERTY(EditAnywhere, meta = (BaseStruct = "MassTag", ExcludeBaseStruct))
	TArray<FInstancedStruct> Tags;
};
