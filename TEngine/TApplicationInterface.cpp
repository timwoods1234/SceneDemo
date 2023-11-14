#include "TApplicationInterface.h"
#include "TMemory.h"
#include "TXMLReader.h"
#include "TConfig.h"
#include "TLocator.h"
#include "TRenderQueueManager.h"
#include "TInputInterface.h"
#include "TCursorManager.h"
#include "TRendererInterface.h"
#include "TTimerInterface.h"
#include "TEventUpdate.h"
#include "TEventUIUpdate.h"
#include "TCameraManager.h"
#include "TConsole.h"
#include "TInputMappings.h"
#include "TGameStats.h"

//-------------------------------------------------------------------------------
TApplicationInterface::TApplicationInterface()
:	m_paused(false)
{
	m_initialized = false;

	TConfig::Create();
	TXMLReader configReader("Assets/Data/Engine/Config.xml", *TConfig::Get());
	TASSERT(!configReader.WasError(), "Unable to locate Config.xml");
}

//-------------------------------------------------------------------------------
TApplicationInterface::~TApplicationInterface()
{
	TConfig::Destroy();
}

//-------------------------------------------------------------------------------
void TApplicationInterface::UpdateInput()
{
	TLocator::GetInput()->Update();
	TCursorManager::Get()->Update();
}

//-------------------------------------------------------------------------------
void TApplicationInterface::Run()
{
	if (TLocator::GetInput()->IsPressed(TINPUT_CONSOLE))
	{
		bool consoleVisible = TConsole::Get()->IsVisible();

		TConsole::Get()->SetVisible(!consoleVisible);
	}

	TLocator::GetTimer()->Update();

	UpdateInput();

	if (TConsole::Get()->IsVisible())
	{
		TConsole::Get()->Update();
	}
	else
	{
		TEventUpdate::Get()->Execute(TLocator::GetTimer()->GetElapsedTime());

		TEventUIUpdate::Get()->Execute();
	}

	Render();
}

//-------------------------------------------------------------------------------
void TApplicationInterface::Render()
{
	TLocator::GetRenderer()->BeginFrame();

	if (TConsole::Get()->IsVisible())
	{
		TConsole::Get()->Render();
	}
	else
	{
		TCameraManager::Get()->OnRender();

		if (TGameStats::Get()->Enabled() && !TConsole::Get()->IsVisible())
		{
			TGameStats::Get()->Render();
		}
	}
	
	TLocator::GetRenderer()->EndFrame();
}
