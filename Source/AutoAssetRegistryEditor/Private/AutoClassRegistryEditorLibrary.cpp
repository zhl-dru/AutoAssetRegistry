#include "AutoClassRegistryEditorLibrary.h"

#include "AutoClassRegistry.h"
#include "Engine/Blueprint.h"
#include "ProjectAssetCollector.h"

DEFINE_LOG_CATEGORY_STATIC(LogAutoClassRegistry, Log, All);

namespace
{
bool RebuildInternal(UAutoClassRegistry* Registry)
{
	if (!Registry)
	{
		return false;
	}

	UClass* BaseClass = Registry->Load();
	if (!BaseClass)
	{
		return false;
	}
	TArray<FAssetData> Assets;
	FARFilter AssetFilter;
	AssetFilter.ClassPaths.Add(UBlueprint::StaticClass()->GetClassPathName());
	AssetFilter.bRecursiveClasses = true;
	FProjectAssetCollector::Collect(AssetFilter, Assets);
	Assets.Sort([](const FAssetData& Left, const FAssetData& Right)
	{
		return Left.PackageName.ToString() < Right.PackageName.ToString();
	});

	TMap<FName, TSubclassOf<UObject>> GeneratedClasses;
	for (const FAssetData& Asset : Assets)
	{
		const UBlueprint* Blueprint = Cast<UBlueprint>(Asset.GetAsset());
		UClass* GeneratedClass = Blueprint ? Blueprint->GeneratedClass : nullptr;
		if (!GeneratedClass || GeneratedClass == BaseClass ||
			!GeneratedClass->IsChildOf(BaseClass) ||
			GeneratedClass->HasAnyClassFlags(
				CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists))
		{
			continue;
		}

		const FName TypeName = Asset.AssetName;
		if (const TSubclassOf<UObject>* ExistingClass = GeneratedClasses.Find(TypeName))
		{
			UE_LOG(
				LogAutoClassRegistry,
				Error,
				TEXT("Registry %s contains duplicate type name %s: %s and %s"),
				*Registry->GetPathName(),
				*TypeName.ToString(),
				*ExistingClass->Get()->GetPathName(),
				*GeneratedClass->GetPathName());
			return false;
		}

		GeneratedClasses.Add(TypeName, GeneratedClass);
	}

	const int32 ClassCount = GeneratedClasses.Num();
	const bool bChanged = Registry->Replace(MoveTemp(GeneratedClasses));
	UE_LOG(
		LogAutoClassRegistry,
		Log,
		TEXT("Registry %s generated %d classes%s"),
		*Registry->GetPathName(),
		ClassCount,
		bChanged ? TEXT(" and was updated") : TEXT(""));
	return true;
}
}

bool UAutoClassRegistryEditorLibrary::RebuildRegistry(UAutoClassRegistry* Registry)
{
	return RebuildInternal(Registry);
}

bool UAutoClassRegistryEditorLibrary::RebuildAllRegistries()
{
	return FProjectAssetCollector::RebuildAll<UAutoClassRegistry>(
		[](UAutoClassRegistry* Registry)
		{
			return RebuildInternal(Registry);
		});
}

