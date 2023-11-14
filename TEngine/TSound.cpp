#include "TSound.h"
#include "TResourceManager.h"
#include "TLocator.h"
#include "TAudioInterface.h"
#include "TXMLReader.h"

//-------------------------------------------------------------------------------
TSound* TSound::Acquire(const char* id)
{
    TString filename = TString::Format("Assets/Sound/%s.wav", id);

    return (TSound*)TResourceManager::Get()->Allocate(ResourceType_Sound, filename.GetPointer());
}

//-------------------------------------------------------------------------------
void TSound::Release(TSound* sound)
{
    TResourceManager::Get()->Release(ResourceType_Sound, sound);
}

//-------------------------------------------------------------------------------
TSound::TSound(const char* filename)
:   m_loop(false),
	m_paused(false)
{
	TString xmlFilename = GetXMLFilename(filename);
	
	TXMLReader reader(xmlFilename.GetPointer(), *this);

    if (reader.WasError())
    {
		TDebugPrint(("[TSound::Load] Failed to parse %s", xmlFilename.GetPointer()));
	}
}

//-------------------------------------------------------------------------------
TSound::~TSound()
{
}

//-------------------------------------------------------------------------------
TRefCountedObject* TSound::Load(const char* id)
{
    TSound* result = TLocator::GetAudio()->LoadSound(id);

    if (result == NULL)
    {
        TDebugPrint(("[TSound::Load] Failed to load %s", id));

		TSafeDelete(result);
    }

	return result;
}

//-------------------------------------------------------------------------------
void TSound::Unload(TRefCountedObject* toDelete)
{
    TSound* sound = static_cast<TSound*>(toDelete);

    TLocator::GetAudio()->UnloadSound(sound);
}

//-------------------------------------------------------------------------------
TXMLObject* TSound::HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects)
{
    return NULL;
}

//-------------------------------------------------------------------------------
void TSound::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
    m_loop = TDataVariant::Find("loop", objects).GetBool();
}

//-------------------------------------------------------------------------------
void TSound::FinaliseLoad()
{
}

//-------------------------------------------------------------------------------
void TSound::Write(TXMLWriter& writer)
{
}

//-------------------------------------------------------------------------------
TString TSound::GetXMLFilename(const char* filename)
{
    TString result = filename;

    int index = result.LastIndexOf('.');

    result.Remove(index, result.GetLength() - index);

    result += ".xml";

    return result;
}
