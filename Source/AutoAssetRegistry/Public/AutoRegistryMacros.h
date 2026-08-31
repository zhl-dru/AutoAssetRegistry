#pragma once

#define AUTO_REGISTRY_FIND_IMPL(RegistryType, ReturnType, MapMember, ValueExpression) \
ReturnType RegistryType::Find(FName Key) const \
{ \
    const auto* Found = MapMember.Find(Key); \
    return Found ? (ValueExpression) : nullptr; \
}

#define AUTO_REGISTRY_GET_NAMES_IMPL(RegistryType, MapMember) \
TArray<FName> RegistryType::GetNames() const \
{ \
    TArray<FName> Names; \
    MapMember.GetKeys(Names); \
    Names.Sort(FNameLexicalLess()); \
    return Names; \
}

#if WITH_EDITORONLY_DATA
#define AUTO_REGISTRY_LOAD_IMPL(RegistryType, ReturnType, ConfigMember) \
ReturnType RegistryType::Load() const \
{ \
    return ConfigMember.LoadSynchronous(); \
}
#else
#define AUTO_REGISTRY_LOAD_IMPL(RegistryType, ReturnType, ConfigMember) \
ReturnType RegistryType::Load() const \
{ \
    return nullptr; \
}
#endif

#define AUTO_REGISTRY_REPLACE_IMPL(RegistryType, MapMember) \
bool RegistryType::Replace(decltype(MapMember)&& NewValues) \
{ \
    if (MapMember.OrderIndependentCompareEqual(NewValues)) \
    { \
        return false; \
    } \
    Modify(); \
    MapMember = MoveTemp(NewValues); \
    MarkPackageDirty(); \
    return true; \
}
