/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "Traits/MEMovementTrait.h"
#include "MassCommonFragments.h"
#include "MassEntityTemplateRegistry.h"
#include "MassMovementFragments.h"
#include "Fragments/MEMovementFragments.h"

void UMEMovementTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	BuildContext.AddFragment<FTransformFragment>();
	BuildContext.AddFragment<FMassVelocityFragment>();
	BuildContext.AddFragment<FMETargetLocationFragment>();

	const uint32 MovementParamsHash = UE::StructUtils::GetStructCrc32(FConstStructView::Make(MovementParams));
	const FSharedStruct MovementParamsFragment = World.GetSubsystem<UMassEntitySubsystem>()->GetOrCreateSharedFragment<
		FMEMovementParamsSharedFragment>(MovementParamsHash, MovementParams);
	BuildContext.AddSharedFragment(MovementParamsFragment);

	const uint32 UnitsGroupInfoHash = UE::StructUtils::GetStructCrc32(FConstStructView::Make(UnitsGroupInfo));
	const FSharedStruct UnitsGroupInfoFragment = World.GetSubsystem<UMassEntitySubsystem>()->GetOrCreateSharedFragment<
		FMEUnitsGroupInfoSharedFragment>(UnitsGroupInfoHash, UnitsGroupInfo);
	BuildContext.AddSharedFragment(UnitsGroupInfoFragment);
}
