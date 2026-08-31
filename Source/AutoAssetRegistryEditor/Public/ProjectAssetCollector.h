#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"

class AUTOASSETREGISTRYEDITOR_API FProjectAssetCollector
{
public:
    static void Collect(const FARFilter& Filter, TArray<FAssetData>& OutAssets);

    template<typename TRegistry, typename TRebuild>
    static bool RebuildAll(TRebuild&& Rebuild)
    {
        FARFilter Filter;
        Filter.ClassPaths.Add(TRegistry::StaticClass()->GetClassPathName());
        Filter.bRecursiveClasses = true;

        TArray<FAssetData> Assets;
        Collect(Filter, Assets);

        bool bSuccess = true;
        for (const FAssetData& Asset : Assets)
        {
            bSuccess = Rebuild(Cast<TRegistry>(Asset.GetAsset())) && bSuccess;
        }
        return bSuccess;
    }
};

