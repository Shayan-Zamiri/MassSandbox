/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CoreMinimal.h"
#include "Fragments/MEHealthFragments.h"
#include "MassSpawner/Public/MassEntityTraitBase.h"
#include "MEHealthTrait.generated.h"

UCLASS(ClassGroup= "Mass Extender", DisplayName= "ME Health Trait")
class MASSEXTENDER_API UMEHealthTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

public:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const override;

	UPROPERTY(EditAnywhere)
	FMEHealthParamsFragment HealthParams;

	UPROPERTY(EditAnywhere)
	float Damage = -10.0f;
};
