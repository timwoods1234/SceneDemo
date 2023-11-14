#include "TDirectSoundBuffer.h"
#include "TWaveFile.h"

//-------------------------------------------------------------------------------
TDirectSoundBuffer::TDirectSoundBuffer(const char* filename, LPDIRECTSOUND pDirectSound)
:   TSound(filename),
	m_soundBuffer(NULL),
    m_volume(0),
    m_bufferSize(0),
    m_sharedBuffer(NULL),
    m_isPlaying(false),
	m_currentPosition(0)
{
    TWaveFile soundWave(filename);

    DSBUFFERDESC dsbd;
    ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));

    dsbd.dwSize = sizeof(DSBUFFERDESC);
    dsbd.dwFlags = DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME;
    dsbd.dwBufferBytes = ((MMCKINFO*)soundWave.GetWaveRiffChunk())->cksize;
    dsbd.lpwfxFormat = (WAVEFORMATEX*)soundWave.GetWaveFormat();

    if (FAILED(pDirectSound->CreateSoundBuffer(&dsbd, (LPDIRECTSOUNDBUFFER*)&m_sharedBuffer, NULL)))
    {
        TDebugPrint(("[TDirectSoundDefinition::TDirectSoundDefinition] Failed to create sound buffer"));
        return;
    }

    m_bufferSize = dsbd.dwBufferBytes;

    FillSharedBuffer(soundWave);

	CreateSoundBuffer(pDirectSound);
}

//-------------------------------------------------------------------------------
TDirectSoundBuffer::~TDirectSoundBuffer()
{
	Stop();

	if (m_soundBuffer != NULL)
	{
		m_soundBuffer->Release();
		m_soundBuffer = NULL;
	}
}

//-------------------------------------------------------------------------------
void TDirectSoundBuffer::Play()
{
	if (m_soundBuffer == NULL)
	{
		return;
	}

	m_currentPosition = 0;
	m_soundBuffer->SetCurrentPosition(m_currentPosition);
	m_currentPosition = 1;

	PlayInternal();

	m_isPlaying = true;
	m_paused = false;
}

//-------------------------------------------------------------------------------
void TDirectSoundBuffer::Stop()
{
	if (m_soundBuffer != NULL)
	{
		m_currentPosition = 0;
		m_soundBuffer->SetCurrentPosition(m_currentPosition);
	}

	StopInternal();

	m_paused = false;
	m_isPlaying = false;
}

//-------------------------------------------------------------------------------
void TDirectSoundBuffer::SetPaused(bool pause)
{
	if (m_currentPosition != 0 && m_paused != pause)
	{
		if (pause)
		{
			StopInternal();
		}
		else
		{
			PlayInternal();
		}

		m_paused = pause;
	}
}

//-------------------------------------------------------------------------------
bool TDirectSoundBuffer::IsPaused()
{
	return m_paused;
}

//-------------------------------------------------------------------------------
bool TDirectSoundBuffer::IsPlaying()
{
    return m_isPlaying;
}

//-------------------------------------------------------------------------------
void TDirectSoundBuffer::SetVolume(int volume)
{
    m_volume = volume;
	
	if(m_soundBuffer != NULL)
	{
		m_soundBuffer->SetVolume(m_volume);
		m_soundBuffer->SetPan(DSBPAN_CENTER);
	}
}

//-------------------------------------------------------------------------------
void TDirectSoundBuffer::Update()
{
	if (m_soundBuffer != NULL)
	{
		DWORD status = 0;
		m_soundBuffer->GetStatus(&status);

		m_isPlaying = ((status & DSBSTATUS_PLAYING) != 0);

		if (!m_isPlaying)
		{
			StopInternal();
		}
	}
}

//-------------------------------------------------------------------------------
void TDirectSoundBuffer::OnLostDevice()
{
	if (m_isPlaying)
	{
		Stop();

		Play();
	}
}

//-------------------------------------------------------------------------------
void TDirectSoundBuffer::StopInternal()
{
	if (m_soundBuffer != NULL)
	{
		m_soundBuffer->Stop();
	}
}

//-------------------------------------------------------------------------------
void TDirectSoundBuffer::PlayInternal()
{
	if (m_soundBuffer != NULL)
	{
		if (m_loop)
		{
			m_soundBuffer->Play(0, 0, DSBPLAY_LOOPING);
		}
		else
		{
			m_soundBuffer->Play(0, 0, 0);
		}
	}
}

//-------------------------------------------------------------------------------
bool TDirectSoundBuffer::CreateSoundBuffer(LPDIRECTSOUND dsound)
{
	if (FAILED(dsound->DuplicateSoundBuffer((LPDIRECTSOUNDBUFFER)m_sharedBuffer, &m_soundBuffer)))
	{
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------
void TDirectSoundBuffer::FillSharedBuffer(TWaveFile& loader)
{
    unsigned char* waveData;
    unsigned int waveSize;
    void* data = NULL;
    void* data2 = NULL;
    unsigned long length;
    unsigned long length2;

    //creates the buffer the the right size.
    int nWaveFileSize = ((MMCKINFO*)loader.GetWaveRiffChunk())->cksize;

    waveData = TNewArray unsigned char[nWaveFileSize];

    if (FAILED(loader.Read(nWaveFileSize, waveData, &waveSize)))
    {
        return;
    }

    loader.Reset();

    //locks the buffer for writing
    if (FAILED(((LPDIRECTSOUNDBUFFER)m_sharedBuffer)->Lock(0, m_bufferSize, &data, &length, &data2, &length2, 0L)))
    {
        return;
    }

    //Ensure that the end of the sound is not empty
    memcpy(data, waveData, m_bufferSize - 50);

    ((LPDIRECTSOUNDBUFFER)m_sharedBuffer)->Unlock(data, m_bufferSize, NULL, 0);

    data = NULL;

    TDeleteArray(waveData);
}
