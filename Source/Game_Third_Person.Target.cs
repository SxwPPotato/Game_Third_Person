// Game_Third_Person Game by Netologiya. All RightsReserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Game_Third_PersonTarget : TargetRules
{
	public Game_Third_PersonTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Game_Third_Person" } );
	}
}
