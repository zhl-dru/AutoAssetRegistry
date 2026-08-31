#include "AutoClassRegistry.h"
#include "AutoRegistryMacros.h"

AUTO_REGISTRY_FIND_IMPL(UAutoClassRegistry, UClass*, Classes, Found->Get())

AUTO_REGISTRY_GET_NAMES_IMPL(UAutoClassRegistry, Classes)

#if WITH_EDITOR
AUTO_REGISTRY_LOAD_IMPL(UAutoClassRegistry, UClass*, BaseClass)

AUTO_REGISTRY_REPLACE_IMPL(UAutoClassRegistry, Classes)
#endif

