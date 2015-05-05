/*
    Overwolf Guild Wars 2 Mumble Link Plugin
    Copyright (c) 2015 Paul Hooijenga
*/

#ifndef NPOVERWOLFGW2PLUGIN_H_
#define NPOVERWOLFGW2PLUGIN_H_

#include <memory>
#include <windows.h>
#include "plugin_common/pluginbase.h"

class nsPluginInstanceOverwolfGW2 : public nsPluginInstanceBase {

public:
    nsPluginInstanceOverwolfGW2(NPP instance);
    virtual ~nsPluginInstanceOverwolfGW2();

public:
    NPBool init(NPWindow* window);
    void shut();
    NPBool isInitialized();

    NPError GetValue(NPPVariable variable, void* scriptable_object_);

private:
    NPP instance;
    NPBool initialized;

    NPObject* scriptable_object;

    static int ref_count;
};

#endif
