#ifndef __TGAMESTATS_H__
#define __TGAMESTATS_H__

// displays metrics, e.g. frame rate

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

#include "TSingleton.h"

class TScreenOutputStream;

class TGameStats : public TEventListener,
				   public TSingleton<TGameStats>
{
public:
	TGameStats();

	~TGameStats();

	void Update(float elapsedTime);

    void Render();

	void Enable(bool enabled);

	bool Enabled() const;

    void OnBeginFrame();

    void OnEndFrame(int drawCalls, int vertCount, int triangleCount);

private:
	TScreenOutputStream* m_outputStream;

	int		m_frameCountUpdateRate;	// how many frames pass before an update
	bool	m_enabled;
	int		m_lastFrame;
	float	m_lastTime;

	float	m_framesPerSecond;
	float	m_msPerFrame;

    int     m_currentFrawCalls;
    int     m_lastFrameDrawCalls;
    int     m_vertCount;
    int     m_triangleCount;
};

#endif
