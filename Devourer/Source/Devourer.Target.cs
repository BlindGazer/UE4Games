// Copyright 2018 GitHub BlindGazer, All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DevourerTarget : TargetRules
{
	public DevourerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Devourer" } );
	}
}
