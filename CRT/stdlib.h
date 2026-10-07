#pragma once
#ifndef __STDLIB__
#define __STDLIB__
#include "ThreadingSharedSymbols.h"
#include "CRT_CORE.h"
#include "CRT_MACROS.h"
typedef struct _div_t
{
	int quot;
	int rem;
} div_t;

typedef struct _ldiv_t
{
	long quot;
	long rem;
} ldiv_t;

typedef struct _lldiv_t
{
	long long quot;
	long long rem;
} lldiv_t;
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define RAND_MAX 0x7fff
double atof(const char* str);
int atoi(const char* nptr);
long int atol(const char* nptr);
long long int atoll(const char* nptr);

//fuck this. ill bother with this later
//TODO: implement these functions
int strfromd(char* restrict s, size_t n, const char* restrict format,
	double fp);
int strfromf(char* restrict s, size_t n, const char* restrict format,
	float fp);
int strfroml(char* restrict s, size_t n, const char* restrict format,
	long double fp);

#ifdef __STDC_IEC_60559_DFP__
int strfromd32(char* restrict s, size_t n, const char* restrict format,
	_Decimal32 fp);
int strfromd64(char* restrict s, size_t n, const char* restrict format,
	_Decimal64 fp);
int strfromd128(char* restrict s, size_t n, const char* restrict format,
	_Decimal128 fp);
#endif

double strtod(const char* restrict nptr, char** restrict endptr);
float strtof(const char* restrict nptr, char** restrict endptr);
long double strtold(const char* restrict nptr, char** restrict endptr);

#ifdef __STDC_IEC_60559_DFP__
_Decimal32 strtod32(const char* restrict nptr, char** restrict endptr);
_Decimal64 strtod64(const char* restrict nptr, char** restrict endptr);
_Decimal128 strtod128(const char* restrict nptr, char** restrict endptr);
#endif





long  strtol(const char* restrict nptr, char** restrict endptr, int base);
long long  strtoll(const char* restrict nptr, char** restrict endptr, int base);
unsigned long  strtoul(const char* restrict nptr, char** restrict endptr, int base);
unsigned long long  strtoull(const char* restrict nptr, char** restrict endptr, int base);

int rand(void);
void srand(unsigned int seed);

void* aligned_alloc(size_t alignment, size_t size);
void* calloc(size_t nmemb, size_t size);
void free(void* ptr);
void free_sized(void* ptr, size_t size);
void free_aligned_sized(void* ptr, size_t alignment, size_t size);
void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
__CRT_NORETURN void abort(void);

int atexit(void_void_func func);
int at_quick_exit(void_void_func func);
__CRT_NORETURN void exit(int status);
__CRT_NORETURN void _Exit(int status);

/// <summary>
/// getenv() extension
/// when "name" is null getenv() performs a capability query 
///		if the returned value is NULL, envoironment variables are not supported
///		if the returned value is not NULL,enviroment variables are supported
/// for any other argument, getenv() behaves as normal
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
char* getenv(const char* name);
__CRT_NORETURN void quick_exit(int status);
int system(const char* string);
#ifndef __cplusplus
void* bsearch(const void* key, void* base, size_t nmemb, size_t size,	int (*compar)(const void*, const void*)); //yeah im sadly not compliant here
#else
template <typename T>
T* bsearch(const T* key, T* base, size_t nmemb, int (*compar)(const T*, const T*))
{
	return (T*)bsearch((const void*)key, (void*)base, nmemb, sizeof(T), (int (*)(const void*, const void*))compar);
}
#endif
void qsort(void* base, size_t nmemb, size_t size,	int (*compar)(const void*, const void*));


int abs(int j);
long int labs(long int j);
long long int llabs(long long int j);
div_t div(int numer, int denom);
ldiv_t ldiv(long int numer, long int denom);
lldiv_t lldiv(long long int numer, long long int denom);

int mblen(const char* s, size_t n);
int mbtowc(wchar_t* restrict pwc, const char* restrict s, size_t n);	
int wctomb(char* s, wchar_t wc);

size_t mbstowcs(wchar_t* restrict pwcs, const char* restrict s, size_t n);
size_t wcstombs(char* restrict s, const wchar_t* restrict pwcs, size_t n);
size_t memalignment(const void* p);

#endif // !__STDLIB__
