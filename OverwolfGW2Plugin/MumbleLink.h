/*
    Overwolf Guild Wars 2 Mumble Link Plugin
    Copyright (c) 2015 Paul Hooijenga
*/

#ifndef MUMBLE_LINK_H
#define MUMBLE_LINK_H

#include <stdint.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma pack(push, 1)

typedef union {
    sockaddr_in6 sin6;
    sockaddr_in sin;
} ServerAddress;

typedef struct {
    ServerAddress serverAddress;
    uint32_t mapId;
    uint32_t mapType;
    uint32_t shardId;
    uint32_t instance;
    uint32_t buildId;
} GW2Context;

typedef struct {
    float x;
    float y;
    float z;
} Coordinate;

typedef struct {
    uint32_t uiVersion;
    uint32_t uiTick;
    Coordinate fAvatarPosition;
    Coordinate fAvatarFront;
    Coordinate fAvatarTop;
    wchar_t name[256];
    Coordinate fCameraPosition;
    Coordinate fCameraFront;
    Coordinate fCameraTop;
    wchar_t identity[256];
    uint32_t contextLength;
    GW2Context context;
    uint8_t _[256 - sizeof(GW2Context)];
    wchar_t description[2048];
} LinkedMem;

#pragma pack(pop)

#define MUMBLE_LINK_NAME L"MumbleLink"

class MumbleLink
{
public:
    MumbleLink();
    ~MumbleLink();

    LinkedMem* pointer;

private:
    HANDLE hMapObject;
};

#endif
