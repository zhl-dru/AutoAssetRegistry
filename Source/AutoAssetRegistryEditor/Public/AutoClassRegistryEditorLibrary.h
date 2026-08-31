#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AutoClassRegistryEditorLibrary.generated.h"

class UAutoClassRegistry;


UCLASS()
class AUTOASSETREGISTRYEDITOR_API UAutoClassRegistryEditorLibrary final
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Class Registry")
	static bool RebuildRegistry(UAutoClassRegistry* Registry);

	
	UFUNCTION(BlueprintCallable, Category = "Class Registry")
	static bool RebuildAllRegistries();

};

