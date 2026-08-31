#include "ProjectAssetCollector.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Modules/ModuleManager.h"

void FProjectAssetCollector::Collect(const FARFilter& Filter, TArray<FAssetData>& OutAssets)
{
    OutAssets.Reset();
    FAssetRegistryModule& Module =
        FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
    Module.Get().GetAssets(Filter, OutAssets);
}

