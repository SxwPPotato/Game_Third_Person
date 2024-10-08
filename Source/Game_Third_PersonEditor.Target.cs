// Game_Third_Person Game by Netologiya. All RightsReserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Game_Third_PersonEditorTarget : TargetRules
{
	public Game_Third_PersonEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Game_Third_Person" } );
	}
}
