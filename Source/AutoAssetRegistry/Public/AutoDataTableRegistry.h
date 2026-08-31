#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "AutoDataTableRegistry.generated.h"

UCLASS(BlueprintType)
class AUTOASSETREGISTRY_API UAutoDataTableRegistry final : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "DataTable Registry")
	UDataTable* Find(FName Key) const;

	UFUNCTION(BlueprintPure, Category = "DataTable Registry")
	TArray<FName> GetNames() const;

#if WITH_EDITOR
	UScriptStruct* Load() const;
	bool Replace(TMap<FName, TSoftObjectPtr<UDataTable>>&& NewTables);
#endif

private:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Registry Generation")
	TSoftObjectPtr<UScriptStruct> RowStruct;
#endif

	UPROPERTY(VisibleAnywhere, Category = "Generated Registry")
	TMap<FName, TSoftObjectPtr<UDataTable>> Tables;
};

