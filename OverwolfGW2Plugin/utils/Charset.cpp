#include "Charset.h"

int DecodeUTF8(char* src, size_t length, wchar_t** dst) {
    int required = MultiByteToWideChar(CP_UTF8, 0, src, length, 0, 0);

    if (dst != nullptr) {
        *dst = new wchar_t[required];
        MultiByteToWideChar(CP_UTF8, 0, src, length, *dst, required);
    }

    return required;
}

int DecodeUTF8(char* src, size_t length, wchar_t* dst, size_t dstSize) {
    return MultiByteToWideChar(CP_UTF8, 0, src, length, dst, dstSize);
}

int EncodeUTF8(wchar_t* src, size_t length, char** dst) {
    int required = WideCharToMultiByte(CP_UTF8, 0, src, length, nullptr, 0, nullptr, nullptr);

    if (dst != nullptr) {
        *dst = (char*)NPN_MemAlloc(required);
        WideCharToMultiByte(CP_UTF8, 0, src, length, *dst, required, nullptr, nullptr);
    }

    return required;
}

int EncodeUTF8(wchar_t* src, char** dst) {
    int required = WideCharToMultiByte(CP_UTF8, 0, src, -1, nullptr, 0, nullptr, nullptr);

    if (dst != nullptr) {
        *dst = (char*)NPN_MemAlloc(required);
        WideCharToMultiByte(CP_UTF8, 0, src, -1, *dst, required, nullptr, nullptr);
    }

    return required;
}

int EncodeUTF8(wchar_t* src, size_t length, char* dst, size_t dstSize) {
    return WideCharToMultiByte(CP_UTF8, 0, src, length, dst, dstSize, nullptr, nullptr);
}

int EncodeUTF8(wchar_t* src, char* dst, size_t dstSize) {
    return WideCharToMultiByte(CP_UTF8, 0, src, -1, dst, dstSize, nullptr, nullptr);
}
