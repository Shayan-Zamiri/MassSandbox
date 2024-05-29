/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
* You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "MSVisualizationTrait.h"
#include "MassActorSubsystem.h"
#include "MassEntityTemplateRegistry.h"
#include "MassVisualizer.h"
#include "MassSandbox/Fragments/MSMovementFragments.h"

UMSVisualizationTrait::UMSVisualizationTrait()
{
	Params.LODRepresentation[EMassLOD::High] = EMassRepresentationType::StaticMeshInstance;
	Params.LODRepresentation[EMassLOD::Medium] = EMassRepresentationType::StaticMeshInstance;
	Params.LODRepresentation[EMassLOD::Low] = EMassRepresentationType::StaticMeshInstance;
	Params.LODRepresentation[EMassLOD::Off] = EMassRepresentationType::StaticMeshInstance;
	HighResTemplateActor = AMassVisualizer::StaticClass();
	LowResTemplateActor = AMassVisualizer::StaticClass();
}

void UMSVisualizationTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	Super::BuildTemplate(BuildContext, World);

	BuildContext.AddFragment<FMassActorFragment>();
}
