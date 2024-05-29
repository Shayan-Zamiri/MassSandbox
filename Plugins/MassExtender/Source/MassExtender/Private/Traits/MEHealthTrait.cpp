/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
* You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "Traits/MEHealthTrait.h"
#include "Fragments/MEHealthFragments.h"
#include "MassSpawner/Public/MassEntityTemplateRegistry.h"

void UMEHealthTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{

	const FMEHealthParamsFragment HealthParamsValidated = HealthParams.GetValidated();
	const uint32 HealthParamsHash = UE::StructUtils::GetStructCrc32(FConstStructView::Make(HealthParamsValidated));
	const FConstSharedStruct HealthParamsFragment = World.GetSubsystem<UMassEntitySubsystem>()->GetOrCreateConstSharedFragment(
		HealthParamsHash, HealthParamsValidated);
	BuildContext.AddConstSharedFragment(HealthParamsFragment);

	BuildContext.AddFragment_GetRef<FMEHealthFragment>().Health = HealthParams.MaxHealth;
	BuildContext.AddFragment_GetRef<FMEModifyHealthFragment>().Amount = 0.0f;
	BuildContext.AddFragment_GetRef<FMEModifyHealthFragment>().Time = 0;
	BuildContext.AddFragment_GetRef<FMEModifyHealthFragment>().Timer = 1.0f;
}
