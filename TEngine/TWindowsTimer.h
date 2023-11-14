#ifndef __TWINDOWSTIMER_H__
#define __TWINDOWSTIMER_H__

#ifndef __TTIMERINTERFACE_H__
#include "TTimerInterface.h"
#endif

#ifndef __TPLATFORM_H__
#include "TPlatform.h"
#endif

#ifdef TPLATFORM_WIN

class TWindowsTimer : public TTimerInterface
{
public:
	TWindowsTimer();
	~TWindowsTimer();

	float GetAppTime() const;
	void Update();
	void Start();
	void Stop();
	unsigned long GetSystemTime() const;

private:
	__int64 m_ticksPerSec;
	__int64 m_currElapsedTime;
	__int64 m_lastElapsedTime;
	__int64 m_baseTime;
	__int64 m_stopTime;

	float m_secsPerCount;

	bool m_timerStopped;
};

#endif //#ifdef __TPLATFORM_WIN

#endif
