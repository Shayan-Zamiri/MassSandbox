/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
* You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "MSMovementTrait.h"

#include "MassCommonFragments.h"
#include "MassEntityTemplateRegistry.h"
#include "MassSandbox/Fragments/MSMovementFragments.h"
#include "MassSandbox/Subsystems/MSSubsystem.h"

void UMSMovementTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	BuildContext.AddTag<FMSMoverTag>();
	BuildContext.AddFragment<FTransformFragment>();

	const FConstSharedStruct MovementParamsFragment = World.GetSubsystem<UMSSubsystem>()->EntitySystem->GetOrCreateConstSharedFragment(
		UE::StructUtils::GetStructCrc32(FConstStructView::Make(MovementParams)), MovementParams);
	BuildContext.AddConstSharedFragment(MovementParamsFragment);
}
