/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
* You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "Processors/MEModifyHealthInitializer.h"
#include "Fragments/MEHealthFragments.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UMEModifyHealthInitializer::UMEModifyHealthInitializer()
{
	ObservedType = FMEModifyHealthFragment::StaticStruct();
	Operation = EMassObservedOperation::Add;
}

void UMEModifyHealthInitializer::ConfigureQueries()
{
	EntityQuery.AddRequirement<FMEModifyHealthFragment>(EMassFragmentAccess::ReadWrite);
}

void UMEModifyHealthInitializer::Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk(EntitySubsystem, Context, [this](FMassExecutionContext& Context)
	{
		const TArrayView<FMEModifyHealthFragment> HealthModifierList = Context.GetMutableFragmentView<FMEModifyHealthFragment>();
		for (FMEModifyHealthFragment& HealthModifier : HealthModifierList)
		{
			HealthModifier.Amount = 0.0f;
			HealthModifier.Time = 0;
			HealthModifier.Timer = 1.0f;
		}
	});
}
