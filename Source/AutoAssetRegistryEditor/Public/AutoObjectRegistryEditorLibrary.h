#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AutoObjectRegistryEditorLibrary.generated.h"

class UAutoObjectRegistry;

UCLASS()
class AUTOASSETREGISTRYEDITOR_API UAutoObjectRegistryEditorLibrary final
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Object Registry")
	static bool RebuildRegistry(UAutoObjectRegistry* Registry);

	UFUNCTION(BlueprintCallable, Category = "Object Registry")
	static bool RebuildAllRegistries();
};

