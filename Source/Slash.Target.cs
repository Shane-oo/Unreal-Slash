using UnrealBuildTool;

public class SlashTarget: TargetRules
{
	#region Construction

	public SlashTarget(TargetInfo Target): base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange(new[] { "Slash" });
	}

	#endregion
}
