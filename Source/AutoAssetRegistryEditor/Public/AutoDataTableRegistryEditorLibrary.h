#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AutoDataTableRegistryEditorLibrary.generated.h"

class UAutoDataTableRegistry;

UCLASS()
class AUTOASSETREGISTRYEDITOR_API UAutoDataTableRegistryEditorLibrary final
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "DataTable Registry")
	static bool RebuildRegistry(UAutoDataTableRegistry* Registry);

	UFUNCTION(BlueprintCallable, Category = "DataTable Registry")
	static bool RebuildAllRegistries();
};

