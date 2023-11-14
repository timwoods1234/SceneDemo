#include "TMemory.h"
#include "TMemoryManager.h"
#include "TString.h"

//-------------------------------------------------------------------------------
void* operator new(size_t size, TMemoryChunkInterface* chunk)
{
	return chunk->Allocate(size);
}

//-------------------------------------------------------------------------------
void* operator new[] (size_t size)
{
	unsigned int* result = (unsigned int*)TMemoryManager::GetHeap()->Allocate(size + 4);

	*result = (unsigned int)(result + 1);

	result++;

	return result;
}

//-------------------------------------------------------------------------------
void* operator new(size_t size, TMemoryChunkInterface* chunk, const char* file, int line)
{
	int length = TStringHelper::TStrLen(file);
	int index = TStringHelper::LastIndexOf(file, '\\', length);

	if (index != -1)
	{
		file = file + index + 1;
	}

	return chunk->AllocateDebug(size, file, line);
}

//-------------------------------------------------------------------------------
void* operator new[](size_t size, const char* file, int line)
{
	int length = TStringHelper::TStrLen(file);
	int index = TStringHelper::LastIndexOf(file, '\\', length);

	if (index != -1)
	{
		file = file + index + 1;
	}

	unsigned int* result = (unsigned int*)TMemoryManager::GetHeap()->AllocateDebug(size + 4, file, line);

	*result = (unsigned int)(result + 1);

	result++;

	return result;
}
