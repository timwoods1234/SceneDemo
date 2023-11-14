#ifndef __TALLOCHEADER_H__
#define __TALLOCHEADER_H__

// Allocation header that precedes all memory allocations.

class TMemoryChunkInterface;

struct TAllocHeader
{
	int allocNum;
	int size;

	TMemoryChunkInterface* chunk;	

	// for pooled memory
	unsigned int memIndex;

	// for heaped memory
	TAllocHeader* next;
	TAllocHeader* prev;

#if defined(DEBUG) | defined(_DEBUG)
	char file[64];
	int lineNumber;
#endif

};

#endif
