#pragma once
#ifndef __STRING__
#define __STRING__
#include "CRT_CORE.h"
#include "CRT_MACROS.h"
__CRT_START
#pragma warning (push)
#pragma warning(disable: __DISABLE_CRT_WARNINGS)
void* memcpy(void* restrict s1, const void* restrict s2, size_t n);
void* memccpy(void* restrict s1, const void* restrict s2, int c, size_t n);
void* memmove(void* s1, const void* s2, size_t n);
char* strcpy(char* restrict s1, const char* restrict s2);
char* strncpy(char* restrict s1, const char* restrict s2, size_t n);
char* strdup(const char* s);
char* strndup(const char* s, size_t n);
char* strcat(char* restrict s1, const char* restrict s2);
char* strncat(char* restrict s1, const char* restrict s2, size_t n);
int memcmp(const void* s1, const void* s2, size_t n);
int strcmp(const char* s1, const char* s2);
int strcoll(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
size_t strxfrm(char* restrict s1, const char* restrict s2, size_t n);
#ifndef __cplusplus
void* memchr(void* s, int c, size_t n);
char* strchr(char* s, int c);
#else
template <typename T>
T* memchr(T* s, int c, size_t n) {
	return (T*)memchr((void*)s, c, n);
}
template <typename T>
T* strchr(T* s, int c) {
	return (T*)strchr((char*)s, c);
}
#endif // !__cplusplus
size_t strcspn(const char* s1, const char* s2);
#ifndef __cplusplus
char* strstr(char* s1, const char* s2);
#else
template <typename T>
T* strstr(T* s1, const char* s2) {
	return (T*)strstr((char*)s1, s2);
}
#endif // !__cplusplus
char* strtok(char* restrict s1, const char* restrict s2);
void* memset(void* s, int c, size_t n);
void* memset_explicit(void* s, int c, size_t n);
char* strerror(int errnum);
size_t strlen(const char* s);
#pragma warning (pop)

__CRT_END
#endif // !__STRING__
