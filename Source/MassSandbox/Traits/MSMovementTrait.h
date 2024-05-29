/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "MassSandbox/Fragments/MSMovementFragments.h"
#include "MSMovementTrait.generated.h"

UCLASS()
class MASSSANDBOX_API UMSMovementTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const override;

	UPROPERTY(EditAnywhere)
	FMSMovementParams MovementParams;
};
