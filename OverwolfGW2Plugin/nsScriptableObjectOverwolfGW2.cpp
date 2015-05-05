/*
    Overwolf Guild Wars 2 Mumble Link Plugin
    Copyright (c) 2015 Paul Hooijenga
*/

#include "nsScriptableObjectOverwolfGW2.h"
#include "utils/Thread.h"
#include "utils/Log.h"
#include "utils/Charset.h"
#include "MumbleLink.h"

#define REGISTER_METHOD(name, method) { \
  methods[NPN_GetStringIdentifier(name)] = &method; \
}

nsScriptableObjectOverwolfGW2::nsScriptableObjectOverwolfGW2(NPP npp) : nsScriptableObjectBase(npp) {
    uiVersion = NPN_GetStringIdentifier("uiVersion");
    uiTick = NPN_GetStringIdentifier("uiTick");
    fAvatarPosition = NPN_GetStringIdentifier("fAvatarPosition");
    fAvatarFront = NPN_GetStringIdentifier("fAvatarFront");
    fAvatarTop = NPN_GetStringIdentifier("fAvatarTop");
    name = NPN_GetStringIdentifier("name");
    fCameraPosition = NPN_GetStringIdentifier("fCameraPosition");
    fCameraFront = NPN_GetStringIdentifier("fCameraFront");
    fCameraTop = NPN_GetStringIdentifier("fCameraTop");
    identity = NPN_GetStringIdentifier("identity");
    serverAddress = NPN_GetStringIdentifier("serverAddress");
    mapId = NPN_GetStringIdentifier("mapId");
    mapType = NPN_GetStringIdentifier("mapType");
    shardId = NPN_GetStringIdentifier("shardId");
    instance = NPN_GetStringIdentifier("instance");
    buildId = NPN_GetStringIdentifier("buildId");
    description = NPN_GetStringIdentifier("description");

    nsAvatarPosition = nullptr;
    nsAvatarFront = nullptr;
    nsAvatarTop = nullptr;
    nsCameraPosition = nullptr;
    nsCameraFront = nullptr;
    nsCameraTop = nullptr;
}

nsScriptableObjectOverwolfGW2::~nsScriptableObjectOverwolfGW2(void) {
}

bool nsScriptableObjectOverwolfGW2::Init() {
    return true;
}

bool nsScriptableObjectOverwolfGW2::HasProperty(NPIdentifier name) {
    return name == uiVersion ||
           name == uiTick ||
           name == fAvatarPosition ||
           name == fAvatarFront ||
           name == fAvatarTop ||
           name == this->name ||
           name == fCameraPosition ||
           name == fCameraFront ||
           name == fCameraTop ||
           name == identity ||
           name == serverAddress ||
           name == mapId ||
           name == mapType ||
           name == shardId ||
           name == instance ||
           name == buildId ||
           name == description;
}

bool nsScriptableObjectOverwolfGW2::GetProperty(NPIdentifier name, NPVariant *result) {
    #define COORDINATE_TO_NPVARIANT(name) \
        if (ns##name == nullptr) { \
            LogMessage(L"Creating nsCoordinate for " L#name L": %p", &link.pointer->f##name); \
            ns##name = (nsCoordinate *)NPN_CreateObject(npp, GET_NPOBJECT_CLASS(nsCoordinate)); \
            NPN_RetainObject(ns##name); \
            ns##name->Init(&link.pointer->f##name); \
        } \
        OBJECT_TO_NPVARIANT(ns##name, *result);

    char* buf;

    if (name == uiVersion) {
        INT32_TO_NPVARIANT(link.pointer->uiVersion, *result);
        return true;
    }

    if (name == uiTick) {
        INT32_TO_NPVARIANT(link.pointer->uiTick, *result);
        return true;
    }

    if (name == fAvatarPosition) {
        COORDINATE_TO_NPVARIANT(AvatarPosition);
        return true;
    }

    if (name == fAvatarFront) {
        COORDINATE_TO_NPVARIANT(AvatarFront);
        return true;
    }

    if (name == fAvatarTop) {
        COORDINATE_TO_NPVARIANT(AvatarTop);
        return true;
    }

    if (name == this->name) {
        EncodeUTF8(link.pointer->name, &buf);
        STRINGZ_TO_NPVARIANT(buf, *result);
        return true;
    }

    if (name == fCameraPosition) {
        COORDINATE_TO_NPVARIANT(CameraPosition);
        return true;
    }

    if (name == fCameraFront) {
        COORDINATE_TO_NPVARIANT(CameraFront);
        return true;
    }

    if (name == fCameraTop) {
        COORDINATE_TO_NPVARIANT(CameraTop);
        return true;
    }

    if (name == identity) {
        EncodeUTF8(link.pointer->identity, &buf);
        STRINGZ_TO_NPVARIANT(buf, *result);
        return true;
    }

    if (name == serverAddress) {
        uint16_t sa_family = *(uint16_t*)&link.pointer->context.serverAddress;
        buf = (char*)NPN_MemAlloc(INET6_ADDRSTRLEN);

        if (sa_family == AF_INET) {
            inet_ntop(AF_INET, &link.pointer->context.serverAddress.sin.sin_addr, buf, INET6_ADDRSTRLEN);
        } else if (sa_family == AF_INET6) {
            inet_ntop(AF_INET6, &link.pointer->context.serverAddress.sin6.sin6_addr, buf, INET6_ADDRSTRLEN);
        } else {
            *buf = '\0';
        }

        STRINGZ_TO_NPVARIANT(buf, *result);
        return true;
    }

    if (name == mapId) {
        INT32_TO_NPVARIANT(link.pointer->context.mapId, *result);
        return true;
    }

    if (name == mapType) {
        INT32_TO_NPVARIANT(link.pointer->context.mapType, *result);
        return true;
    }

    if (name == shardId) {
        INT32_TO_NPVARIANT(link.pointer->context.shardId, *result);
        return true;
    }

    if (name == instance) {
        INT32_TO_NPVARIANT(link.pointer->context.instance, *result);
        return true;
    }

    if (name == buildId) {
        INT32_TO_NPVARIANT(link.pointer->context.buildId, *result);
        return true;
    }

    if (name == description) {
        EncodeUTF8(link.pointer->description, &buf);
        STRINGZ_TO_NPVARIANT(buf, *result);
        return true;
    }

    return false;
}
