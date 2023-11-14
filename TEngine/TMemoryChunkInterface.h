#ifndef __TMEMORYCHUNKINTERFACE_H__
#define __TMEMORYCHUNKINTERFACE_H__

// Base class for an area of memory.
// Extended for memory pool and heap.

#ifndef __TALLOCHEADER_H__
#include "TAllocHeader.h"
#endif

class TStreamInterface;

class TMemoryChunkInterface
{
public:
	static void   Deallocate(void* mem);

	static int    GetMemoryBookmark();

	static const  char* TraceToSource(TAllocHeader* header);

	virtual void* AllocateDebug(size_t bytes, const char* file = "", int line = 0) = 0;

	virtual void* Allocate(size_t bytes) = 0;

	virtual void  FreeMemory(TAllocHeader* header) = 0;

	virtual void  Deactivate() = 0;

	virtual int  PrintAllocations(TStreamInterface* stream) = 0;

	bool		IsActive() const;

	unsigned int GetID() const;

	size_t		GetBytesAllocated() const;

protected:
	bool m_active;
	unsigned int m_id;

	size_t m_bytesAllocated;
	size_t m_bytesPeak;

	int m_instances;

	static int s_nextAllocNum;
};

#endif
