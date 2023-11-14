#include <stdio.h>
#include <memory>

#include "TStringPool.h"
#include "TStringHelper.h"
#include "TStringPoolSearch.h"
#include "TError.h"

//-------------------------------------------------------------------------------
char TStringPool::ms_sharedBuffer[TSTRING_POOL_SIZE];
TStringPoolEntry* TStringPool::ms_newestEntry = 0;

TStringPoolEntry TStringPool::ms_poolEntries[TSTRING_POOL_ENTRIES];
unsigned int TStringPool::ms_numTotalStrings = 0;

TStringPoolEntry* TStringPool::ms_freeHead = NULL;
TStringPoolEntry* TStringPool::ms_allocHead = NULL;

//-------------------------------------------------------------------------------
int TStringPool::GetNumAllocations()
{
	return ms_numTotalStrings;
}

//-------------------------------------------------------------------------------
int TStringPool::GetAllocatedBytes()
{
	if (ms_newestEntry != NULL)
	{
		return ms_newestEntry->blockOffset + ms_newestEntry->blockLength;
	}

	return 0;
}

//-------------------------------------------------------------------------------
void TStringPool::PrintPool(char* outputBuffer)
{
	unsigned int end = 0;

	if (ms_newestEntry!= NULL)
	{
		end = (ms_newestEntry->blockOffset + ms_newestEntry->blockLength);
	}

	for (unsigned int index = 0; index < end; index++)
	{
		if (ms_sharedBuffer[index] != '\0')
		{
			outputBuffer[index] = ms_sharedBuffer[index];
		}
		else
		{
			outputBuffer[index] = '^';
		}
	}

	outputBuffer[end + 1] = '\n';
}

//-------------------------------------------------------------------------------
void TStringPool::DebugEraseBlock(TStringPoolEntry& entry)
{
	unsigned int start = entry.blockOffset;
	unsigned int end = entry.blockOffset + entry.blockLength;

	for (unsigned int index = start; index < end; index++)
	{
		ms_sharedBuffer[index] = '-';
	}
}

//-------------------------------------------------------------------------------
TStringPoolEntry* TStringPool::Allocate(const char* data, int length)
{
	TStringPoolEntry* newEntry = TStringPoolSearch::FindAllocatedEntry(ms_allocHead, data, length);

	if (newEntry != NULL)
	{
		newEntry->refCount++;

		return newEntry;
	}

#if TSTRING_DEBUG_MODE
	for (unsigned int index = 0; index < ms_nNumTotalStrings; index++)
	{
		if (ms_poolEntries[index].refCount == 0)
		{
			continue;
		}

		if (TStringHelper::TStrCmp(data, &ms_sharedBuffer[ms_poolEntries[index].nBlockOffset]) == 0)
		{
			TASSERT(false, "[TStringPool::Allocate] Failed to pick up existing allocation");
		}
	}
#endif

	newEntry = TStringPoolSearch::FindFreeEntry(ms_freeHead, length + 1);

	if (newEntry == NULL)
	{
		newEntry = AllocateNewEntry(length);
	}
	else
	{
		ms_freeHead = TStringPoolSearch::Remove(ms_freeHead, newEntry);
	}

	if (newEntry != NULL)
	{
		char* dst = ms_sharedBuffer + newEntry->blockOffset;

#if TSTRING_DEBUG_MODE
		DebugEraseBlock(*newEntry);
#endif

		TStringHelper::TStrNCpy(data, dst, length);

		newEntry->refCount = 1;
		newEntry->stringLength = length;

		ms_allocHead = TStringPoolSearch::Insert(ms_allocHead, newEntry);
	}

	return newEntry;
}

//-------------------------------------------------------------------------------
TStringPoolEntry* TStringPool::Allocate(const char* data)
{
	int length = TStringHelper::TStrLen(data);

	return Allocate(data, length);
}

//-------------------------------------------------------------------------------
void TStringPool::Deallocate(TStringPoolEntry* entry)
{
	if (entry != NULL)
	{
		entry->refCount--;

		TASSERT((entry->refCount >= 0), "[TStringPool::Deallocate] string has negative ref count");

		if (entry->refCount == 0)
		{
			RemoveAllocatedEntry(entry);
		}
	}
}

//-------------------------------------------------------------------------------
TStringPoolEntry* TStringPool::Reallocate(TStringPoolEntry* existingEntry, const char* data)
{
	if (existingEntry == NULL)
	{
		return Allocate(data);
	}
	else
	{
		Deallocate(existingEntry);

		int length = TStringHelper::TStrLen(data);
		return Allocate(data, length);
	}

	return NULL;
}

//-------------------------------------------------------------------------------
const char* TStringPool::GetData(const TStringPoolEntry& entry)
{
	return ms_sharedBuffer + entry.blockOffset;
}

//-------------------------------------------------------------------------------
TStringPoolEntry* TStringPool::AllocateNewEntry(int length)
{
	int offset = 0;

	if (ms_newestEntry != NULL)
	{
		offset = ms_newestEntry->blockOffset + ms_newestEntry->blockLength;
	}

	if ((offset + length + 1 > TSTRING_POOL_SIZE) || ms_numTotalStrings >= TSTRING_POOL_ENTRIES)
	{
		TASSERT(false, "[TStringPool::AllocateNewEntry] not enough space in the pool");

		return 0;
	}

	ms_poolEntries[ms_numTotalStrings].blockOffset = offset;
	ms_poolEntries[ms_numTotalStrings].blockLength = length + 1;
	ms_poolEntries[ms_numTotalStrings].prevEntry = 0;
	ms_poolEntries[ms_numTotalStrings].nextEntry = 0;

	ms_numTotalStrings++;

	TStringPoolEntry* lastPool = &(ms_poolEntries[ms_numTotalStrings - 1]);

	if (ms_newestEntry == NULL)
	{
		ms_newestEntry = lastPool;
	}
	else
	{
		TASSERT( 
			(lastPool->blockOffset == (ms_newestEntry->blockOffset + ms_newestEntry->blockLength)),
			"[TStringPool::AllocateNewEntry] New entry overlaps with the buffer"
			);

		ms_newestEntry = lastPool;
	}

	return ms_newestEntry;
}

//-------------------------------------------------------------------------------
void TStringPool::RemoveAllocatedEntry(TStringPoolEntry* entry)
{
	if (entry->refCount > 0)
	{
		TASSERT(false, "[TStringPool::RemoveAllocatedEntry] Removing allocated entry that is still referenced");
	}

	ms_allocHead = TStringPoolSearch::Remove(ms_allocHead, entry);

#if TSTRING_DEBUG_MODE
	DebugEraseBlock(*entry);
#endif

	if (entry != NULL)
	{
		ms_freeHead = TStringPoolSearch::Insert(ms_freeHead, entry);
	}
}
