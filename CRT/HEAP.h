#pragma once
#ifndef __HEAP__


#include "CRT_CORE.h"
#include "CRT_MACROS.h"

__CRT_START
/// <summary>
/// Creates the ProgramHeap with a initial size.
/// InitSize is in pages.
/// when 0 it will create with one page
/// </summary>
/// <param name="initSize"></param>
/// <returns></returns>
bool CreateHeap(size_t initSize);
__CRT_END
#endif // !__HEAP__