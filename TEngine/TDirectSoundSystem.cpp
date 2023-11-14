#pragma comment(lib, "dsound.lib")

#include "TDirectSoundSystem.h"
#include "TDirectSoundBuffer.h"
#include "TError.h"
#include "TD3DEventDeviceLost.h"
#include "TEventUpdate.h"

//-------------------------------------------------------------------------------
TDirectSoundSystem::TDirectSoundSystem(HWND window)
:	m_directSound(NULL),
	m_primarySoundBuffer(NULL),
	m_volume(0.f),
	m_directVolume(0)
{
	TD3DEventDeviceLost::Get()->Register(this, &TDirectSoundSystem::OnLostDevice);

	TEventUpdate::Get()->Register(this, &TDirectSoundSystem::OnUpdate);

    if (!Init(window))
	{
		TDebugPrint(("[TDirectSoundSystem] Failed to initialize TDirectSoundSystem"));

        m_soundAvailable = false;
	}
}

//-------------------------------------------------------------------------------
TDirectSoundSystem::~TDirectSoundSystem()
{
    TASSERT(m_soundInstances.GetSize() == 0, "TDirect Audio still has sounds allocated");

    Release();

	TEventUpdate::Get()->Unregister(this, &TDirectSoundSystem::OnUpdate);

	TD3DEventDeviceLost::Get()->Unregister(this, &TDirectSoundSystem::OnLostDevice);
}

//-------------------------------------------------------------------------------
TSound* TDirectSoundSystem::LoadSound(const char* filename)
{
	TDirectSoundBuffer* buffer = TNew TDirectSoundBuffer(filename, m_directSound);

	buffer->SetVolume(m_directVolume);

	m_soundInstances.Add(buffer);

	return buffer;
}

//-------------------------------------------------------------------------------
void TDirectSoundSystem::UnloadSound(TSound* sound)
{
	TDirectSoundBuffer* buffer = static_cast<TDirectSoundBuffer*>(sound);

	m_soundInstances.Remove(buffer);

	TSafeDelete(buffer);
}

//-------------------------------------------------------------------------------
void TDirectSoundSystem::StopAllSounds()
{
    for (unsigned int index = 0; index < m_soundInstances.GetSize(); index++)
    {
        m_soundInstances[index]->Stop();
    }
}

//-------------------------------------------------------------------------------
void TDirectSoundSystem::SetVolume(float relativeVolume)
{
	m_volume = relativeVolume;

	m_directVolume = (m_volume == 0.f)
					  ? DSBVOLUME_MIN
					  : DSBVOLUME_MAX + (int)( (DSBVOLUME_MIN * 0.5) * (1.f - m_volume));

    for (unsigned int index = 0; index < m_soundInstances.GetSize(); index++)
    {
		m_soundInstances[index]->SetVolume(m_directVolume);
    }
}

//-------------------------------------------------------------------------------
float TDirectSoundSystem::GetVolume() const
{
	return m_volume;
}

//-------------------------------------------------------------------------------
void TDirectSoundSystem::OnUpdate(float elapsedTime)
{
    for (unsigned int index = 0; index < m_soundInstances.GetSize(); index++)
    {
		if (m_soundInstances[index]->IsPlaying())
		{
			m_soundInstances[index]->Update();
		}
    }
}

//-------------------------------------------------------------------------------
void TDirectSoundSystem::OnLostDevice()
{
    for (unsigned int index = 0; index < m_soundInstances.GetSize(); index++)
    {
		m_soundInstances[index]->OnLostDevice();
    }
}

//-------------------------------------------------------------------------------
bool TDirectSoundSystem::Init(HWND window)
{
	if (FAILED(DirectSoundCreate(NULL, &m_directSound,NULL)))
	{
		return false;
	}

	if (FAILED( m_directSound->SetCooperativeLevel(window, DSSCL_PRIORITY)))
	{
		return false;
	}

	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize  = sizeof( DSBUFFERDESC );
	dsbdesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;

	if (FAILED(m_directSound->CreateSoundBuffer(&dsbdesc ,&m_primarySoundBuffer,NULL)))
	{
		return false;
	}

	if (FAILED(m_primarySoundBuffer->QueryInterface(IID_IDirectSound3DListener, &m_listener)))
	{
		return false;
	}

	DS3DLISTENER gs_listenerParams;
	gs_listenerParams.dwSize = sizeof(DS3DLISTENER);
	static_cast<LPDIRECTSOUND3DLISTENER>(m_listener)->GetAllParameters( &gs_listenerParams);

	WAVEFORMATEX wfx;
	ZeroMemory(&wfx,sizeof(WAVEFORMATEX));
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 1;
	wfx.nSamplesPerSec = 22050;
	wfx.wBitsPerSample = 16;
	wfx.nBlockAlign     = wfx.wBitsPerSample / 8 * wfx.nChannels;
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

	if (FAILED(m_primarySoundBuffer->SetFormat(&wfx)))
	{
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------
void TDirectSoundSystem::Release()
{
	for (unsigned int index = 0; index < m_soundInstances.GetSize(); ++index)
	{
		TSafeDelete(m_soundInstances[index]);
	}

	if (m_listener != NULL)
	{
		static_cast<LPDIRECTSOUND3DLISTENER>(m_listener)->Release();
		m_listener = NULL;
	}

	SafeRelease(m_primarySoundBuffer);
	SafeRelease(m_directSound);
}