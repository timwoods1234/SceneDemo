#ifndef __TDYNAMICSET_H__
#define __TDYNAMICSET_H__

#ifndef __TMEMORY_H__
#include "TMemory.h"
#endif

#ifndef __TERROR_H__
#include "TError.h"
#endif

template<class T>
class TDynamicSet
{
public:
	inline TDynamicSet(unsigned int initialSize = 0, unsigned int incrementSize = 5);

	inline TDynamicSet(const TDynamicSet<T> & setToCopy);

	inline ~TDynamicSet();

	inline TDynamicSet<T>& operator= (const TDynamicSet<T>& copy);

	inline unsigned int GetSize() const;

	inline unsigned int GetCapacity() const;

	inline T& Add(const T& element = T());

	inline void Remove(const T& element, bool maintainOrder = false);

	inline void RemoveAt(unsigned int index, bool maintainOrder = false);

	inline bool Contains(const T& element) const;

	inline const T& operator [] (unsigned int index) const;

	inline T& operator[] (unsigned int index);

	inline void Clear();

	inline void Append(const TDynamicSet<T> & otherSet);

	// call this only when the set won't be used any more
	inline void ReleaseMemory();

protected:
	unsigned int m_size;
	unsigned int m_capacity;
	unsigned int m_incrementSize;

	T* m_data;
};

#include "TDynamicSet.inl"

#endif
