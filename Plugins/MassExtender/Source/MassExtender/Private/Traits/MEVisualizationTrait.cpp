/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "Traits/MEVisualizationTrait.h"
#include "MassActorSubsystem.h"
#include "MassEntityTemplateRegistry.h"
#include "MassVisualizer.h"

UMEVisualizationTrait::UMEVisualizationTrait()
{
	Params.LODRepresentation[EMassLOD::High] = EMassRepresentationType::StaticMeshInstance;
	Params.LODRepresentation[EMassLOD::Medium] = EMassRepresentationType::StaticMeshInstance;
	Params.LODRepresentation[EMassLOD::Low] = EMassRepresentationType::StaticMeshInstance;
	Params.LODRepresentation[EMassLOD::Off] = EMassRepresentationType::StaticMeshInstance;
	HighResTemplateActor = AActor::StaticClass();
	LowResTemplateActor = AActor::StaticClass();
}

void UMEVisualizationTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	Super::BuildTemplate(BuildContext, World);

	BuildContext.AddFragment<FMassActorFragment>();
}
