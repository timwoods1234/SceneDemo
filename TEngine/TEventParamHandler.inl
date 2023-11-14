//-------------------------------------------------------------------------------
template <class Type, typename Param>
inline void	TEventParamHandler<Type, Param>::Setup(TEventListener* object, Handler handler)
{
	TEventParamHandlerBase<Param>::m_object = object;
	m_handler = handler;
}

//-------------------------------------------------------------------------------
template <class Type, typename Param>
void TEventParamHandler<Type, Param>::Execute(Param data)
{
	Type* instancePtr = static_cast<Type*>(TEventParamHandlerBase<Param>::m_object);
	(instancePtr->*m_handler)(data);
}

/***********************************************************************************************************/

template <class Type, typename Param>
inline typename TEventParamHandler<Type, Param>::Handler	
TEventParamHandler<Type, Param>::GetHandler() const
{
	return m_handler;
}

/***********************************************************************************************************/