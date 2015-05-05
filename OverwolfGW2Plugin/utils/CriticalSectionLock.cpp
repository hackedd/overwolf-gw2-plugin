/*
  Overwolf GW2 Plugin
  Copyright (c) 2014 Ovefwolf Ltd.
*/
#include "CriticalSectionLock.h"

using namespace utils;

CriticalSection::CriticalSection() {
    InitializeCriticalSection(&critical_section);
}

CriticalSection::~CriticalSection() {
    DeleteCriticalSection(&critical_section);
}

void CriticalSection::lock() {
    EnterCriticalSection(&critical_section);
}

void CriticalSection::unlock() {
    LeaveCriticalSection(&critical_section);
}

CriticalSectionLock::CriticalSectionLock(CriticalSection& criticalSection) : critical_section(criticalSection) {
    critical_section.lock();
}

CriticalSectionLock::~CriticalSectionLock() {
    critical_section.unlock();
}
