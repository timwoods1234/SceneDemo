#include "TError.h"
#include "TMemoryChunkInterface.h"
#include "TMemoryManager.h"

//-------------------------------------------------------------------------------
int TMemoryChunkInterface::s_nextAllocNum = 1;

//-------------------------------------------------------------------------------
unsigned int TMemoryChunkInterface::GetID() const
{
	return m_id;
}

//-------------------------------------------------------------------------------
void TMemoryChunkInterface::Deallocate (void* mem)
{
	TAllocHeader* header = (TAllocHeader*)((char*)mem - sizeof(TAllocHeader));

	header->chunk->FreeMemory(header);
}

//-------------------------------------------------------------------------------
int TMemoryChunkInterface::GetMemoryBookmark()
{
	return s_nextAllocNum;
}

//-------------------------------------------------------------------------------
const char* TMemoryChunkInterface::TraceToSource(TAllocHeader* header)
{
#if defined(DEBUG) | defined(_DEBUG)
	static char buffer[512];
	sprintf_s(buffer, 512, "%s:%d", header->file, header->lineNumber);
	return buffer;
#else
	return "trace unavailable in release";
#endif
}


//-------------------------------------------------------------------------------
bool TMemoryChunkInterface::IsActive() const
{
	return m_active;
}

//-------------------------------------------------------------------------------
size_t TMemoryChunkInterface::GetBytesAllocated() const 
{
	return m_bytesAllocated; 
}
