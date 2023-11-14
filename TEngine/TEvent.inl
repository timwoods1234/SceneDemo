//-------------------------------------------------------------------------------
template <class ObjectType>
inline void	TEvent::Register(ObjectType* object, typename TEventHandler<ObjectType>::Handler handler)
{
	TEventHandler<ObjectType>* objectHandler = TNew TEventHandler<ObjectType>();
	objectHandler->Setup(object, handler);

	m_listeners.Add(objectHandler);
}

//-------------------------------------------------------------------------------
template <class ObjectType>
inline void	TEvent::Unregister(ObjectType* object, typename TEventHandler<ObjectType>::Handler handler)
{
	for (unsigned int index = 0; index < m_listeners.GetSize(); ++index)
	{
		TEventHandlerBase* registeredHandler = m_listeners[index];
		TEventListener* registeredObject = registeredHandler->GetListener();

		if (registeredObject == object)
		{
			TEventHandler<ObjectType>* handlerType = static_cast<TEventHandler<ObjectType>*>(m_listeners[index]);

			if (handlerType->GetHandler() == handler)
			{
				TSafeDelete(m_listeners[index]);
				m_listeners.RemoveAt(index);

				index--;
			}
		}
	}
}
