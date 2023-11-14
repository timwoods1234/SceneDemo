#ifndef __TDIRECTSOUNDSYSTEM_H__
#define __TDIRECTSOUNDSYSTEM_H__

#ifndef __TPLATFORM_H__
#include "TPlatform.h"
#endif

#ifdef TPLATFORM_WIN

#ifndef __DSOUND_INCLUDED__
#include <dsound.h>
#endif

#ifndef __TAUDIOINTERFACE_H__
#include "TAudioInterface.h"
#endif

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class TDirectSoundBuffer;

class TDirectSoundSystem : public TAudioInterface,
                           public TEventListener
{
public:
                    TDirectSoundSystem(HWND window);

                    ~TDirectSoundSystem();

    TSound*			LoadSound(const char* filename);

    void            UnloadSound(TSound* sound);

    void			StopAllSounds();

    void			SetVolume(float relativeVolume);

    float			GetVolume() const;

    void            OnUpdate(float elapsedTime);

    void            OnLostDevice();

private:
    bool            Init(HWND window);

    void            Release();

    TDynamicSet<TDirectSoundBuffer*> m_soundInstances;

	LPDIRECTSOUND m_directSound;
	LPDIRECTSOUNDBUFFER m_primarySoundBuffer;
	void* m_listener;
	float m_volume;
	int m_directVolume;
};

#endif // #ifdef TPLATFORM_WIN

#endif // #ifndef __TDIRECTSOUNDSYSTEM_H__
