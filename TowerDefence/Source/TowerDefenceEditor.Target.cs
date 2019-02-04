// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TowerDefenceEditorTarget : TargetRules
{
	public TowerDefenceEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "TowerDefence" } );
	}
}
