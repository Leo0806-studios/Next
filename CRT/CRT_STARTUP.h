#pragma once
//#include "stdbool.h"

#include "CRT_MACROS.h"
#include "CRT_CORE.h"
#include "stdint.h"
#include "wchar.h"
__CRT_START

#pragma warning(push)
#pragma warning(disable: __DISABLE_CRT_WARNINGS)

typedef enum __CRT_API_ERROR:uint64_t {
	__CRT_SUCCESS = 0,
	__CRT_OUT_OF_MEMORY = 1,
	__CRT_INVALID_ARGUMENT = 2,
	__CRT_STREAM_ERROR = 3,
	__CRT_STREAM_NOT_FOUND = 4,
	__CRT_INVALID_HANDLE = 5,
	__CRT_STREAM_READ_ERROR = 6,
	__CRT_STREAM_WRITE_ERROR = 7,
	__CRT_STREAM_ALREADY_EXISTS = 8,
	__CRT_MEMORY_FREE_FAILIURE=9
}__CRT_API_ERROR;


typedef struct __CRT_OS_SIGNAL_TABLE {
	__int64 SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM;
} __CRT_OS_SIGNAL_TABLE;
typedef struct __CRT_OS_API_RETURN_VPTR {
	__CRT_API_ERROR code;
	void* value;
}__CRT_OS_API_RETURN_VPTR;
typedef struct __CRT_OS_API_RETURN_BOOL {
	__CRT_API_ERROR code;
	bool value;
}__CRT_OS_API_RETURN_BOOL;
typedef struct __CRT_OS_API_RETURN_SIZE_T {
	__CRT_API_ERROR code;
	size_t value;

}__CRT_OS_API_RETURN_SIZE_T;
typedef struct __CRT_OS_CALLBACKS
{
	
	__CRT_API_ERROR(*TerminateProcess)(int exitCode);
	__CRT_OS_API_RETURN_VPTR (*createThread)(void(*startAddress)(void*), void* arg);
	__CRT_API_ERROR(*joinThread)(void* threadHandle);
	__CRT_API_ERROR(*terminateThread)(void* threadHandle);
	__CRT_OS_API_RETURN_VPTR(*allocatePage)(void) ;
	__CRT_OS_API_RETURN_VPTR(*allocatePages)(size_t amountOfPages) ;
	__CRT_API_ERROR(*freePage)(void* ptr) ;
	__CRT_API_ERROR(*freePages)(void* ptr) ;
	__CRT_OS_API_RETURN_VPTR (*openStream)(const char* path,uint64_t flags) ;
	__CRT_API_ERROR  (*closeStream)(void* handle);
	__CRT_OS_API_RETURN_SIZE_T(*read)(void* handle, void* buffer, size_t size) ;
	__CRT_OS_API_RETURN_SIZE_T(*write)(void* handle, const void* buffer, size_t size) ;
	__CRT_API_ERROR (*readW)(const wchar_t* str) ;
	__CRT_API_ERROR(*writeW)(const wchar_t* str) ;
} __CRT_OS_CALLBACKS;

typedef struct __CRT_INIT_PARAMETERS {
	__CRT_OS_CALLBACKS callbacks;
	bool callMain;
}__CRT_INIT_PARAMETERS;
void TerminateProcess(int exitCode);
/// <summary>
/// allocates a single 4KiB page.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void* AllocatePage(void);
/// <summary>
/// Allocates a contiguose region of 4KiB pages
/// </summary>
/// <param name="amountOfPages"></param>
/// <returns></returns>
void* AllocatePages(size_t amountOfPages);
/// <summary>
/// Frees a page allocated with AllocatePage. passing a pointer not allocated with it may lead to undefined behaviour
/// </summary>
/// <param name="ptr"></param>
/// <returns></returns>
bool FreePage(void* ptr);

/// <summary>
/// frees a region of pages allocated wiht AllocatePages. passing a pointer not allocated with this may lead to undefined behaviour.
/// </summary>
/// <param name="ptr"></param>
/// <returns></returns>
bool FreePages(void* ptr);

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
/// <summary>
/// Writes "size" bytes of data to the stream. the exact behaviour depends on the flags with which the stream was opened
/// </summary>
/// <param name="handle"></param>
/// <param name="buffer"></param>
/// <param name="size"></param>
/// <returns></returns>
size_t Write(void* handle, const void* buffer, size_t size);
typedef int(*mainFunc)(int, char**) ;
/// <summary>
/// main entrypoint of the program. calls main if defined in th init parameters the return is the return value of main. otherwise it is zero
/// </summary>
/// <param name="params"></param>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int __MainCRTStartup(__CRT_INIT_PARAMETERS* params, int argc, char** argv);
#pragma warning(pop)
__CRT_END