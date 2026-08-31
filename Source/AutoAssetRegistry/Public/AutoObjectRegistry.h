#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AutoObjectRegistry.generated.h"

UCLASS(BlueprintType)
class AUTOASSETREGISTRY_API UAutoObjectRegistry final : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Object Registry")
	UObject* Find(FName Key) const;

	UFUNCTION(BlueprintPure, Category = "Object Registry")
	TArray<FName> GetNames() const;

#if WITH_EDITOR
	UClass* Load() const;
	bool Replace(TMap<FName, TSoftObjectPtr<UObject>>&& NewObjects);
#endif

private:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Registry Generation", meta = (AllowAbstract = "true"))
	TSoftClassPtr<UObject> BaseClass;
#endif

	UPROPERTY(VisibleAnywhere, Category = "Generated Registry")
	TMap<FName, TSoftObjectPtr<UObject>> Objects;
};

