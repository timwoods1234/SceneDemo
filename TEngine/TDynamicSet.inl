//-------------------------------------------------------------------------------
template <class T>
inline TDynamicSet<T>::TDynamicSet(unsigned int initialSize, unsigned int incrementSize)
:	m_size(0),
	m_data(NULL),
	m_capacity(0),
	m_incrementSize(incrementSize)
{
	if (m_incrementSize == 0)
	{
		m_incrementSize = 1;
	}

	if (initialSize > 0)
	{
		m_capacity = initialSize;

		m_data = TNewArray T[m_capacity];
	}
}

//-------------------------------------------------------------------------------
template <class T>
inline TDynamicSet<T>::TDynamicSet(const TDynamicSet<T>& setToCopy)
:	m_size(0),
	m_data(NULL),
	m_capacity(0),
	m_incrementSize(setToCopy.m_incrementSize)
{
	unsigned int size = setToCopy.GetSize();

	for (unsigned int i = 0; i < size; ++i)
	{
		Add(setToCopy.m_data[i]);
	}
}

//-------------------------------------------------------------------------------
template <class T>
inline TDynamicSet<T>::~TDynamicSet()
{
	ReleaseMemory();
}

//-------------------------------------------------------------------------------
template <class T>
inline TDynamicSet<T>& TDynamicSet<T>::operator= (const TDynamicSet<T>& copy)
{
	Clear();

	unsigned int size = copy.GetSize();

	for (unsigned int i = 0; i < size; ++i)
	{
		Add(copy.m_data[i]);
	}

	return *this;
}

//-------------------------------------------------------------------------------
template <class T>
inline unsigned int TDynamicSet<T>::GetSize() const
{
	return m_size;
}

//-------------------------------------------------------------------------------
template <class T>
inline unsigned int TDynamicSet<T>::GetCapacity() const
{
	return m_capacity;
}

//-------------------------------------------------------------------------------
template <class T>
inline const T& TDynamicSet<T>::operator[] (unsigned int index) const
{
	TASSERT((index < m_size), ("[TDynamicSet] Invalid index"));
	return m_data[index];
}

//-------------------------------------------------------------------------------
template <class T>
inline T& TDynamicSet<T>::operator[] (unsigned int index)
{
	TASSERT((index < m_size), ("[TDynamicSet] Invalid index"));
	return m_data[index];
}

//-------------------------------------------------------------------------------
template <class T>
inline void TDynamicSet<T>::RemoveAt(unsigned int index, bool maintainOrder)
{
	TASSERT((index < m_size), ("[TDynamicSet] Invalid index"));

	if (maintainOrder)
	{
		// move elements down
		for (unsigned int removeIndex = index; removeIndex < (m_size - 1); ++removeIndex)
		{
			m_data[removeIndex] = m_data[removeIndex + 1];
		}
	}
	else
	{
		// move last element into slot we are removing
		m_data[index] = m_data[m_size - 1];
	}

	m_size--;
}

//-------------------------------------------------------------------------------
template <class T>
inline void TDynamicSet<T>::Remove(const T &element, bool maintainOrder)
{
	for (unsigned int i = 0; i < m_size; ++i)
	{
		if (m_data[i] == element)
		{
			RemoveAt(i, maintainOrder);

			return;
		}
	}
}

//-------------------------------------------------------------------------------
template <class T>
inline T& TDynamicSet<T>::Add(const T &element)
{
	if (m_size >= m_capacity)
	{
		T* oldData = m_data;

		m_capacity += m_incrementSize;

		m_data = TNewArray T[m_capacity];

		if (oldData)
		{
			for (unsigned int i = 0; i < m_size; ++i)
			{
				m_data[i] = oldData[i];
			}

			TDeleteArray(oldData);
			oldData = NULL;
		}
	}

	m_data[m_size] = element;
	m_size++;

	return m_data[m_size - 1];
}

//-------------------------------------------------------------------------------
template <class T>
inline void TDynamicSet<T>::Clear()
{
	m_size = 0;
}

//-------------------------------------------------------------------------------
template <class T>
inline bool TDynamicSet<T>::Contains(const T& element) const
{
	for (unsigned int i = 0; i < m_size; ++i)
	{
		if (m_data[i] == element)
		{
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------------------
template <class T>
inline void TDynamicSet<T>::Append(const TDynamicSet<T> &otherSet)
{
	unsigned int size = otherSet.GetSize();

	for (unsigned int i = 0; i < size; ++i)
	{
		Add(otherSet[i]);
	}
}

//-------------------------------------------------------------------------------
template <class T>
inline void TDynamicSet<T>::ReleaseMemory()
{
	Clear();

	if (m_data != NULL)
	{
		TDeleteArray(m_data);
		m_data = NULL;
	}

	m_capacity = 0;
}
