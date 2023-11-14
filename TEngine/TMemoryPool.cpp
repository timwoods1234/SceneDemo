#include <cstdlib>
#include <memory.h>

#include "TString.h"
#include "TError.h"
#include "TMemoryPool.h"
#include "TStreamInterface.h"

//-------------------------------------------------------------------------------
void TMemoryPool::Initialize()
{
	m_active        = false;
	m_bytesAllocated = 0;
	m_bytesPeak      = 0;
	m_instances	 = 0;
}

//-------------------------------------------------------------------------------
void TMemoryPool::Activate(unsigned int id, size_t blockSize, unsigned int numBlocks)
{
	m_id			 = id;
	m_blockSize		 = blockSize;
	m_numBlocks		 = numBlocks;

	m_bytesAllocated = 0;
	m_bytesPeak      = 0;
	m_active        = true;
	m_instances	 = 0;

	// Reserve space, all blocks start unused
	m_memory = (char*)malloc(numBlocks * (blockSize+sizeof(TAllocHeader)));

	m_memInUse = (bool*)malloc(numBlocks * sizeof(bool));

	for (unsigned int i = 0; i < numBlocks; i++)
	{
		m_memInUse[i] = false;
	}
}

//-------------------------------------------------------------------------------
void TMemoryPool::Deactivate ()
{
	// free memory
	if (m_active)
	{
		free(m_memInUse);
		free(m_memory);
	}

	m_bytesAllocated = 0;
	m_bytesPeak      = 0;
	m_active		 = false;
	m_id			 = 0;
	m_instances	 = 0;
}

//-------------------------------------------------------------------------------
void* TMemoryPool::InternalAllocate(size_t bytes, TAllocHeader*& header)
{
	size_t requestedBytes = m_blockSize + sizeof(TAllocHeader);

	if ((bytes + m_bytesAllocated) > (m_blockSize * m_numBlocks))
	{
		TASSERT(false, "TMemoryPool -- not enough free memory");
		return NULL;
	}

	// find empty block
	unsigned int i = 0;
	while ((i < m_numBlocks) && m_memInUse[i])
	{
		i++;
	}

	if (i >= m_numBlocks)
	{
		TASSERT(false, "TMemoryPool -- Pool is full");
		return NULL;
	}

	// pMemBlock = start of requested memory block in pMemory
	int memBlock = i * (m_blockSize + sizeof(TAllocHeader));
	m_memInUse[i] = true;

	header = (TAllocHeader*)((char*)m_memory + memBlock);

	header->allocNum = s_nextAllocNum++;
	header->memIndex = i;
	header->chunk = this;
	header->size = bytes;

	m_bytesAllocated += bytes;

	if (m_bytesAllocated > m_bytesPeak)
	{
		m_bytesPeak = m_bytesAllocated;
	}

	m_instances++;

	// return address is just after index marker
	void* startMemBlock = (char*)(m_memory + memBlock + sizeof(TAllocHeader));
	memset(startMemBlock, 0, m_blockSize);

	return startMemBlock;
}

//-------------------------------------------------------------------------------
void* TMemoryPool::Allocate(size_t bytes)
{
	TAllocHeader* header = NULL;

	return InternalAllocate(bytes, header);
}

//-------------------------------------------------------------------------------
void* TMemoryPool::AllocateDebug(size_t bytes, const char* file, int line)
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
void TMemoryPool::FreeMemory(TAllocHeader* header)
{
	m_memInUse[header->memIndex] = false;

	m_bytesAllocated -= header->size;

	m_instances--;
}

//-------------------------------------------------------------------------------
int TMemoryPool::PrintAllocations(TStreamInterface* stream)
{
	int allocations = 0;

	for (unsigned int i = 0; i < m_numBlocks; i++)
	{
		if (m_memInUse[i])
		{
			if (stream != NULL)
			{
				int memBlock = i * (m_blockSize + sizeof(TAllocHeader));
				TAllocHeader* header = (TAllocHeader*)((char*)m_memory + memBlock);

				TString formattedText = TString::Format("AllocID %d (Pool %d, block %d): address 0x%0Xd %s \n",
					header->allocNum, m_id, i, (char*)header + sizeof(TAllocHeader), TraceToSource(header));

				stream->WriteString(formattedText.GetPointer());
			}

			allocations++;
		}
	}

	return allocations;
}

//-------------------------------------------------------------------------------
bool TMemoryPool::IsFull() const
{
	return (m_instances == m_numBlocks); 
}

//-------------------------------------------------------------------------------
size_t TMemoryPool::GetBlockSize() const 
{ 
	return m_blockSize; 
}
