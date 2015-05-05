#ifndef UTILS_CHARSET_H_
#define UTILS_CHARSET_H_

#include <Windows.h>
#include <npapi.h>

int DecodeUTF8(char* src, size_t length, wchar_t** dst);
int DecodeUTF8(char* src, size_t length, wchar_t* dst, size_t dstSize);
int EncodeUTF8(wchar_t* src, size_t length, char** dst);
int EncodeUTF8(wchar_t* src, char** dst);
int EncodeUTF8(wchar_t* src, size_t length, char* dst, size_t dstSize);
int EncodeUTF8(wchar_t* src, char* dst, size_t dstSize);

#endif
