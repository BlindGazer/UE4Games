// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

using UnrealBuildTool;

public class TowerDefence : ModuleRules
{
	public TowerDefence(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivatePCHHeaderFile = "Public/TowerDefence.h";
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule" , "NavigationSystem", "UMG" });

        PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
