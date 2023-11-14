#ifndef __TMEMORYMANAGER_H__
#define __TMEMORYMANAGER_H__

#include <stdio.h>

#ifndef __TALLOCHEADER_H__
#include "TAllocHeader.h"
#endif

#ifndef __TMEMORYHEAP_H__
#include "TMemoryHeap.h"
#endif

#ifndef __TMEMORYPOOL_H__
#include "TMemoryPool.h"
#endif

class TMemoryChunkInterface;
class TString;
class TStreamInterface;

class TMemoryManager
{
public:
	static void Initialize();
	static void ShutDown();

	static bool CreatePool(size_t blockSize, int numInitialBlocks, unsigned int& index);
	static void DeletePool(unsigned int id);

	static TMemoryHeap* GetHeap();
	static TMemoryPool* GetPool(unsigned int index);

	static void GetSummary(int& heapAllocations, int& heapedBytes, int& poolAllocations, int& pooledBytes);
	static void PrintAllocations(TStreamInterface* stream);

private:
	static void DestroyChunk(TMemoryChunkInterface* chunk);

	const static int MAXPOOLS = 6;

	static TMemoryPool ms_pools[MAXPOOLS];
	static TMemoryHeap ms_heap;
};

#endif
