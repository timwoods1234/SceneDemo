#include "TGameStats.h"
#include "TTimerInterface.h"
#include "TMesh.h"
#include "TLocator.h"
#include "TRendererInterface.h"
#include "TFont.h"
#include "TEventUpdate.h"
#include "TEventUIRender.h"
#include "TStringPool.h"
#include "TScreenOutputStream.h"

//-------------------------------------------------------------------------------
DefineSingleton(TGameStats);

//-------------------------------------------------------------------------------
TGameStats::TGameStats()
:	m_framesPerSecond(0.f),
	m_msPerFrame(0.f),
	m_frameCountUpdateRate(30),
	m_lastFrame(0),
	m_lastTime(0.f),
	m_enabled(false),
    m_lastFrameDrawCalls(0),
    m_currentFrawCalls(0)
{
	m_outputStream = TNew TScreenOutputStream();
	m_outputStream->SetOffset(24);
	m_outputStream->SetColor(TColor::White());

    m_lastTime = TLocator::GetTimer()->GetAppTime();
}

//-------------------------------------------------------------------------------
TGameStats::~TGameStats()
{
	Enable(false);

	TSafeDelete(m_outputStream);
}

//-------------------------------------------------------------------------------
void TGameStats::Update(float elapsedTime)
{
	int frameCount = TLocator::GetTimer()->GetFrameCount();
	float now = TLocator::GetTimer()->GetAppTime();

	if (frameCount >= m_lastFrame + m_frameCountUpdateRate)
	{
		int frameCountDifference = frameCount - m_lastFrame;
		m_lastFrame = frameCount;

		float timeDifference = now - m_lastTime;

		m_framesPerSecond = ((float)frameCountDifference) / (float)timeDifference;
		m_lastTime = now;

        m_msPerFrame = 1000 * (timeDifference / frameCountDifference);
	}
}

//-------------------------------------------------------------------------------
void TGameStats::Render()
{
	m_outputStream->SetPosition(10, 10);

	char buffer[256];

	sprintf_s(buffer, 256, "Frames Per Second: %.1f", m_framesPerSecond);
	m_outputStream->WriteString(buffer);
	
	sprintf_s(buffer, 256, "Frame Speed (ms): %.2f", m_msPerFrame);
	m_outputStream->WriteString(buffer);

	sprintf_s(buffer, 256, "Triangles: %d", m_triangleCount);
	m_outputStream->WriteString(buffer);

	sprintf_s(buffer, 256, "Vertices: %d", m_vertCount);
	m_outputStream->WriteString(buffer);
	
	sprintf_s(buffer, 256, "Draw Calls: %d", m_lastFrameDrawCalls);
	m_outputStream->WriteString(buffer);
	
	sprintf_s(buffer, 256, "%d strings (%d bytes)", TStringPool::GetNumAllocations(), TStringPool::GetAllocatedBytes());
	m_outputStream->WriteString(buffer);
}

//-------------------------------------------------------------------------------
bool TGameStats::Enabled() const
{
	return m_enabled;
}

//-------------------------------------------------------------------------------
void TGameStats::Enable(bool enabled)
{
	if (m_enabled != enabled)
	{
		m_enabled = enabled;

		if (m_enabled)
		{
			TEventUpdate::Get()->Register(this, &TGameStats::Update);
			TEventUIRender::Get()->Register(this, &TGameStats::Render);
		}
		else
		{
			TEventUpdate::Get()->Unregister(this, &TGameStats::Update);
			TEventUIRender::Get()->Unregister(this, &TGameStats::Render);
		}
	}
}

//-------------------------------------------------------------------------------
void TGameStats::OnBeginFrame()
{
    m_lastFrameDrawCalls = m_currentFrawCalls;
    m_currentFrawCalls = 0;

    m_vertCount = 0;
    m_triangleCount = 0;
}

//-------------------------------------------------------------------------------
void TGameStats::OnEndFrame(int drawCalls, int vertCount, int triangleCount)
{
    m_currentFrawCalls += drawCalls;
    m_vertCount += vertCount;
    m_triangleCount += triangleCount;
}