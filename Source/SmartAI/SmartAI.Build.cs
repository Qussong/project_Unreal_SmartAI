// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SmartAI : ModuleRules
{
	public SmartAI(ReadOnlyTargetRules Target) : base(Target)
	{
        PublicIncludePaths.AddRange(new string[] { "SmartAI" });

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
