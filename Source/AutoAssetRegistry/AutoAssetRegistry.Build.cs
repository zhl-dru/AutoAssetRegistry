using UnrealBuildTool;

public class AutoAssetRegistry : ModuleRules
{
    public AutoAssetRegistry(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
    }
}

