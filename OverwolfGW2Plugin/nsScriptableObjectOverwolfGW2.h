/*
    Overwolf Guild Wars 2 Mumble Link Plugin
    Copyright (c) 2015 Paul Hooijenga
*/

#ifndef NNSSCRIPTABLEOBJECTOVERWOLFGW2_H_
#define NNSSCRIPTABLEOBJECTOVERWOLFGW2_H_

#include "nsScriptableObjectBase.h"
#include "MumbleLink.h"
#include "nsCoordinate.h"

class nsScriptableObjectOverwolfGW2 : public nsScriptableObjectBase {

public:
    nsScriptableObjectOverwolfGW2(NPP npp);
    virtual ~nsScriptableObjectOverwolfGW2(void);
    bool Init();

    virtual bool HasProperty(NPIdentifier name) override;
    virtual bool GetProperty(NPIdentifier name, NPVariant *result) override;

private:
    MumbleLink link;

    NPIdentifier uiVersion;
    NPIdentifier uiTick;
    NPIdentifier fAvatarPosition;
    NPIdentifier fAvatarFront;
    NPIdentifier fAvatarTop;
    NPIdentifier name;
    NPIdentifier fCameraPosition;
    NPIdentifier fCameraFront;
    NPIdentifier fCameraTop;
    NPIdentifier identity;
    NPIdentifier serverAddress;
    NPIdentifier mapId;
    NPIdentifier mapType;
    NPIdentifier shardId;
    NPIdentifier instance;
    NPIdentifier buildId;
    NPIdentifier description;

    nsCoordinate* nsAvatarPosition;
    nsCoordinate* nsAvatarFront;
    nsCoordinate* nsAvatarTop;
    nsCoordinate* nsCameraPosition;
    nsCoordinate* nsCameraFront;
    nsCoordinate* nsCameraTop;

};

DECLARE_NPOBJECT_CLASS_WITH_BASE(nsScriptableObjectOverwolfGW2);

#endif
