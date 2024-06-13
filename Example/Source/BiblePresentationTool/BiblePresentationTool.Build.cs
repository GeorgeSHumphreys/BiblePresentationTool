// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BiblePresentationTool : ModuleRules
{
	public BiblePresentationTool(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG" });
	}
}
