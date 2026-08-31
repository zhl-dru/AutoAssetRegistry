#include "AutoObjectRegistryEditorLibrary.h"

#include "AutoObjectRegistry.h"
#include "ProjectAssetCollector.h"

namespace
{
	bool Rebuild(UAutoObjectRegistry* Registry)
	{
		if (!Registry) return false;
		UClass* BaseClass = Registry->Load();
		if (!BaseClass) return false;
		TArray<FAssetData> Assets;
		FARFilter AssetFilter;
		AssetFilter.ClassPaths.Add(BaseClass->GetClassPathName());
		AssetFilter.bRecursiveClasses = true;
		FProjectAssetCollector::Collect(AssetFilter, Assets);
		TMap<FName, TSoftObjectPtr<UObject>> Objects;
		for (const FAssetData& Asset : Assets)
		{
			UObject* Object = Asset.GetAsset();
			if (!Object || !Object->IsA(BaseClass)) continue;
			const FName Key(*Asset.ToSoftObjectPath().ToString());
			if (Objects.Contains(Key)) return false;
			Objects.Add(Key, TSoftObjectPtr<UObject>(Asset.ToSoftObjectPath()));
		}
		return Registry->Replace(MoveTemp(Objects));
	}
}

bool UAutoObjectRegistryEditorLibrary::RebuildRegistry(UAutoObjectRegistry* Registry)
{ return Rebuild(Registry); }

bool UAutoObjectRegistryEditorLibrary::RebuildAllRegistries()
{
	return FProjectAssetCollector::RebuildAll<UAutoObjectRegistry>(Rebuild);
}

