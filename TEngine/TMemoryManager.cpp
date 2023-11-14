#include "TError.h"
#include "TString.h"
#include "TMemoryManager.h"
#include "TStreamInterface.h"

//-------------------------------------------------------------------------------
TMemoryPool TMemoryManager::ms_pools[MAXPOOLS];
TMemoryHeap TMemoryManager::ms_heap;

//-------------------------------------------------------------------------------
void TMemoryManager::Initialize()
{   
	for (unsigned int i = 0; i < MAXPOOLS; ++i)
	{
		ms_pools[i].Initialize();
	}

	ms_heap.Initialize();
	ms_heap.Activate(1);
}

//-------------------------------------------------------------------------------
bool TMemoryManager::CreatePool(size_t blockSize, int numInitialBlocks, unsigned int& index)
{
	index = -1;

	for (unsigned int i = 0; i < MAXPOOLS; ++i)
	{
		if (ms_pools[i].IsActive())
		{
			continue;
		}

		ms_pools[i].Activate(blockSize, blockSize, numInitialBlocks);

		index = i;

		break;
	}

	return (index != -1);
}

//-------------------------------------------------------------------------------
void TMemoryManager::DeletePool(unsigned int id)
{
	for (unsigned int i = 0; i < MAXPOOLS; ++i)
	{
		if (ms_pools[i].IsActive() && (ms_pools[i].GetID() == id))
		{
			DestroyChunk(&ms_pools[i]);
		}
	}
}

//-------------------------------------------------------------------------------
TMemoryHeap* TMemoryManager::GetHeap()
{
	return &ms_heap;
}

//-------------------------------------------------------------------------------
TMemoryPool* TMemoryManager::GetPool(unsigned int index)
{
	TASSERT( (index >= 0 && index < MAXPOOLS), "TMemoryManager -- Pool index out of range");
	return &ms_pools[index];
}

//-------------------------------------------------------------------------------
void TMemoryManager::DestroyChunk(TMemoryChunkInterface* chunk)
{
	chunk->Deactivate();
}

//-------------------------------------------------------------------------------
void TMemoryManager::ShutDown()
{
	for (unsigned int i=0; i < MAXPOOLS; ++i)
	{
		DestroyChunk(&ms_pools[i]);
	}

	DestroyChunk(&ms_heap);
}

 //-------------------------------------------------------------------------------
void TMemoryManager::GetSummary(int& heapAllocations, int& heapedBytes, int& poolAllocations, int& pooledBytes)
{
	heapedBytes = ms_heap.GetBytesAllocated();

	pooledBytes = 0;

	for (unsigned int i = 0; i < MAXPOOLS; i++)
	{
		if (ms_pools[i].IsActive())
		{
			pooledBytes += ms_pools[i].GetBytesAllocated();
		}
	}

	poolAllocations = 0;

	for (unsigned int i = 0; i < MAXPOOLS; i++)
	{
		if (ms_pools[i].IsActive())
		{
			poolAllocations += ms_pools[i].PrintAllocations(NULL);
		}
	}

	heapAllocations = 0;

	if (ms_heap.IsActive())
	{
		heapAllocations = ms_heap.PrintAllocations(NULL);
	}
}

//-------------------------------------------------------------------------------
void TMemoryManager::PrintAllocations(TStreamInterface* stream)
{
	stream->WriteString("TMemoryManager Allocations:\n");

	int totalBytes = 0;
	int totalAllocations = 0;

	for (unsigned int i = 0; i < MAXPOOLS; i++)
	{
		if (ms_pools[i].IsActive())
		{
			totalAllocations += ms_pools[i].PrintAllocations(stream);
			totalBytes += ms_pools[i].GetBytesAllocated();
		}
	}

	if (ms_heap.IsActive())
	{
		totalAllocations += ms_heap.PrintAllocations(stream);
		totalBytes += ms_heap.GetBytesAllocated();
	}

	TString formattedText = TString::Format("Total Allocations: %d (%d bytes)", totalAllocations, totalBytes);
	stream->WriteString(formattedText.GetPointer());
}
