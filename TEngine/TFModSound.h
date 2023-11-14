#ifndef __TFMODSOUND_H__
#define __TFMODSOUND_H__

#ifndef __TSOUND_H__
#include "TSound.h"
#endif

#ifndef _FMOD_HPP
#include "fmod.hpp"
#endif

class TFModSoundSystem;

class TFModSound : public TSound
{
public:
	TFModSound(TFModSoundSystem* soundSystem, FMOD::System* fmodSoundSystem, const char* filename);

	~TFModSound();

    void Play();

    void Stop();

	void SetPaused(bool pause);

	bool IsPaused();

    bool IsPlaying();

private:
	TFModSoundSystem* m_soundSystem;
	FMOD::Sound* m_sound;
};

#endif
