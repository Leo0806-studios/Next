#pragma once
#include <CRT_STARTUP.h>
typedef struct __CXX_RUNTIME_INIT_PARAMETERS {
	__CRT_OS_CALLBACKS callbacks;
	size_t initialHeapSize;
	void* imageBaseAddress;
} __CXX_RUNTIME_INIT_PARAMETERS;