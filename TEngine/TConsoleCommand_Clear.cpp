#include "TConsoleCommand_Clear.h"
#include "TConsole.h"

//-------------------------------------------------------------------------------
TConsoleCommand_Clear::TConsoleCommand_Clear()
{
	m_commandTrigger = "clear";
}

//-------------------------------------------------------------------------------
TConsoleCommand_Clear::~TConsoleCommand_Clear()
{
}

//-------------------------------------------------------------------------------
void TConsoleCommand_Clear::Trigger(const TString& command)
{
	TConsole::Get()->Clear();
}