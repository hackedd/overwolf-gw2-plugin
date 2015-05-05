/*
    Overwolf Guild Wars 2 Mumble Link Plugin
    Copyright (c) 2015 Paul Hooijenga
*/

#ifndef NS_COORDINATE_H_
#define NS_COORDINATE_H_

#include "nsScriptableObjectBase.h"
#include "MumbleLink.h"

class nsCoordinate : public nsScriptableObjectBase {
private:
    Coordinate* c;
    NPIdentifier x, y, z;

public:
    nsCoordinate(NPP npp);
    ~nsCoordinate();
    void Init(Coordinate* c);

    virtual bool HasProperty(NPIdentifier name) override;
    virtual bool GetProperty(NPIdentifier name, NPVariant *result) override;
};

DECLARE_NPOBJECT_CLASS_WITH_BASE(nsCoordinate);

#endif
