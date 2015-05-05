/*
    Overwolf Guild Wars 2 Mumble Link Plugin
    Copyright (c) 2015 Paul Hooijenga
*/

#include "nsPluginInstanceOverwolfGW2.h"
#include "nsScriptableObjectOverwolfGW2.h"
#include "utils/Log.h"

// we use this to force our plugin container to shut down
// when no one is using it.  Browsers try to keep the plugin
// open for optimization reasons - we don't want it
int nsPluginInstanceOverwolfGW2::ref_count = 0;

nsPluginInstanceOverwolfGW2::nsPluginInstanceOverwolfGW2(NPP instance) : nsPluginInstanceBase() {
    this->instance = instance;
    this->initialized = FALSE;
    this->scriptable_object = NULL;
    nsPluginInstanceOverwolfGW2::ref_count++;
}

nsPluginInstanceOverwolfGW2::~nsPluginInstanceOverwolfGW2() {
    nsPluginInstanceOverwolfGW2::ref_count--;

    if (nsPluginInstanceOverwolfGW2::ref_count == 0) {
        PostQuitMessage(0);
    }
}

NPBool nsPluginInstanceOverwolfGW2::init(NPWindow* window) {
    initialized = TRUE;
    return TRUE;
}

void nsPluginInstanceOverwolfGW2::shut() {
    if (scriptable_object != NULL) {
      NPN_ReleaseObject(scriptable_object);
    }

    initialized = FALSE;
}

NPBool nsPluginInstanceOverwolfGW2::isInitialized() {
    return initialized;
}

NPError nsPluginInstanceOverwolfGW2::GetValue(NPPVariable variable, void* ret_value) {
    NPError rv = NPERR_INVALID_PARAM;

    switch (variable) {
        case NPPVpluginScriptableNPObject:
            if (scriptable_object == NULL) {
                scriptable_object = NPN_CreateObject(instance, GET_NPOBJECT_CLASS(nsScriptableObjectOverwolfGW2));

                NPN_RetainObject(scriptable_object);

                ((nsScriptableObjectOverwolfGW2*)scriptable_object)->Init();
            }

            *(NPObject **)ret_value = scriptable_object;
            rv = NPERR_NO_ERROR;

        default:
            break;
    }

    return rv;
}
