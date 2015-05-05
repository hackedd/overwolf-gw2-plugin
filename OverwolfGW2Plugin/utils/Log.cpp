#include "Log.h"

LPWSTR GetLastErrorMessage()
{
    LPWSTR lpMsgBuf;
    DWORD error = GetLastError();

    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                   FORMAT_MESSAGE_FROM_SYSTEM |
                   FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                   (LPWSTR)&lpMsgBuf, 0, NULL);

    return lpMsgBuf;
}

void LogLastError(const wchar_t* prefix) {
    wchar_t* error = GetLastErrorMessage();

    if (prefix == nullptr) {
        LogMessage(L"%s", error);
    } else {
        LogMessage(L"%s: %sb ", prefix, error);
    }

    LocalFree(error);
}

void LogMessage(const wchar_t* format, ...) {
    static wchar_t buffer[4096];
    wchar_t *p = buffer;
    size_t remaining = ARRAYSIZE(buffer) - 1;
    int len;
    va_list args;

    len = GetDateFormatEx(LOCALE_NAME_INVARIANT, 0, NULL, L"yyyy-MM-dd", p, remaining, NULL);
    p += len - 1;
    *p++ = L' ';
    remaining -= len;

    len = GetTimeFormatEx(LOCALE_NAME_INVARIANT, 0, NULL, L"HH:mm:ss", p, remaining);
    p += len - 1;
    *p++ = L' ';
    remaining -= len;

    va_start(args, format);
    StringCchVPrintfW(p, remaining, format, args);
    va_end(args);

    OutputDebugStringW(buffer);
}
