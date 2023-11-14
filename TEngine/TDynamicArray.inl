//-------------------------------------------------------------------------------
template <class T>
TDynamicArray<T>::TDynamicArray(unsigned int initialSize)
:	m_clearNewBlocks(true),
	m_data(NULL),
	m_size(0),
	m_last(0),
	m_get(0),
	m_unsorted(false)
{
	if (initialSize > 0)
	{
		m_data = TNewArray T[initialSize];

		memset(&m_data[0], 0, initialSize * sizeof(T));

		m_size = initialSize;
		m_last = m_size;
	}
}

//-------------------------------------------------------------------------------
template <class T>
TDynamicArray<T>::~TDynamicArray()
{
	if (m_data != NULL)
	{
		TDeleteArray(m_data);
		m_data = NULL;
	}
}

//-------------------------------------------------------------------------------
template <class T>
void TDynamicArray<T>::Resize(unsigned int size)
{
	if (size < m_size)
	{
		m_last = size;

		return;
	}

	unsigned int newSize = size;

	T* newData = TNewArray T[newSize];
	TASSERT((newData != NULL),("[TDynamicArray] Couldn't allocate memory"));

	if (m_data != 0)
	{
		memcpy(newData, m_data, sizeof(T) * m_size);
		TDeleteArray(m_data);
	}

	m_data = newData;

	if (m_clearNewBlocks)
	{
		memset(&m_data[m_size], 0, (newSize - m_size) * sizeof(T));
	}
	
	m_size = newSize;
	m_last = m_size;
}

//-------------------------------------------------------------------------------
template <class T>
void TDynamicArray<T>::Remove(const T data)
{
	unsigned int i = 0;

	while(i < m_last)
	{
		if (m_data[i] == data)
		{
			if (m_get == i)
			{
				m_get--;
			}
			
			if (m_unsorted)
			{
				m_data[i] = m_data[m_last - 1];
				m_last--;

				return;
			}
			else
			{
				memcpy(&m_data[i], &m_data[i + 1], sizeof(T) * (m_last - i));
				m_last--;

				return;
			}
		}
		i++;
	}
}

//-------------------------------------------------------------------------------
template <class T>
void TDynamicArray<T>::RemoveAt(unsigned int index)
{
	TASSERT( (index < m_last), ("[TDynamicArray] Index out of bounds"));

	const unsigned int i = index;

	if (m_get == i)
	{
		m_get--;
	}
	
	if (m_unsorted)
	{
		m_data[i] = m_data[m_last - 1];
		m_last--;
		return;
	}
	else
	{
		memcpy(&m_data[i], &m_data[i+1], sizeof(T) * (m_last - i));
		m_last--;
		return;
	}
}

//-------------------------------------------------------------------------------
template <class T>
void TDynamicArray<T>::SetClearNewBlocksFlag(bool clear)
{
	m_clearNewBlocks = clear;
}

//-------------------------------------------------------------------------------
template <class T>
unsigned int TDynamicArray<T>::GetCapacity() const
{
	return m_size;
}

//-------------------------------------------------------------------------------
template <class T>
unsigned int TDynamicArray<T>::GetSize() const
{
	return m_last;
}

//-------------------------------------------------------------------------------
template <class T>
T& TDynamicArray<T>::operator[] (unsigned int index)
{
	TASSERT((index < m_size), ("[TDynamicArray] Invalid index"));
	return m_data[index];
}

//-------------------------------------------------------------------------------
template <class T>
const T& TDynamicArray<T>::operator[] (unsigned int index) const
{
	TASSERT( (index < m_size), "[TDynamicArray] Index out of bounds");
	return m_data[index];
}

//-------------------------------------------------------------------------------
template <class T>
void TDynamicArray<T>::Set(unsigned int index, const T element)
{
	if ((index + 1) > m_size)
	{
		Resize(index + 1);
	}

	m_data[index] = element;

	if (index >= m_last)
	{
		m_last = index + 1;
	}
}

//-------------------------------------------------------------------------------
template <class T>
void TDynamicArray<T>::Add(const T data)
{
	Set(m_last, data);
}

//-------------------------------------------------------------------------------
template <class T>
void TDynamicArray<T>::SetUnsorted(bool unsorted)
{
	m_unsorted = unsorted;
}

//-------------------------------------------------------------------------------
template <class T>
bool TDynamicArray<T>::Contains(const T data)
{
	unsigned int i = 0;

	while (i < m_last)
	{
		if (m_data[i] == data)
		{
			return true;
		}

		++i;
	}

	return false;
}

//-------------------------------------------------------------------------------
template <class T> 
inline TDynamicArray<T>& TDynamicArray<T>::operator = ( const TDynamicArray<T>& copy )
{
	TASSERT( (m_size == copy.m_size), ("Array sizes must be the same"));

	for (unsigned int i = 0; i < m_size; i++)
	{
		m_data[i] = copy.m_data[i];
	}

	m_last = copy.m_last;

	return *this;
}