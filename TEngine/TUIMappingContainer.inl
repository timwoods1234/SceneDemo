//-------------------------------------------------------------------------------	
template <class ObjectType>
inline void TUIMappingContainer::Register(
						const TString& objectName,
						const TString& functionName,
						ObjectType* object,
						typename TUIMappingHandler<ObjectType>::TUIMappingFunction handler
						)
{
	TUIMappingHandler<ObjectType>* objectHandler = TNew TUIMappingHandler<ObjectType>();

	objectHandler->SetObjectName(objectName);
	objectHandler->SetMappingName(functionName);
	objectHandler->SetupMapping(object, handler);

	m_mappings.Add(objectHandler);
}
