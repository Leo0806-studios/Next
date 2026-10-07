#include "CRT_CORE.h"
#include "CRT_MACROS.h"
#include "HEAP.h"
#include "stdlib.h"
struct __CRT_HEAP_NODE;
/// <summary>
/// header for a region of bytes
/// </summary>
typedef struct  __CRT_MEMORY_NODE {
	__CRT_MEMORY_NODE* prev;
	__CRT_MEMORY_NODE* next;
	__CRT_HEAP_NODE* parrent;
	size_t size;
	void* data;
	bool isFree;
} __CRT_MEMORY_NODE;

/// <summary>
/// header for a collection of pages 
/// </summary>
typedef struct __CRT_HEAP_NODE {
	__CRT_HEAP_NODE* prev;
	__CRT_HEAP_NODE* next;
	size_t sizePages;
	__CRT_MEMORY_NODE* first;
	__CRT_MEMORY_NODE* last;
	size_t freeBytes;
	size_t usedSize;
} __CRT_HEAP_NODE;
typedef struct __CRT_HEAP {
	__CRT_HEAP_NODE* first;
	__CRT_HEAP_NODE* last;
	size_t totalSize;
	size_t usedSize;
} __CRT_HEAP;

__CRT_HEAP heap;
Tuple(__CRT_HEAP_NODE, __CRT_HEAP_NODE*, __CRT_HEAP_NODE*);



static __CRT_HEAP_NODE_Tuple SplitHeapNode(__CRT_HEAP_NODE* node, size_t sizeBytes) {
	__assume(node != nullptr);
	if (node->prev == NULL && node->next == NULL) {
		__CRT_HEAP_NODE* newNodeSecond = (__CRT_HEAP_NODE*)((char*)node + sizeBytes + sizeof(__CRT_HEAP_NODE));
	}

}

