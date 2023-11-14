#ifndef __TMEMORYHEAP_H__
#define __TMEMORYHEAP_H__

// Heaped memory, stored as a linked list of allocations.

#ifndef __ALLOCAHEADER_H__
#include "TAllocHeader.h"
#endif

#ifndef __TMEMORYCHUNKINTERFACE_H__
#include "TMemoryChunkInterface.h"
#endif

class TMemoryHeap : public TMemoryChunkInterface
{
public:
	void  Initialize();

	void* Allocate(size_t bytes);

	void* AllocateDebug(size_t bytes, const char* file = "", int line=0);

	void  FreeMemory(TAllocHeader* header);

	void  Activate(unsigned int id);

	void  Deactivate();

	int  PrintAllocations(TStreamInterface* stream);

private:
	void* InternalAllocate(size_t bytes, TAllocHeader*& header);

	TAllocHeader * m_headAlloc;
};

#endif
