// Copyright 2018 GitHub BlindGazer, All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DevourerEditorTarget : TargetRules
{
	public DevourerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Devourer" } );
	}
}
