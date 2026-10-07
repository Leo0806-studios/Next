#pragma once
#include <CRT_STARTUP.h>
#include <CRT_MACROS.h>
__CRT_START
typedef struct __CXX_EXTENDED_OS_CALLBACKS {
	uint64_t placeholder;

} __CXX_EXTENDED_OS_CALLBACKS;;

typedef struct __CXX_SECTION_INFO { //NOSONAR
	size_t offset;
	size_t size;
} __CXX_SECTION_INFO;

typedef struct __CXX_LOADED_IMAGE_INFO {//NOSONAR
	void* imageBaseAddress;
	size_t imageSize;
	__CXX_SECTION_INFO text;
	__CXX_SECTION_INFO data;
	__CXX_SECTION_INFO bss;
	__CXX_SECTION_INFO rdata;
	__CXX_SECTION_INFO pdata;
	__CXX_SECTION_INFO xdata;

} __CXX_LOADED_IMAGE_INFO;//NOLINT



typedef struct __CXX_RUNTIME_INIT_PARAMETERS {//NOSONARs
	__CRT_OS_CALLBACKS callbacks;
	__CXX_EXTENDED_OS_CALLBACKS extendedCallbacks;
	size_t initialHeapSize;
	void* imageBaseAddress;
	__CXX_LOADED_IMAGE_INFO loadedImageInfo;
	__CRT_MAIN_INFO mainInfo;
} __CXX_RUNTIME_INIT_PARAMETERS; 

void __MAIN_CXX_RUNTIME_INIT(__CXX_RUNTIME_INIT_PARAMETERS* params);
const __CXX_RUNTIME_INIT_PARAMETERS* __Cxx_params_singleton(__CXX_RUNTIME_INIT_PARAMETERS* params);
__CRT_END