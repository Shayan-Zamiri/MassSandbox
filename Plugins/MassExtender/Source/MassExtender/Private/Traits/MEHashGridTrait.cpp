/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "Traits/MEHashGridTrait.h"
#include "MassCommonFragments.h"
#include "MassEntityTemplateRegistry.h"
#include "MassMovementFragments.h"

void UMEHashGridTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	BuildContext.AddFragment<FTransformFragment>();
	BuildContext.AddFragment<FMassVelocityFragment>();

	const uint32 HashGridHash = UE::StructUtils::GetStructCrc32(FConstStructView::Make(HashGrid));
	const FSharedStruct HashGridSharedFragment = World.GetSubsystem<UMassEntitySubsystem>()->GetOrCreateSharedFragment<
		FMEHashGridSharedFragment>(HashGridHash, HashGrid);
	FMEHashGridSharedFragment& HashGridSharedFragmentRef = HashGridSharedFragment.GetMutable<FMEHashGridSharedFragment>();
	HashGridSharedFragmentRef.HashGrid = FMEHashGrid{
		HashGridSharedFragmentRef.CellSize, HashGridSharedFragmentRef.Collision, World.GetSubsystem<UMassEntitySubsystem>()
	};
	BuildContext.AddSharedFragment(HashGridSharedFragment);
}
