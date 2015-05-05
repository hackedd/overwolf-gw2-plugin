/*
    Overwolf Guild Wars 2 Mumble Link Plugin
    Copyright (c) 2015 Paul Hooijenga
*/

#ifndef UTILS_LOG_H_
#define UTILS_LOG_H_

#include <Windows.h>
#include <strsafe.h>

void LogMessage(const wchar_t* format, ...);
void LogLastError(const wchar_t* prefix);

#define _U(t) L##t
#define U(t) _U(t)

#endif
