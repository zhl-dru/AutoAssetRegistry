using UnrealBuildTool;

public class AutoAssetRegistryEditor : ModuleRules
{
    public AutoAssetRegistryEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "AssetRegistry",
            "AutoAssetRegistry"
        });
        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "UnrealEd"
        });
    }
}
