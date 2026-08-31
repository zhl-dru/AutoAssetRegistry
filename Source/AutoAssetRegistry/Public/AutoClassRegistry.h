#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AutoClassRegistry.generated.h"

UCLASS(BlueprintType)
class AUTOASSETREGISTRY_API UAutoClassRegistry final : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Class Registry")
	UClass* Find(FName Key) const;

	UFUNCTION(BlueprintPure, Category = "Class Registry")
	TArray<FName> GetNames() const;

#if WITH_EDITOR
	UClass* Load() const;
	bool Replace(TMap<FName, TSubclassOf<UObject>>&& NewClasses);
#endif

private:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Registry Generation", meta = (AllowAbstract = "true"))
	TSoftClassPtr<UObject> BaseClass;
#endif

	UPROPERTY(VisibleAnywhere, Category = "Generated Registry")
	TMap<FName, TSubclassOf<UObject>> Classes;
};

