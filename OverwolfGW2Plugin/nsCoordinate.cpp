/*
    Overwolf Guild Wars 2 Mumble Link Plugin
    Copyright (c) 2015 Paul Hooijenga
*/

#include "nsCoordinate.h"
#include "utils/Log.h"

nsCoordinate::nsCoordinate(NPP npp) : nsScriptableObjectBase(npp) {
    x = NPN_GetStringIdentifier("x");
    y = NPN_GetStringIdentifier("y");
    z = NPN_GetStringIdentifier("z");
}

nsCoordinate::~nsCoordinate() {
}

void nsCoordinate::Init(Coordinate *c) {
    this->c = c;
}

bool nsCoordinate::HasProperty(NPIdentifier name) {
//    NPUTF8* n = NPN_UTF8FromIdentifier(name);
//    LogMessage(L"nsCoordinate::HasProperty: %hs", n);
//    NPN_MemFree(n);

    return name == x || name == y || name == z;
}

bool nsCoordinate::GetProperty(NPIdentifier name, NPVariant *result) {
//    NPUTF8* n = NPN_UTF8FromIdentifier(name);
//    LogMessage(L"nsCoordinate::GetProperty: %hs (%p)", n, c);
//    NPN_MemFree(n);

    if (name == x) {
        DOUBLE_TO_NPVARIANT(c->x, *result);
        return true;
    }
    if (name == y) {
        DOUBLE_TO_NPVARIANT(c->y, *result);
        return true;
    }
    if (name == z) {
        DOUBLE_TO_NPVARIANT(c->z, *result);
        return true;
    }
    return false;
}
