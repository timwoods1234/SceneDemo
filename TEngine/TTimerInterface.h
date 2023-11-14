#ifndef __TTIMERINTERFACE_H__
#define __TTIMERINTERFACE_H__

class TTimerInterface
{
public:
	TTimerInterface();

	virtual ~TTimerInterface() {}
	virtual float GetAppTime() const = 0;
	virtual void Update() = 0;
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual unsigned long GetSystemTime() const = 0; 

	float GetElapsedTime() const;
	void SetPause(bool pause);
	void SetTimeMultiplier(float multiplier);
	float GetTimeMultiplier() const;
	unsigned int GetFrameCount() const;

protected:
	unsigned int m_frameCount;
	float m_timeMultiplier;
	float m_elapsedTime;
	bool m_paused;
};

#endif
