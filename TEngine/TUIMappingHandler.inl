//-------------------------------------------------------------------------------
template <class Type>
TUIMappingHandler<Type>::~TUIMappingHandler()
{
}

//-------------------------------------------------------------------------------
template <class Type>
inline void TUIMappingHandler<Type>::Execute(const TUIVariableParameter* parameters, TUIVariableResult* result)
{
	Type* instance = static_cast<Type*>(m_receiver);

	(instance->*m_mappingFunction)(parameters, result);
}

//-------------------------------------------------------------------------------
template <class Type>
inline void TUIMappingHandler<Type>::SetupMapping(TUIController* receiver, TUIMappingFunction mapping)
{
	m_mappingFunction = mapping;

	m_receiver = receiver;
}
