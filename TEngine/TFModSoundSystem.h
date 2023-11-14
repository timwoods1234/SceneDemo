#ifndef __TFMODSOUNDSYSTEM_H__
#define __TFMODSOUNDSYSTEM_H__

#ifndef _FMOD_HPP
#include "fmod.hpp"
#endif

#ifndef __TAUDIOINTERFACE_H__
#include "TAudioInterface.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

class TFModSound;

class TFModSoundSystem : public TAudioInterface,
						 public TEventListener
{
public:
	TFModSoundSystem();

	~TFModSoundSystem();

	TSound* LoadSound(const char* filename);

    void UnloadSound(TSound* sound);

	void StopAllSounds();

	void SetVolume(float relativeVolume);

	float GetVolume() const;

	void OnUpdate(float elapsedTime);

	void Play(FMOD::Sound* sound);
	
	void Stop(FMOD::Sound* sound);
	
	bool IsPlaying(FMOD::Sound* sound);

private:
	bool Init();

	TDynamicSet<TFModSound*> m_soundInstances;

	float m_volume;

	FMOD::System* m_soundSystem;
	FMOD::Channel* m_channel;
	FMOD_RESULT m_lastResult;
};

#endif
