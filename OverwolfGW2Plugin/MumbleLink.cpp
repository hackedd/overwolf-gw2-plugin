/*
    Overwolf Guild Wars 2 Mumble Link Plugin
    Copyright (c) 2015 Paul Hooijenga
*/

#include "MumbleLink.h"
#include "utils/Log.h"

MumbleLink::MumbleLink() {
    hMapObject = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, MUMBLE_LINK_NAME);

    if (hMapObject == nullptr) {
        LogLastError(L"OpenFileMapping");
        /* If the mapping does not exist, try to create it. */
        hMapObject = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(LinkedMem), MUMBLE_LINK_NAME);
    }

    if (hMapObject == nullptr) {
        pointer = nullptr;
    } else {
        pointer = (LinkedMem*)MapViewOfFile(hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(LinkedMem));
        if (pointer == nullptr) {
            LogLastError(L"MapViewOfFile");
        }
    }

    LogMessage(L"hMapObject: %p; pointer: %p", hMapObject, pointer);
}

MumbleLink::~MumbleLink() {
    if (pointer != nullptr) {
        UnmapViewOfFile(pointer);
    }

    if (hMapObject != nullptr) {
        CloseHandle(hMapObject);
    }
}
