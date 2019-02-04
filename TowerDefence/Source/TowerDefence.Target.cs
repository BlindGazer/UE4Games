// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TowerDefenceTarget : TargetRules
{
	public TowerDefenceTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "TowerDefence" } );
	}
}
