#include "nsScriptableObjectBase.h"

nsScriptableObjectBase::nsScriptableObjectBase(NPP npp) : npp(npp) {
}

nsScriptableObjectBase::~nsScriptableObjectBase() {
}

void nsScriptableObjectBase::Invalidate() {
}

bool nsScriptableObjectBase::HasMethod(NPIdentifier name) {
   return false;
}

bool nsScriptableObjectBase::Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result) {
    return false;
}

bool nsScriptableObjectBase::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result) {
    return false;
}

bool nsScriptableObjectBase::HasProperty(NPIdentifier name) {
    return false;
}

bool nsScriptableObjectBase::GetProperty(NPIdentifier name, NPVariant *result) {
    return false;
}

bool nsScriptableObjectBase::SetProperty(NPIdentifier name, const NPVariant *value) {
   return false;
}

bool nsScriptableObjectBase::RemoveProperty(NPIdentifier name) {
    return false;
}

bool nsScriptableObjectBase::Enumerate(NPIdentifier **value, uint32_t *count) {
    return false;
}

bool nsScriptableObjectBase::Construct(const NPVariant *args, uint32_t argCount, NPVariant *result) {
    return false;
}

void nsScriptableObjectBase::_Deallocate(NPObject *npobj) {
    TRACE_SCRIPTABLE_METHOD();
    /* XXX: This crashes sometimes with npobj == 0x00000001 */
    // delete (nsScriptableObjectBase*)npobj;
}

void nsScriptableObjectBase::_Invalidate(NPObject *npobj) {
    TRACE_SCRIPTABLE_METHOD();
    ((nsScriptableObjectBase*)npobj)->Invalidate();
}

bool nsScriptableObjectBase::_HasMethod(NPObject *npobj, NPIdentifier name) {
#if TRACE_METHODS
    NPUTF8* n = NPN_UTF8FromIdentifier(name);
    TRACE_SCRIPTABLE_METHOD_ARGS(L"name: %hs", n);
    NPN_MemFree(n);
#endif

    return ((nsScriptableObjectBase*)npobj)->HasMethod(name);
}

bool nsScriptableObjectBase::_Invoke(NPObject *npobj, NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result) {
#if TRACE_METHODS
    NPUTF8* n = NPN_UTF8FromIdentifier(name);
    TRACE_SCRIPTABLE_METHOD_ARGS(L"name: %hs; args: %p; argCount: %u; result: %p", n, args, argCount, result);
    NPN_MemFree(n);
#endif

    return ((nsScriptableObjectBase*)npobj)->Invoke(name, args, argCount, result);
}

bool nsScriptableObjectBase::_InvokeDefault(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
    TRACE_SCRIPTABLE_METHOD_ARGS(L"args: %p; argCount: %u; result: %p", args, argCount, result);

    return ((nsScriptableObjectBase*)npobj)->InvokeDefault(args, argCount, result);
}

bool nsScriptableObjectBase::_HasProperty(NPObject *npobj, NPIdentifier name) {
#if TRACE_METHODS
    NPUTF8* n = NPN_UTF8FromIdentifier(name);
    TRACE_SCRIPTABLE_METHOD_ARGS(L"name: %hs", n);
    NPN_MemFree(n);
#endif

    return ((nsScriptableObjectBase*)npobj)->HasProperty(name);
}

bool nsScriptableObjectBase::_GetProperty(NPObject *npobj, NPIdentifier name, NPVariant *result) {
#if TRACE_METHODS
    NPUTF8* n = NPN_UTF8FromIdentifier(name);
    TRACE_SCRIPTABLE_METHOD_ARGS(L"name: %hs; result: %p", n, result);
    NPN_MemFree(n);
#endif

    return ((nsScriptableObjectBase*)npobj)->GetProperty(name, result);
}

bool nsScriptableObjectBase::_SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value) {
#if TRACE_METHODS
    NPUTF8* n = NPN_UTF8FromIdentifier(name);
    TRACE_SCRIPTABLE_METHOD_ARGS(L"name: %hs; value: %p", n, value);
    NPN_MemFree(n);
#endif

    return ((nsScriptableObjectBase*)npobj)->SetProperty(name, value);
}

bool nsScriptableObjectBase::_RemoveProperty(NPObject *npobj, NPIdentifier name) {
#if TRACE_METHODS
    NPUTF8* n = NPN_UTF8FromIdentifier(name);
    TRACE_SCRIPTABLE_METHOD_ARGS(L"name: %hs", n);
    NPN_MemFree(n);
#endif

    return ((nsScriptableObjectBase*)npobj)->RemoveProperty(name);
}

bool nsScriptableObjectBase::_Enumerate(NPObject *npobj, NPIdentifier **value, uint32_t *count) {
    TRACE_SCRIPTABLE_METHOD_ARGS(L"value: %p; count: %p", value, count);
    return ((nsScriptableObjectBase*)npobj)->Enumerate(value, count);
}

bool nsScriptableObjectBase::_Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
    TRACE_SCRIPTABLE_METHOD_ARGS(L"args: %p; argCount: %u; result: %p", args, argCount, result);
    return ((nsScriptableObjectBase*)npobj)->Construct(args, argCount, result);
}
