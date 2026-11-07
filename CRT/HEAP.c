#include "CRT_CORE.h"
#include "CRT_MACROS.h"
#include "HEAP.h"
#include "stdlib.h"
#include <intrin.h>
#include "stdint.h"
uint64_t __CRT_HEAP_LOCK = 0;
 typedef struct __CRT_HEAP_NODE __CRT_HEAP_NODE;
 typedef struct __CRT_MEMORY_NODE __CRT_MEMORY_NODE;
#pragma warning(push)
#pragma warning(disable: 4820)
/// <summary>
/// header for a region of bytes
/// </summary>
typedef struct  __CRT_MEMORY_NODE {
	  __CRT_MEMORY_NODE* prev;
	  __CRT_MEMORY_NODE* next;
	  __CRT_HEAP_NODE* parrent;
	size_t size;//counts from *data
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
#pragma warning(pop)
Tuple(__CRT_MEMORY_NODE, __CRT_MEMORY_NODE*, __CRT_MEMORY_NODE*);


/// <summary>
/// splits node int two nodes. the first node will be sizeBytes big, returns a tuple of the first and second node.
/// </summary>
/// <param name="node"></param>
/// <param name="sizeBytes"></param>
/// <returns></returns>
static __CRT_MEMORY_NODE_Tuple SplitHeapNode(__CRT_MEMORY_NODE* node, size_t sizeBytes) {
	__assume(node != NULL);
	__assume(node->size >= sizeBytes + sizeof(__CRT_MEMORY_NODE));
	if (node->prev == NULL && node->next == NULL) {
		__CRT_MEMORY_NODE* newNodeSecond = (__CRT_MEMORY_NODE*)((char*)node + sizeBytes + sizeof(__CRT_MEMORY_NODE));
		newNodeSecond->prev = node;
		newNodeSecond->next = node->next;
		newNodeSecond->size = (node->size - sizeBytes) - sizeof(__CRT_MEMORY_NODE);
		newNodeSecond->parrent = node->parrent;
		newNodeSecond->isFree = true;
		newNodeSecond->data = NULL;
		node->next = newNodeSecond;
		node->size = sizeBytes;
		node->isFree = true;
		node->data = NULL;
		return (__CRT_MEMORY_NODE_Tuple){ node,newNodeSecond };
		

	}

}

