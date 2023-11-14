//-------------------------------------------------------------------------------
template <typename Param>
inline TEventParam<Param>::TEventParam()
{

}

//-------------------------------------------------------------------------------
template <typename Param>
inline TEventParam<Param>::~TEventParam()
{
	Clear();
}

//-------------------------------------------------------------------------------
template <typename Param>
inline void TEventParam<Param>::Clear()
{
	for (unsigned int index = 0; index < m_listeners.GetSize(); ++index)
	{
		TSafeDelete(m_listeners[index]);
	}

	m_listeners.Clear();
}

//-------------------------------------------------------------------------------
template <typename Param>
inline void	TEventParam<Param>::Execute(Param data)
{
	for (unsigned int index = 0; index < m_listeners.GetSize(); ++index)
	{
		m_listeners[index]->Execute(data);
	}
}

//-------------------------------------------------------------------------------
template <typename Param>
template <class ObjectType>
inline void	TEventParam<Param>::Register(ObjectType* object, typename TEventParamHandler<ObjectType, Param>::Handler handler)
{
	TEventParamHandler<ObjectType, Param>* objectHandler = TNew TEventParamHandler<ObjectType, Param>();
	objectHandler->Setup(object, handler);

	m_listeners.Add(objectHandler);
}

//-------------------------------------------------------------------------------
template <typename Param>
template <class ObjectType>
inline void	TEventParam<Param>::Unregister(ObjectType* object, typename TEventParamHandler<ObjectType, Param>::Handler handler)
{
	for (unsigned int index = 0; index < m_listeners.GetSize(); ++index)
	{
		TEventParamHandlerBase<Param>* registeredHandler = m_listeners[index];
		TEventListener* registeredObject = registeredHandler->GetListener();

		if (registeredObject == object)
		{
			TEventParamHandler<ObjectType, Param>* handlerType = static_cast<TEventParamHandler<ObjectType, Param>*>(m_listeners[index]);

			if (handlerType->GetHandler() == handler)
			{
				TSafeDelete(m_listeners[index]);

				m_listeners.RemoveAt(index);

				index--;
			}
		}
	}
}
