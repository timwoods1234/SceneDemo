#include "TWindowsTimer.h"
#include "TLocator.h"

//-------------------------------------------------------------------------------
TWindowsTimer::TWindowsTimer()
:	m_ticksPerSec(0),
	m_currElapsedTime(0),
	m_lastElapsedTime(0),
	m_baseTime(0),
	m_stopTime(0),
	m_secsPerCount(0.f),
	m_timerStopped(false)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_ticksPerSec);
	m_secsPerCount = 1.0f / (float)m_ticksPerSec;

	QueryPerformanceCounter((LARGE_INTEGER*)&m_lastElapsedTime);
}

//-------------------------------------------------------------------------------
TWindowsTimer::~TWindowsTimer()
{
}

//-------------------------------------------------------------------------------
float TWindowsTimer::GetAppTime() const
{
	return (float) (m_currElapsedTime - m_baseTime) * m_secsPerCount;
}

//-------------------------------------------------------------------------------
void TWindowsTimer::Update()
{
    // Get either the current time or the stop time, depending on whether we're stopped
    if(m_stopTime != 0)
	{
        m_currElapsedTime = m_stopTime;
	}
    else
	{
        QueryPerformanceCounter( (LARGE_INTEGER*)&m_currElapsedTime );
	}

    m_elapsedTime = (m_currElapsedTime - m_lastElapsedTime) * m_secsPerCount;

	if (m_elapsedTime > 1.f)
	{
		// ensure no undesired behaviour if the app idles between frames
		m_elapsedTime = 0.01f;
	}

	m_elapsedTime *= m_timeMultiplier;

    m_lastElapsedTime = m_currElapsedTime;

	++m_frameCount;
}

//-------------------------------------------------------------------------------
void TWindowsTimer::Start()
{
    if (m_timerStopped)
	{
        m_baseTime += m_currElapsedTime - m_stopTime;
	}

    m_stopTime = 0;
    m_lastElapsedTime = m_currElapsedTime;
    m_timerStopped = false;
}

//-------------------------------------------------------------------------------
void TWindowsTimer::Stop()
{
	m_stopTime = m_currElapsedTime;
	m_lastElapsedTime = m_currElapsedTime;

	m_timerStopped = true;
}

//-------------------------------------------------------------------------------
unsigned long TWindowsTimer::GetSystemTime() const
{
	return timeGetTime();
}
