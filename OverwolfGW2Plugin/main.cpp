/*
    Overwolf Guild Wars 2 Mumble Link Plugin
    Copyright (c) 2015 Paul Hooijenga
*/

#include "nsPluginInstanceOverwolfGW2.h"

// this defines the mime-type when using <object> or <embed>
// NOTE: this is actually really declared in the Version resource of the dll
char kMimeType[] = "application/x-overwolf-gw2-plugin";

NPError NS_PluginInitialize() {
    return NPERR_NO_ERROR;
}

void NS_PluginShutdown() {
}

nsPluginInstanceBase* NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct) {
    if (aCreateDataStruct == NULL) {
        return nullptr;
    }

    return new nsPluginInstanceOverwolfGW2(aCreateDataStruct->instance);
}

void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin) {
    if (aPlugin) {
        delete (nsPluginInstanceOverwolfGW2*)aPlugin;
    }
}

char* NPP_GetMIMEDescription(void) {
    return kMimeType;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
#if DEBUG_MSGBOX
    wchar_t buf[100];

    if (dwReason == DLL_PROCESS_ATTACH) {
        wsprintfW(buf, L"DLL_PROCESS_ATTACH\r\npid = %d", GetCurrentProcessId());
        MessageBoxW(NULL, buf, L"Guild Wars 2 Overwolf Plugin", MB_OK | MB_ICONINFORMATION);
    }
#endif

    return TRUE;
}
