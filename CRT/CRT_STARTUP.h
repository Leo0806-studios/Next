#pragma once
//#include "stdbool.h"

#include "CRT_MACROS.h"
#include "CRT_CORE.h"
#include "stdint.h"
#include "wchar.h"
__CRT_START
#pragma warning(push)
#pragma warning(disable: __DISABLE_CRT_WARNINGS)

typedef enum __CRT_API_ERROR {
	__CRT_SUCCESS = 0,
	__CRT_OUT_OF_MEMORY = 1,
	__CRT_INVALID_ARGUMENT = 2,
	__CRT_STREAM_ERROR = 3,
	__CRT_STREAM_NOT_FOUND = 4,
	__CRT_INVALID_HANDLE = 5,
	__CRT_STREAM_READ_ERROR = 6,
	__CRT_STREAM_WRITE_ERROR = 7,
	__CRT_STREAM_ALREADY_EXISTS = 8,
}__CRT_API_ERROR;
typedef struct __CRT_OS_SIGNAL_TABLE {
	__int64 SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM;
} __CRT_OS_SIGNAL_TABLE;
typedef struct __CRT_OS_CALLBACKS
{
	
	void(*TerminateProcess)(int exitCode);
	void* (*createThread)(void(*startAddress)(void*), void* arg);
	void(*joinThread)(void* threadHandle);
	void(*terminateThread)(void* threadHandle);
	void* (*alocatePage)(void) ;
	void* (*allocatePages)(size_t amountOfPages) ;
	bool (*freePage)(void* ptr) ;
	bool(*freePages)(void* ptr) ;
	void* (*openStream)(const char* path,uint64_t flags) ;
	void  (*closeStream)(void* handle);
	size_t(*read)(void* handle, void* buffer, size_t size) ;
	size_t(*write)(void* handle, const void* buffer, size_t size) ;
	void (*readW)(const wchar_t* str) ;
	void (*writeW)(const wchar_t* str) ;
} __CRT_OS_CALLBACKS;
typedef enum __CRT_MAIN_STATE {
	e_minMain,
	e_main,
	e_halfMainRet,
	e_halfMainParams
}__CRT_MAIN_STATE;
	typedef union __CRT_MAIN_HOLDER {
		void(*minMain)(void);
		int(*main)(int, char**);
		int (*halfMainRet)(void);
		int(*halfMainParams)(int, char**);
	} __CRT_MAIN_HOLDER;
typedef struct __CRT_MAIN_INFO {
	__CRT_MAIN_HOLDER main;
	__CRT_MAIN_STATE state;

}__CRT_MAIN_INFO;
typedef struct __CRT_INIT_PARAMETERS {
	__CRT_OS_CALLBACKS callbacks;
	__CRT_MAIN_INFO mainInfo;
}__CRT_INIT_PARAMETERS;
void TerminateProcess(int exitCode);
void* AlocatePage(void);
void* AllocatePages(size_t amountOfPages);
bool FreePage(void* ptr);

/// <summary>
/// opens a Stream and returns a handle to it. The flags parameter is a bitmask that specifies the access mode and other options for the Stream. The following flags are defined:
/// </summary>
/// <param name="path"></param>
/// <param name="flags"></param>
/// <returns></returns>
void* OpenStream(const char* path,uint64_t flags);

/// <summary>
/// Closes a Stream handle that was previously opened with OpenStream.
/// </summary>
/// <param name="handle"></param>
void CloseStream(void* handle);

/// <summary>
/// Reads "size" bytes of data from the Stream handle into the buffer pointed to by "buffer". 
/// </summary>
/// <param name="handle"></param>
/// <param name="buffer"></param>
/// <param name="size"></param>
/// <returns></returns>
size_t Read(void* handle, void* buffer, size_t size);
size_t Write(void* handle, const void* buffer, size_t size);
void WriteW(const wchar_t* str);
void ReadW(const wchar_t* str);
bool __MainCRTStartup(__CRT_INIT_PARAMETERS* params, int argc, char** argv);
#pragma warning(pop)
__CRT_END