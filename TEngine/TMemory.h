#ifndef __TMEMORY_H__
#define __TMEMORY_H__

#pragma warning (disable : 4291)	// no matching delete
#pragma warning (disable : 4302)	// truncation to unsigned int

#ifndef __TMEMORYMANAGER_H__
#include "TMemoryManager.h"
#endif

//-------------------------------------------------------------------------------
extern void* operator new(size_t size, TMemoryChunkInterface* chunk, const char* file, int line);
extern void* operator new(size_t size, TMemoryChunkInterface* chunk);
extern void* operator new[](size_t size, const char* file, int line);
extern void* operator new[](size_t size);

//-------------------------------------------------------------------------------
template <class T>
inline void	TDelete(T*& ptr)
{
	ptr->~T();

	TMemoryChunkInterface::Deallocate(ptr);

	ptr = NULL;
};

//-------------------------------------------------------------------------------
template <class T>
inline void	TDeleteArray(T*& ptr)
{
	// find the extra byte that holds the number of allocations
	unsigned int* mem = (unsigned int*)ptr;
	mem--;

	if (*mem != (unsigned int)ptr)
	{
		// it's a complex class, so call the destructors
		for (unsigned int index = 0; index < *mem; index++)
		{
			ptr[index].~T();
		}

		mem--;
	}

	TMemoryChunkInterface::Deallocate(mem);

	ptr = NULL;
};

//-------------------------------------------------------------------------------
#if defined(DEBUG) | defined(_DEBUG)
	#define TNew					::new(TMemoryManager::GetHeap(), __FILE__, __LINE__)
	#define TNewArray				::new(__FILE__, __LINE__)
	#define TPoolNew(pool)			::new(TMemoryManager::GetPool(pool), __FILE__, __LINE__)
#else
	#define TNew					::new(TMemoryManager::GetHeap())
	#define TNewArray				::new
	#define TPoolNew(pool)			::new(TMemoryManager::GetPool(pool))
#endif

#define TSafeDelete(object)			if (object != NULL) { TDelete(object); object = NULL; }
#define TSafeDeleteArray(object)	if (object != NULL) { TDeleteArray(object); object = NULL; }

// macros for un-tracked memory
#define SafeDelete(object)			if (object != NULL) { delete(object); object = NULL; }
#define SafeDeleteArray(p)			if (p) { delete[] (p);   (p) = NULL; }
#define SafeRelease(object)			if (object != NULL) { object->Release(); object = NULL; }

#endif
