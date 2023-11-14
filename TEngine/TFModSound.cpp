#include "TFModSound.h"
#include "TFModSoundSystem.h"

//-------------------------------------------------------------------------------
TFModSound::TFModSound(TFModSoundSystem* soundSystem, FMOD::System* fmodSoundSystem, const char* filename)
:	TSound(filename)
{
	m_soundSystem = soundSystem;

	m_sound = NULL;

	FMOD_MODE mode = m_loop ? FMOD_LOOP_NORMAL | FMOD_2D : FMOD_DEFAULT;
	
	FMOD_RESULT result = fmodSoundSystem->createSound(filename, mode, NULL, &m_sound);

	TASSERT(result == FMOD_OK, "[TFModSound::TFModSound] failed to load sound");
}

//-------------------------------------------------------------------------------
TFModSound::~TFModSound()
{
	if (m_sound != NULL)
	{
		m_sound->release();
		m_sound = NULL;
	}
}

//-------------------------------------------------------------------------------
void TFModSound::Play()
{
	m_soundSystem->Play(m_sound);
	
	m_paused = false;
}

//-------------------------------------------------------------------------------
void TFModSound::Stop()
{
	m_soundSystem->Stop(m_sound);

	m_paused = false;
}

//-------------------------------------------------------------------------------
void TFModSound::SetPaused(bool pause)
{
	if (m_paused != pause)
	{
		if (pause)
		{
			m_soundSystem->Stop(m_sound);
		}
		else
		{
			m_soundSystem->Play(m_sound);
		}

		m_paused = pause;
	}
}

//-------------------------------------------------------------------------------
bool TFModSound::IsPaused()
{
	return m_paused;
}

//-------------------------------------------------------------------------------
bool TFModSound::IsPlaying()
{
	return m_soundSystem->IsPlaying(m_sound);
}