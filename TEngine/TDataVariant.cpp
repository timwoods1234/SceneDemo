#include <cstdlib>
#include "TDataVariant.h"

//-------------------------------------------------------------------------------
const TDataVariant TDataVariant::s_default;

//-------------------------------------------------------------------------------
TDataVariant::TDataVariant()
{
	m_tagId = TString::GetEmptyString();
	m_data = TString::GetEmptyString();
}

//-------------------------------------------------------------------------------
TDataVariant::~TDataVariant()
{

}

//-------------------------------------------------------------------------------
TDataVariant::TDataVariant(const char* id, const char* data)
{
	Setup(id, data);
}

//-------------------------------------------------------------------------------
void TDataVariant::Setup(const char* id, const char* data)
{
	m_tagId = id;
	m_data = data;
}

//-------------------------------------------------------------------------------
const char* TDataVariant::GetString() const
{
	return m_data.GetPointer();
}

//-------------------------------------------------------------------------------
int TDataVariant::GetInt() const
{
	if (m_data.IsEmpty())
	{
		return 0;
	}

	return TStringHelper::ConvertToInt(m_data.GetPointer());
}

//-------------------------------------------------------------------------------
float TDataVariant::GetFloat(float defaultValue) const
{
	if (m_data.IsEmpty())
	{
		return defaultValue;
	}

	return TStringHelper::ConvertToFloat(m_data.GetPointer());
}

//-------------------------------------------------------------------------------
bool TDataVariant::GetBool() const
{
	return (m_data == "true" || 
			m_data == "TRUE" || 
			m_data == "True");
}

//-------------------------------------------------------------------------------
const TDataVariant& TDataVariant::Find(const TString& tagId, TDynamicSet<TDataVariant>& data)
{
	for (unsigned int index = 0; index < data.GetSize(); ++index)
	{
		if (data[index].m_tagId == tagId)
		{
			return data[index];
		}
	}

	return s_default;
}

//-------------------------------------------------------------------------------
const TDataVariant& TDataVariant::Find(const char* tagId, TDynamicSet<TDataVariant>& data)
{
	for (unsigned int index = 0; index < data.GetSize(); ++index)
	{
		if (data[index].m_tagId == tagId)
		{
			return data[index];
		}
	}

	return s_default;
}
