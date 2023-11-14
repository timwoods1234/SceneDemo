#ifndef __TSTRINGPOOL_H__
#define __TSTRINGPOOL_H__

#ifndef __TSTRINGPOOLENTRY_H__
#include "TStringPoolEntry.h"
#endif

/*
#if defined(DEBUG) | defined(_DEBUG)
#	define TSTRING_DEBUG_MODE 1
#endif
*/

#define TSTRING_POOL_SIZE 32768
#define TSTRING_POOL_ENTRIES 1024

class TStringPool
{
public:
	static TStringPoolEntry* Allocate(const char* data);

	static void Deallocate(TStringPoolEntry* entry);

	static TStringPoolEntry* Reallocate(TStringPoolEntry* entry, const char* data);

	static const char* GetData(const TStringPoolEntry& entry);

	static void PrintPool(char* outputBuffer);

	static int GetNumAllocations();

	static int GetAllocatedBytes();

private:
	static TStringPoolEntry* Allocate(const char* data, int length);

	static TStringPoolEntry* AllocateNewEntry(int length);

	static void DebugEraseBlock(TStringPoolEntry& entry);

	static void RemoveAllocatedEntry(TStringPoolEntry* entry);

	static char ms_sharedBuffer[TSTRING_POOL_SIZE];
	static TStringPoolEntry ms_poolEntries[TSTRING_POOL_ENTRIES];

	static unsigned int ms_numTotalStrings;

	static TStringPoolEntry* ms_newestEntry;
	static TStringPoolEntry* ms_freeHead;
	static TStringPoolEntry* ms_allocHead;
};

#endif
