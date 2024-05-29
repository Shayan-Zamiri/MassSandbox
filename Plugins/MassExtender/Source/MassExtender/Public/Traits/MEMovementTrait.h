/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "Fragments/MEMovementFragments.h"
#include "Fragments/MEUnitFragments.h"
#include "MEMovementTrait.generated.h"

UCLASS(ClassGroup= "Mass Extender", DisplayName= "ME Movement Trait")
class MASSEXTENDER_API UMEMovementTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

public:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const override;

	UPROPERTY(EditAnywhere)
	FMEMovementParamsSharedFragment MovementParams;

	UPROPERTY(EditAnywhere)
	FMEUnitsGroupInfoSharedFragment UnitsGroupInfo;
};