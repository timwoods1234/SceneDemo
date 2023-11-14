#include "TAudioConfig.h"
#include "TLocator.h"
#include "TAudioInterface.h"

//-------------------------------------------------------------------------------
TAudioConfig::TAudioConfig()
:	m_volume(1.f)
{
}

//-------------------------------------------------------------------------------
TAudioConfig::~TAudioConfig()
{
}

//-------------------------------------------------------------------------------
TXMLObject* TAudioConfig::HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects)
{
	return NULL;
}

//-------------------------------------------------------------------------------
void TAudioConfig::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_volume = TDataVariant::Find("volume", objects).GetFloat();
}

//-------------------------------------------------------------------------------
void TAudioConfig::FinaliseLoad()
{
	TLocator::GetAudio()->SetVolume(m_volume);
}

//-------------------------------------------------------------------------------
void TAudioConfig::Write(TXMLWriter& writer)
{
}
