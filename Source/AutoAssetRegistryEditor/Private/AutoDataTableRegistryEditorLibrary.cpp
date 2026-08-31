#include "AutoDataTableRegistryEditorLibrary.h"

#include "AutoDataTableRegistry.h"
#include "ProjectAssetCollector.h"

namespace
{
	bool Rebuild(UAutoDataTableRegistry* Registry)
	{
		if (!Registry)
		{
			return false;
		}
		UScriptStruct* RowStruct = Registry->Load();
		if (!RowStruct)
		{
			return false;
		}

		TArray<FAssetData> Assets;
		FARFilter AssetFilter;
		AssetFilter.ClassPaths.Add(UDataTable::StaticClass()->GetClassPathName());
		AssetFilter.bRecursiveClasses = true;
		FProjectAssetCollector::Collect(AssetFilter, Assets);
		TMap<FName, TSoftObjectPtr<UDataTable>> Tables;
		for (const FAssetData& Asset : Assets)
		{
			UDataTable* Table = Cast<UDataTable>(Asset.GetAsset());
			if (!Table || Table->GetRowStruct() != RowStruct)
			{
				continue;
			}
			const FName Path(*Asset.ToSoftObjectPath().ToString());
			Tables.Add(Path, TSoftObjectPtr<UDataTable>(Asset.ToSoftObjectPath()));
		}
		return Registry->Replace(MoveTemp(Tables));
	}
}

bool UAutoDataTableRegistryEditorLibrary::RebuildRegistry(UAutoDataTableRegistry* Registry)
{
	return Rebuild(Registry);
}

bool UAutoDataTableRegistryEditorLibrary::RebuildAllRegistries()
{
	return FProjectAssetCollector::RebuildAll<UAutoDataTableRegistry>(Rebuild);
}

