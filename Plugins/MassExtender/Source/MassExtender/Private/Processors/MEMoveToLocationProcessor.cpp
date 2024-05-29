/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "Processors/MEMoveToLocationProcessor.h"
#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "MassMovementFragments.h"
#include "METypes.h"
#include "Fragments/MEHashGridFragments.h"
#include "Fragments/MEMovementFragments.h"


// CTOR/DTOR & VIRTUAL FUNCTIONS

UMEMoveToLocationProcessor::UMEMoveToLocationProcessor()
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::All);
	ExecutionOrder.ExecuteInGroup = UE::Mass::ProcessorGroupNames::Movement;
}

void UMEMoveToLocationProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite, EMassFragmentPresence::All);
	EntityQuery.AddRequirement<FMassVelocityFragment>(EMassFragmentAccess::ReadWrite, EMassFragmentPresence::All);
	EntityQuery.AddRequirement<FMETargetLocationFragment>(EMassFragmentAccess::ReadOnly, EMassFragmentPresence::All);
	EntityQuery.AddSharedRequirement<FMEMovementParamsSharedFragment>(EMassFragmentAccess::ReadOnly, EMassFragmentPresence::All);
	EntityQuery.AddSharedRequirement<FMEHashGridSharedFragment>(EMassFragmentAccess::ReadWrite, EMassFragmentPresence::All);
	EntityQuery.AddTagRequirement<FMEMoveToLocationTag>(EMassFragmentPresence::All);
}

void UMEMoveToLocationProcessor::Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk(EntitySubsystem, Context, [this,&EntitySubsystem](FMassExecutionContext& Context)
	{
		const TArrayView<FTransformFragment>& TransformList = Context.GetMutableFragmentView<FTransformFragment>();
		const TArrayView<FMassVelocityFragment>& VelocityList = Context.GetMutableFragmentView<FMassVelocityFragment>();
		const TArrayView<FMETargetLocationFragment>& TargetLocationList = Context.GetMutableFragmentView<FMETargetLocationFragment>();
		const FMEMovementParamsSharedFragment& MovementParams = Context.GetSharedFragment<FMEMovementParamsSharedFragment>();
		FMEHashGridSharedFragment& HashGrid = Context.GetMutableSharedFragment<FMEHashGridSharedFragment>();

		const float DeltaTime = Context.GetDeltaTimeSeconds();

		for (int i = 0; i < Context.GetNumEntities(); i++)
		{
			FTransform& Transform = TransformList[i].GetMutableTransform();
			const FVector Location = Transform.GetLocation();
			FVector& TargetLocation = TargetLocationList[i].Location;
			FVector& Velocity = VelocityList[i].Value;
			Velocity = (TargetLocation - Location).GetSafeNormal() * MovementParams.Speed;
			FVector NewLocation = Location + Velocity * DeltaTime;

			TArray<FMassEntityHandle> Res;
			const int32 Num = HashGrid.HashGrid.FindValuesInSphere(Location, HashGrid.CellSize, Res);

			if (Num == 0)
			{
				FVector OldLocation = Location;
				Transform.SetLocation(NewLocation);
				HashGrid.HashGrid.UpdateValues(Context.GetEntity(i), OldLocation, NewLocation);
			}


			for (const auto& It : Res)
			{
				if (HashGrid.Collision.MoveTo(Location).Intersect(HashGrid.Collision.MoveTo(
					FMassEntityView{EntitySubsystem, It}.GetFragmentData<FTransformFragment>().GetTransform().GetLocation())))
				{
					FBox Test = HashGrid.Collision.MoveTo(Location);
					FBox Test2 = HashGrid.Collision.MoveTo(
						FMassEntityView{EntitySubsystem, It}.GetFragmentData<FTransformFragment>().GetTransform().GetLocation());
					DrawDebugBox(GetWorld(), Test.GetCenter(), Test.GetExtent(), FColor::Red);
					DrawDebugBox(GetWorld(), Test2.GetCenter(), Test2.GetExtent(), FColor::Green);
					break;
				}

				FVector OldLocation = Location;
				Transform.SetLocation(NewLocation);
				HashGrid.HashGrid.UpdateValues(Context.GetEntity(i), OldLocation, NewLocation);
			}


			if (FMath::IsNearlyEqual(Location.X, TargetLocation.X, 0.1f) && FMath::IsNearlyEqual(Location.Y, TargetLocation.Y, 0.1f))
			{
				TargetLocationList[i].bIsLocationSet = false;
				Context.Defer().RemoveTag<FMEMoveToLocationTag>(Context.GetEntity(i));
			}
		}
	});
}
