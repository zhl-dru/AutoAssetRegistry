#include "AutoObjectRegistry.h"
#include "AutoRegistryMacros.h"

AUTO_REGISTRY_FIND_IMPL(UAutoObjectRegistry, UObject*, Objects, Found->LoadSynchronous())

AUTO_REGISTRY_GET_NAMES_IMPL(UAutoObjectRegistry, Objects)

#if WITH_EDITOR
AUTO_REGISTRY_LOAD_IMPL(UAutoObjectRegistry, UClass*, BaseClass)

AUTO_REGISTRY_REPLACE_IMPL(UAutoObjectRegistry, Objects)
#endif

