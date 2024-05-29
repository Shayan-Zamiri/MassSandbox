/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "Processors/MEHealthModifierProcessor.h"
#include "METypes.h"
#include "MassCommonTypes.h"
#include "Fragments/MEHealthFragments.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UMEHealthModifierProcessor::UMEHealthModifierProcessor()
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::All);
	ExecutionOrder.ExecuteInGroup = ME::ProcessorGroupNames::Gameplay;
	ExecutionOrder.ExecuteAfter.Add(UE::Mass::ProcessorGroupNames::Movement);
}

void UMEHealthModifierProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FMEHealthFragment>(EMassFragmentAccess::ReadWrite, EMassFragmentPresence::All);
	EntityQuery.AddRequirement<FMEModifyHealthFragment>(EMassFragmentAccess::ReadOnly, EMassFragmentPresence::All);
	EntityQuery.AddConstSharedRequirement<FMEHealthParamsFragment>(EMassFragmentPresence::All);
	EntityQuery.AddTagRequirement<FMEShouldModifyHealthTag>(EMassFragmentPresence::All);
}

void UMEHealthModifierProcessor::Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk
	(EntitySubsystem, Context, [this](FMassExecutionContext& Context)
	 {
		 const TArrayView<FMEModifyHealthFragment> ModifierList = Context.GetMutableFragmentView<FMEModifyHealthFragment>();
		 const TArrayView<FMEHealthFragment> HealthList = Context.GetMutableFragmentView<FMEHealthFragment>();
		 const FMEHealthParamsFragment& HealthParams = Context.GetConstSharedFragment<FMEHealthParamsFragment>();

		 for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		 {
			 FMEModifyHealthFragment& Modifier = ModifierList[EntityIndex];
			 FMEHealthFragment& Health = HealthList[EntityIndex];

			 const float DeltaTime = Context.GetDeltaTimeSeconds();
			 Modifier.Timer -= DeltaTime;
			 if (Modifier.Time == -1)
			 {
				 Health.Health += Modifier.Amount;
				 Context.Defer().RemoveTag<FMEShouldModifyHealthTag>(Context.GetEntity(EntityIndex));
			 }
			 else
			 {
				 if (Modifier.Timer <= 0.0f)
				 {
					 Health.Health += Modifier.Amount;
					 Modifier.Time -= 1;
					 Modifier.Timer = 1.0f;
				 }
				 if (Modifier.Time == 0)
				 {
					 Context.Defer().RemoveTag<FMEShouldModifyHealthTag>(Context.GetEntity(EntityIndex));
				 }
			 }

			 if (Health.Health + Modifier.Amount <= 0.0f)
				 Context.Defer().DestroyEntity(Context.GetEntity(EntityIndex));
		 }
	 }
	);
}
