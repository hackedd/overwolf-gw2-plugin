#ifndef NSSCRIPTABLEOBJECTBASE_H_
#define NSSCRIPTABLEOBJECTBASE_H_

#include <windows.h>

#include "plugin_common/pluginbase.h"
#include "utils/Log.h"

#if TRACE_METHODS
#define TRACE_SCRIPTABLE_METHOD() LogMessage(U(__FUNCTION__) L" %p", npobj)
#define TRACE_SCRIPTABLE_METHOD_ARGS(fmt, ...) LogMessage(U(__FUNCTION__) L" %p " fmt, npobj, __VA_ARGS__)
#else
#define TRACE_SCRIPTABLE_METHOD()
#define TRACE_SCRIPTABLE_METHOD_ARGS(...)
#endif

template<class T>
static NPObject* AllocateNpObject(NPP npp, NPClass*) {
  NPObject* obj = new T(npp);
  return obj;
}

/*------------------------------------------------------------------------
class nsScriptableObjectBase : public NPObject

	Inherits From:

	Description:   Helper class that can be used to map calls to the
                   NPObject hooks into virtual methods on instances of
                   classes that derive from this class.

	Data members:

------------------------------------------------------------------------*/
class nsScriptableObjectBase : public NPObject {
public:
    nsScriptableObjectBase(NPP npp);
    virtual ~nsScriptableObjectBase();

public:
    // Virtual NPObject hooks called through this base class. Override
    // as you see fit.
    virtual void Invalidate();
    virtual bool HasMethod(NPIdentifier name);
    virtual bool Invoke(NPIdentifier name, const NPVariant *args,
                    uint32_t argCount, NPVariant *result);
    virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount,
                            NPVariant *result);
    virtual bool HasProperty(NPIdentifier name);
    virtual bool GetProperty(NPIdentifier name, NPVariant *result);
    virtual bool SetProperty(NPIdentifier name, const NPVariant *value);
    virtual bool RemoveProperty(NPIdentifier name);
    virtual bool Enumerate(NPIdentifier **value, uint32_t *count);
    virtual bool Construct(const NPVariant *args, uint32_t argCount, NPVariant *result);

    static void _Deallocate(NPObject *npobj);
    static void _Invalidate(NPObject *npobj);
    static bool _HasMethod(NPObject *npobj, NPIdentifier name);
    static bool _Invoke(NPObject *npobj, NPIdentifier name,
                        const NPVariant *args, uint32_t argCount,
                        NPVariant *result);
    static bool _InvokeDefault(NPObject *npobj, const NPVariant *args,
                               uint32_t argCount, NPVariant *result);
    static bool _HasProperty(NPObject * npobj, NPIdentifier name);
    static bool _GetProperty(NPObject *npobj, NPIdentifier name,
                             NPVariant *result);
    static bool _SetProperty(NPObject *npobj, NPIdentifier name,
                          const NPVariant *value);
    static bool _RemoveProperty(NPObject *npobj, NPIdentifier name);
    static bool _Enumerate(NPObject *npobj, NPIdentifier **value,
                           uint32_t *count);
    static bool _Construct(NPObject *npobj, const NPVariant *args,
                           uint32_t argCount, NPVariant *result);

protected:
    NPP npp;
};

#define DECLARE_NPOBJECT_CLASS_WITH_BASE(_class)   \
static NPClass s##_class##_NPClass = {             \
  NP_CLASS_STRUCT_VERSION,                         \
  AllocateNpObject<_class>,                        \
  nsScriptableObjectBase::_Deallocate,             \
  nsScriptableObjectBase::_Invalidate,             \
  nsScriptableObjectBase::_HasMethod,              \
  nsScriptableObjectBase::_Invoke,                 \
  nsScriptableObjectBase::_InvokeDefault,          \
  nsScriptableObjectBase::_HasProperty,            \
  nsScriptableObjectBase::_GetProperty,            \
  nsScriptableObjectBase::_SetProperty,            \
  nsScriptableObjectBase::_RemoveProperty,         \
  nsScriptableObjectBase::_Enumerate,              \
  nsScriptableObjectBase::_Construct               \
}

#define GET_NPOBJECT_CLASS(_class) &s##_class##_NPClass

#endif
