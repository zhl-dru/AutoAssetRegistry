#include "AutoDataTableRegistry.h"
#include "AutoRegistryMacros.h"

AUTO_REGISTRY_FIND_IMPL(UAutoDataTableRegistry, UDataTable*, Tables, Found->LoadSynchronous())

AUTO_REGISTRY_GET_NAMES_IMPL(UAutoDataTableRegistry, Tables)

#if WITH_EDITOR
AUTO_REGISTRY_LOAD_IMPL(UAutoDataTableRegistry, UScriptStruct*, RowStruct)

AUTO_REGISTRY_REPLACE_IMPL(UAutoDataTableRegistry, Tables)
#endif

