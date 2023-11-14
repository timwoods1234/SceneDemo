#ifndef __TDYNAMICARRAY_H__
#define __TDYNAMICARRAY_H__

#ifndef __TERROR_H__
#include "TError.h"
#endif

template <class T>
class TDynamicArray
{
public:
	TDynamicArray(unsigned int initialSize = 0);

	~TDynamicArray();

	inline void SetClearNewBlocksFlag(bool clear);

	inline unsigned int GetCapacity() const;

	inline unsigned int GetSize() const;

	inline T& operator[] (unsigned int index);

	inline const T& operator[] (unsigned int index) const;

	inline void Set(unsigned int index, const T element);

	inline void Add(const T data);

	inline bool	Contains(const T data);

	inline void SetUnsorted(bool unsorted);

	void Remove(const T data);

	void RemoveAt(unsigned int index);

	void Resize(unsigned int size);

	TDynamicArray<T>& operator= ( const TDynamicArray<T>& copy );

private:
	T* m_data;
	unsigned int m_size;
	mutable unsigned int m_get;
	unsigned int m_last;
	bool m_clearNewBlocks;
	bool m_unsorted;
};

#include "TDynamicArray.inl"

#endif
