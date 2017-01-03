#ifndef HEAP_MIDWARE_H
#define HEAP_MIDWARE_H
#include <stdint.h>

#define MAX_HEAP_TYPE 8

typedef enum
{
	common_heap = 1,
}HeapType_e;

typedef struct A_BLOCK_LINK_INTERGRATE
{
	struct A_BLOCK_LINK_INTERGRATE *pxNextFreeBlock;	/*<< The next free block in the list. */
	int xBlockSize;						/*<< The size of the free block. */
} BlockLinkIntergrate_t;

typedef struct
{
	unsigned char * ucHeapArray;
	BlockLinkIntergrate_t xStart; 
	BlockLinkIntergrate_t *pxEnd;
	size_t xFreeBytesRemaining;
	size_t xMinimumEverFreeBytesRemaining;
}HeapIntergrate_s;

extern HeapIntergrate_s heap_mem[];

#endif
