/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */


using UnrealBuildTool;

public class MassExtender : ModuleRules
{
	public MassExtender(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"MassEntity",
				"MassCommon",
				"MassSpawner",
				"StructUtils",
				"MassRepresentation",
				"MassActors",
				"MassMovement",
				"DeveloperSettings"
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine"
			}
		);
	}
}