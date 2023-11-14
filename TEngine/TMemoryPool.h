#ifndef __TMEMORYPOOL_H__
#define __TMEMORYPOOL_H__

// A contiguous block of memory to be used as a pool.
// Pool block size can be arbitrary so this can be used for generic allocations.
// e.g. if you wanted to store allocations of similar size
// (like a series of classes that share an inheritance tree).

#ifndef __TMEMORYCHUNKINTERFACE_H__
#include "TMemoryChunkInterface.h"
#endif

class TMemoryPool : public TMemoryChunkInterface
{
public:
	void   Initialize();

	void*  AllocateDebug(size_t bytes, const char* file = "", int line = 0);

	void*  Allocate(size_t bytes);

	void   FreeMemory(TAllocHeader* header);

	void   Activate(unsigned int id, size_t blockSize, unsigned int numBlocks);

	void   Deactivate();

	int		PrintAllocations(TStreamInterface* stream);

	bool   IsFull() const;

	size_t GetBlockSize() const;

private:
	void* InternalAllocate(size_t bytes, TAllocHeader*& header);

	bool*  m_memInUse;	// flag for each 'block'
	char*  m_memory;
	size_t m_blockSize;
	unsigned int m_numBlocks;
};

#endif
