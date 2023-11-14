//-------------------------------------------------------------------------------
template <class Type>
inline void	TEventHandler<Type>::Setup(class TEventListener* object, Handler handler)
{
	m_object = object;
	m_handler = handler;
}

//-------------------------------------------------------------------------------
template <class Type>
void TEventHandler<Type>::Execute()
{
	Type* instancePtr = static_cast<Type*>(m_object);
	(instancePtr->*m_handler)();
}

//-------------------------------------------------------------------------------
template <class Type>
inline typename TEventHandler<Type>::Handler	
TEventHandler<Type>::GetHandler() const
{
	return m_handler;
}
