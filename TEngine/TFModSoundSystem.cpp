#pragma comment(lib, "fmod_vc.lib")

#include "TFModSoundSystem.h"
#include "TEventUpdate.h"
#include "TFModSound.h"

//-------------------------------------------------------------------------------
TFModSoundSystem::TFModSoundSystem()
:	m_volume(1.0f),
	m_channel(NULL),
	m_soundSystem(NULL)
{
	m_lastResult = FMOD_OK;

	if (!Init())
	{
		m_soundAvailable = false;
	}
	else
	{
		SetVolume(m_volume);

		TEventUpdate::Get()->Register(this, &TFModSoundSystem::OnUpdate);
	}
}

//-------------------------------------------------------------------------------
TFModSoundSystem::~TFModSoundSystem()
{
    TASSERT(m_soundInstances.GetSize() == 0, "TDirect Audio still has sounds allocated");

	TEventUpdate::Get()->Unregister(this, &TFModSoundSystem::OnUpdate);

	m_soundSystem->close();
	m_soundSystem->release();
}

//-------------------------------------------------------------------------------
bool TFModSoundSystem::Init()
{
	unsigned int version;
	void* extradriverdata = NULL;

	m_lastResult = FMOD::System_Create(&m_soundSystem);
	if (m_lastResult != FMOD_OK)
	{
		TDebugPrint(("[TFModSoundSystem::TFModSoundSystem] Failed to create FMOD"));
		return false;
	}

	m_lastResult = m_soundSystem->getVersion(&version);
	if (m_lastResult != FMOD_OK)
	{
		TDebugPrint(("[TFModSoundSystem::TFModSoundSystem] Failed to obtain version"));
		return false;
	}

	if (version < FMOD_VERSION)
	{
		TDebugPrint(("[TFModSoundSystem::TFModSoundSystem] Version is out of date"));
		return false;
	}

	m_lastResult = m_soundSystem->init(32, FMOD_INIT_NORMAL, NULL);
	if (m_lastResult != FMOD_OK)
	{
		TDebugPrint(("[TFModSoundSystem::TFModSoundSystem] Failed to init system"));
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------
TSound* TFModSoundSystem::LoadSound(const char* filename)
{
	TFModSound* sound = TNew TFModSound(this, m_soundSystem, filename);

	m_soundInstances.Add(sound);

	return sound;
}

//-------------------------------------------------------------------------------
void TFModSoundSystem::UnloadSound(TSound* sound)
{
	TFModSound* fModSound = static_cast<TFModSound*>(sound);

	m_soundInstances.Remove(fModSound);

	TSafeDelete(fModSound);
}

//-------------------------------------------------------------------------------
void TFModSoundSystem::StopAllSounds()
{
	for (unsigned int index = 0; index < m_soundInstances.GetSize(); index++)
	{
		m_soundInstances[index]->Stop();
	}
}

//-------------------------------------------------------------------------------
void TFModSoundSystem::SetVolume(float relativeVolume)
{
	m_lastResult = m_channel->setVolume(relativeVolume);

	if (m_lastResult != FMOD_OK)
	{
		TDebugPrint(("[TFModSoundSystem::SetVolume] Failed to set volume"));
	}
	else
	{
		m_volume = relativeVolume;
	}
}

//-------------------------------------------------------------------------------
float TFModSoundSystem::GetVolume() const
{
	return m_volume;
}

//-------------------------------------------------------------------------------
void TFModSoundSystem::OnUpdate(float elapsedTime)
{
	if (m_channel != NULL)
	{
		bool playing = false;

		m_lastResult = m_channel->isPlaying(&playing);

		if ((m_lastResult != FMOD_OK) && (m_lastResult != FMOD_ERR_INVALID_HANDLE) && (m_lastResult != FMOD_ERR_CHANNEL_STOLEN))
		{
			TDebugPrint(("[TFModSoundSystem::Update] Failed to get channel state"));
		}
	}
}

//-------------------------------------------------------------------------------
void TFModSoundSystem::Play(FMOD::Sound* sound)
{
	// TODO: add flag param to set position to 0

	m_lastResult = m_soundSystem->playSound(sound, NULL, false, &m_channel);

	if (m_lastResult != FMOD_OK)
	{
		TDebugPrint(("[TFModSoundSystem::Play] Play Sound Failed"));
	}
}

//-------------------------------------------------------------------------------
void TFModSoundSystem::Stop(FMOD::Sound* sound)
{
	// TODO: add flag param to set position to 0

	// play with the pause flag set
	m_lastResult = m_soundSystem->playSound(sound, NULL, true, &m_channel);

	if (m_lastResult != FMOD_OK)
	{
		TDebugPrint(("[TFModSoundSystem::PlaySound] Stop Sound Failed"));
	}
}

//-------------------------------------------------------------------------------
bool TFModSoundSystem::IsPlaying(FMOD::Sound* sound)
{
	bool playing = true;
	m_lastResult = m_channel->isPlaying(&playing);

	if ((m_lastResult != FMOD_OK) && (m_lastResult != FMOD_ERR_INVALID_HANDLE) && (m_lastResult != FMOD_ERR_CHANNEL_STOLEN))
	{
		return false;
	}

	if (!playing)
	{
		return false;
	}

	FMOD::Sound* currentSound = NULL;
	m_channel->getCurrentSound(&currentSound);

	if (currentSound == sound)
	{
		return true;
	}

	return false;
}