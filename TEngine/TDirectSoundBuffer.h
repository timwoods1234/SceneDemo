#ifndef __TDIRECTSOUNDBUFFER_H__
#define __TDIRECTSOUNDBUFFER_H__

#ifndef __TSOUND_H__
#include "TSound.h"
#endif

#ifndef __DSOUND_INCLUDED__
#include <dsound.h>
#endif

class TWaveFile;

class TDirectSoundBuffer : public TSound
{
public:
    TDirectSoundBuffer(const char* filename, LPDIRECTSOUND pDirectSound);

    ~TDirectSoundBuffer();

    void Play();

    void Stop();

	void SetPaused(bool pause);

	bool IsPaused();

    bool IsPlaying();

    void SetVolume(int volume);

	void Update();

	void OnLostDevice();

private:
	void StopInternal();

	void PlayInternal();

	bool CreateSoundBuffer(LPDIRECTSOUND dsound);

    void FillSharedBuffer(TWaveFile& loader);

    LPDIRECTSOUNDBUFFER m_soundBuffer; // todo: rename because it's a ptr

    int			m_volume;

    int			m_bufferSize;
    void*		m_sharedBuffer; // todo: rename because it's a ptr

    bool		m_isPlaying;

	unsigned long m_currentPosition;
};

#endif

