#include "TTimerInterface.h"

//-------------------------------------------------------------------------------
TTimerInterface::TTimerInterface()
:	m_frameCount(0),
	m_timeMultiplier(1.f),
	m_elapsedTime(0.f),
	m_paused(false)
{
}

//-------------------------------------------------------------------------------
float TTimerInterface::GetElapsedTime() const
{
	return m_elapsedTime;
}

//-------------------------------------------------------------------------------
void TTimerInterface::SetPause(bool pause)
{
	if (m_paused != pause)
	{
		m_paused = pause;

		if (m_paused)
		{
			Start();
		}
		else
		{
			Stop();
		}
	}
}

//-------------------------------------------------------------------------------
void TTimerInterface::SetTimeMultiplier(float multiplier)
{
	m_timeMultiplier = multiplier;
}

//-------------------------------------------------------------------------------
float TTimerInterface::GetTimeMultiplier() const
{
	return m_timeMultiplier;
}

//-------------------------------------------------------------------------------
unsigned int TTimerInterface::GetFrameCount() const
{
	return m_frameCount;
}
