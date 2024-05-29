/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CoreMinimal.h"
#include "MassCommonFragments.h"
#include "MassEntityView.h"

namespace ME::ProcessorGroupNames
{
	const FName Gameplay = FName(TEXT("Gameplay"));
}

// STRUCTS

struct FMEHashGrid
{
	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	FMEHashGrid()
		: CellSize(0.0f),
		  ObjectCollision(FBox{}),
		  EntitySubsystem(nullptr)
	{
	}

	FMEHashGrid(double InCellSize, FBox ObjectCollision, UMassEntitySubsystem* InOutEntitySubsystem)
		: CellSize(InCellSize),
		  ObjectCollision(ObjectCollision),
		  EntitySubsystem(InOutEntitySubsystem)
	{
	}

	// FUNCTIONS
public:
	void InsertValue(const FMassEntityHandle& Value, const FVector& Position)
	{
		const FIntVector Index{ToGrid(Position)};
		Grid.Add(Index, Value);
	}

	bool RemoveValue(const FMassEntityHandle& Value, const FVector& Position)
	{
		const FIntVector Index{ToGrid(Position)};
		return Grid.Remove(Index, Value) > 0;
	}

	bool IsCellEmpty(const FVector& Position) const
	{
		const FIntVector Index{ToGrid(Position)};
		return !Grid.Contains(Index);
	}

	void UpdateValues(const FMassEntityHandle& Value, const FVector& OldPosition, const FVector& NewPosition)
	{
		const FIntVector OldIndex = ToGrid(OldPosition);
		const FIntVector NewIndex = ToGrid(NewPosition);

		if (OldIndex == NewIndex)
			return;
		
		const bool bWasAtOldPos = Grid.RemoveSingle(OldIndex, Value) == 1;
		check(bWasAtOldPos); //TOOD: Crash
		Grid.Add(NewIndex, Value);
	}

	TPair<FMassEntityHandle, double> FindNearestValueInRadius(const FVector& QueryPoint, double Radius) const
	{
		if (!Grid.Num())
			return TPair<FMassEntityHandle, double>(FMassEntityHandle{},MAX_dbl);

		const FIntVector MinIndex = ToGrid(QueryPoint - Radius * FVector::One());
		const FIntVector MaxIndex = ToGrid(QueryPoint + Radius * FVector::One());

		double MinDistsq = MAX_dbl;
		FMassEntityHandle Nearest{};
		const double RadiusSquared = Radius * Radius;


		TArray<FMassEntityHandle> Values;
		for (int Z = MinIndex.Z; Z <= MaxIndex.Z; Z++)
		{
			for (int Y = MinIndex.Y; Y <= MaxIndex.Z; Y++)
			{
				for (int X = MinIndex.X; X <= MaxIndex.Z; X++)
				{
					FIntVector Index{X, Y, Z};
					Values.Reset();
					Grid.MultiFind(Index, Values);
					for (const auto& It : Values)
					{
						//TODO: Ignore Function

						FVector ValueLocation = FMassEntityView(*EntitySubsystem, It).
						                        GetFragmentData<FTransformFragment>().GetTransform().GetLocation();
						const double Distsq = FVector::DistSquared(ValueLocation, QueryPoint);
						if (Distsq < RadiusSquared && Distsq < MinDistsq)
						{
							Nearest = It;
							MinDistsq = Distsq;
						}
					}
				}
			}
		}

		return TPair<FMassEntityHandle, double>(Nearest, MinDistsq);
	}

	int FindValuesInSphere(const FVector& QueryPoint, double Radius, TArray<FMassEntityHandle>& ResultsOut) const
	{
		if (!Grid.Num())
			return 0;

		const FIntVector MinIndex = ToGrid(QueryPoint - Radius * FVector::One());
		const FIntVector MaxIndex = ToGrid(QueryPoint + Radius * FVector::One());

		const double RadiusSquared = Radius * Radius;

		TArray<FMassEntityHandle> Values;
		for (int Z = MinIndex.Z; Z <= MaxIndex.Z; Z++)
		{
			for (int Y = MinIndex.Y; Y <= MaxIndex.Z; Y++)
			{
				for (int X = MinIndex.X; X <= MaxIndex.Z; X++)
				{
					FIntVector Index{X, Y, Z};
					Values.Reset();
					Grid.MultiFind(Index, Values);
					for (const auto& It : Values)
					{
						//TODO: Ignore Function

						FVector ValueLocation = FMassEntityView(*EntitySubsystem, It).
						                        GetFragmentData<FTransformFragment>().GetTransform().GetLocation();
						const double Distsq = FVector::DistSquared(ValueLocation, QueryPoint);
						if (Distsq < RadiusSquared)
						{
							ResultsOut.Add(It);
						}
					}
				}
			}
		}

		return ResultsOut.Num();
	}

	/** Convert real-valued point to integer grid coordinates */
	FIntVector ToGrid(const FVector& P) const
	{
		return FIntVector(
			static_cast<int32>(FMath::Floor(P.X / CellSize)),
			static_cast<int32>(FMath::Floor(P.Y / CellSize)),
			static_cast<int32>(FMath::Floor(P.Z / CellSize)));
	}

	/** Convert integer grid coordinates to double-valued point */
	FVector FromGrid(const FIntVector& GridPoint) const
	{
		return FVector{GridPoint.X * CellSize, GridPoint.Y * CellSize, GridPoint.Z * CellSize};
	}

	// PROPERTIES
private:
	double CellSize;
	FBox ObjectCollision;
	TMultiMap<FIntVector, FMassEntityHandle> Grid;
	UMassEntitySubsystem* EntitySubsystem;
};
