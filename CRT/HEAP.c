#include "CRT_CORE.h"
#include "CRT_MACROS.h"
#include "CRT_STARTUP.h"
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
static __CRT_MEMORY_NODE_Tuple SplitMemoryNode(__CRT_MEMORY_NODE* node, size_t sizeBytes) {
	__assume(node != NULL);
	__assume(node->size >= sizeBytes + sizeof(__CRT_MEMORY_NODE));
	__CRT_MEMORY_NODE* newNodeSecond = (__CRT_MEMORY_NODE*)((char*)node + sizeBytes + sizeof(__CRT_MEMORY_NODE));
	*newNodeSecond = (__CRT_MEMORY_NODE){ 0 };
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
	if (newNodeSecond->next == NULL) {
		newNodeSecond->parrent->last = newNodeSecond;
	}
	return (__CRT_MEMORY_NODE_Tuple) {
		node, newNodeSecond
	};

}
static __CRT_MEMORY_NODE* MergeMemoryNode(__CRT_MEMORY_NODE_Tuple nodes) {
	__assume(nodes.first != NULL && nodes.second != NULL);
	__assume(nodes.first->next == nodes.second && nodes.second->prev == nodes.first);
	__CRT_MEMORY_NODE* first = nodes.first;
	__CRT_MEMORY_NODE* second = nodes.second;
	first->next = second->next;
	first->size = ((uint64_t)first - (uint64_t)second) + second->size;
	first->data = NULL;
	first->isFree = true;
	if (first->next == NULL) {
		first->parrent->last = first;
	}
	return first;
}

__CRT_MEMORY_NODE* FindFittingNode(size_t size) {
	__assume(heap.first != NULL && heap.last != NULL);
	__CRT_HEAP_NODE* currentHeapNode = heap.first;

	while (true) {
		if (currentHeapNode->freeBytes - sizeof(__CRT_MEMORY_NODE*) <= size) {
			if (!currentHeapNode->next) {
				break;
			}
			currentHeapNode = currentHeapNode->next;
			continue;
		}


		__CRT_MEMORY_NODE* currentMemoryNode = currentHeapNode->first;

		while (true) {
			if (!currentMemoryNode->isFree) {
				if (!currentMemoryNode->next) {
					break;
				}
				currentMemoryNode = currentMemoryNode->next;
				continue;
			}
			if (currentMemoryNode->size < size) {
				if (!currentMemoryNode->next) {
					break;
				}
				currentMemoryNode = currentMemoryNode->next;
				continue;
			}

			if (currentMemoryNode->size == size || (currentMemoryNode->size - sizeof(__CRT_MEMORY_NODE))<size) {
				return currentMemoryNode;
			}
			
			return SplitMemoryNode(currentMemoryNode, size).first;
			if (!currentMemoryNode->next) {
				break;
			}
			currentMemoryNode = currentMemoryNode->next;
		}
		if (!currentHeapNode->next) {
			break;
		}
		currentHeapNode = currentHeapNode->next;
	}
	return NULL;
}

__CRT_MEMORY_NODE* AllocateNew(size_t size) {
	const size_t roundToNextPageMultiple = ((size + sizeof(__CRT_HEAP_NODE) + sizeof(__CRT_MEMORY_NODE)) + __CRT_PAGE_SIZE - 1) - (((size+sizeof(__CRT_HEAP_NODE)+sizeof(__CRT_MEMORY_NODE))+__CRT_PAGE_SIZE - 1) % __CRT_PAGE_SIZE);
	void* data = NULL;
	if (roundToNextPageMultiple == __CRT_PAGE_SIZE) {
		data=AllocatePage();
	}
	else {
		data=AllocatePages(size % __CRT_PAGE_SIZE);
	}



}
void* malloc(size_t size) {
	__CRT_MEMORY_NODE* node = FindFittingNode(size);
	if (!node) {
		node = AllocateNew(size);
	}
	if (!node) {
		return NULL;
	}
	node->isFree = false;
	node->data = ((char*)node) + sizeof(__CRT_MEMORY_NODE*);
	return node->data;
	

}
