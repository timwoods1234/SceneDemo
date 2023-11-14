#include <cstdlib>
#include <memory.h>

#include "TError.h"
#include "TMemoryHeap.h"
#include "TString.h"
#include "TStringHelper.h"
#include "TStreamInterface.h"

//-------------------------------------------------------------------------------
void TMemoryHeap::Initialize()
{
	m_active        = false;
	m_bytesAllocated = 0;
	m_bytesPeak      = 0;
	m_instances	 = 0;
	m_headAlloc	 = NULL;
}

//-------------------------------------------------------------------------------
void TMemoryHeap::Activate (unsigned int id)
{
	m_id			 = id;
	m_bytesAllocated = 0;
	m_bytesPeak      = 0;
	m_active        = true;
	m_instances     = 0;
}

//-------------------------------------------------------------------------------
void TMemoryHeap::Deactivate ()
{
	m_bytesAllocated = 0;
	m_bytesPeak      = 0;
	m_active		 = false;
	m_id			 = 0;
	m_instances     = 0;
}

//-------------------------------------------------------------------------------
void* TMemoryHeap::Allocate(size_t bytes)
{
	TAllocHeader* header = NULL;
	return InternalAllocate(bytes, header);
}

//-------------------------------------------------------------------------------
void* TMemoryHeap::AllocateDebug(size_t bytes, const char* file, int line)
{
	TAllocHeader* header = NULL;

	void* result = InternalAllocate(bytes, header);

#if defined(DEBUG) | defined(_DEBUG)
	TStringHelper::TStrNCpy(file, header->file, 64);
	header->lineNumber = line;
#endif

	return result;
}

//-------------------------------------------------------------------------------
void* TMemoryHeap::InternalAllocate(size_t bytes, TAllocHeader*& header)
{
	size_t requestedBytes = bytes + sizeof(TAllocHeader);

	char* mem = (char*)malloc(requestedBytes);

	if (!mem)
	{
		TASSERT(false, "TMemoryHeap -- allocation failed");

		return NULL;
	}

	header = (TAllocHeader*)mem;

	header->chunk		= this;
	header->size		= bytes;
	header->next		= m_headAlloc;
	header->prev		= NULL;
	header->allocNum  = s_nextAllocNum++;

	if (m_headAlloc != NULL)
	{
		m_headAlloc->prev = header;
	}

	m_headAlloc = header;

	m_bytesAllocated += bytes;

	if (m_bytesAllocated > m_bytesPeak)
	{
		m_bytesPeak = m_bytesAllocated;
	}

	m_instances++;

	void* startMemBlock = (char*)(mem + sizeof(TAllocHeader));
	memset(startMemBlock, 0, bytes);

	return startMemBlock; 
}

//-------------------------------------------------------------------------------
void TMemoryHeap::FreeMemory(TAllocHeader* header)
{
	if (header->prev == NULL)
	{
		m_headAlloc = header->next;
	}        
	else
	{
		header->prev->next = header->next;
	}

	if (header->next != NULL)
	{
		header->next->prev = header->prev;   
	}

	m_bytesAllocated -= header->size;
	m_instances--;

	free(header);
}

//-------------------------------------------------------------------------------
int TMemoryHeap::PrintAllocations(TStreamInterface* stream)
{
	int allocations = 0;
	TAllocHeader* header = m_headAlloc;

	while (header != NULL)
	{
		if (stream != NULL)
		{
			TString formattedText = TString::Format("AllocID %d (heap): %d bytes, address 0x%0Xd %s \n",
				header->allocNum, header->size, (char*)header + sizeof(TAllocHeader), TraceToSource(header));

			stream->WriteString(formattedText.GetPointer());
		}

		allocations++;

		header = header->next;
	}

	return allocations;
}
