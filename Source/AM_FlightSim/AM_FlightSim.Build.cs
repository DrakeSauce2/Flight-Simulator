// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AM_FlightSim : ModuleRules
{
	public AM_FlightSim(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { "EnhancedInput", "Slate", "SlateCore", "UMG", "Niagara" });

    }
}
