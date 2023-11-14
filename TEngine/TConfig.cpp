#include "TConfig.h"
#include "TMath.h"

//-------------------------------------------------------------------------------
DefineSingleton(TConfig);

//-------------------------------------------------------------------------------
TConfig::TConfig()
:	m_screenHeight(480.f),
	m_screenWidth(640.f),
	m_windowed(true),
	m_useBatching(false)
{
}

//-------------------------------------------------------------------------------
TConfig::~TConfig()
{
}

//-------------------------------------------------------------------------------
float TConfig::GetScreenWidth() const
{
	return m_screenWidth;
}

//-------------------------------------------------------------------------------
float TConfig::GetScreenHeight() const
{
	return m_screenHeight;
}

//-------------------------------------------------------------------------------
bool TConfig::IsWindowed() const
{
	return m_windowed;
}

//-------------------------------------------------------------------------------
bool TConfig::UseBatching() const
{
	return m_useBatching;
}

//-------------------------------------------------------------------------------
unsigned int TConfig::GetNumAtlases() const
{
	return m_atlasNames.GetSize();
}

//-------------------------------------------------------------------------------
const TString& TConfig::GetAtlasFilename(unsigned int index) const
{
	return m_atlasNames[index];
}

//-------------------------------------------------------------------------------
TXMLObject* TConfig::HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects)
{
	if (strID == "Atlas")
	{
		TString filename = TString::Format("Assets/Atlas/%s.xml", TDataVariant::Find("name", objects).GetString());

		m_atlasNames.Add(filename);
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void TConfig::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_screenWidth = TDataVariant::Find("width", objects).GetFloat();
	m_screenHeight = TDataVariant::Find("height", objects).GetFloat();
	m_windowed = TDataVariant::Find("windowed", objects).GetBool();
	m_useBatching = TDataVariant::Find("useBatching", objects).GetBool();
}

//-------------------------------------------------------------------------------
void TConfig::FinaliseLoad()
{
	m_screenWidth = TMax(m_screenWidth, 640.f);
	m_screenHeight = TMax(m_screenHeight, 480.f);
}

//-------------------------------------------------------------------------------
void TConfig::Write(TXMLWriter& writer)
{
}