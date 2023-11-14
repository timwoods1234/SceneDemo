#include "TConsoleCommand_Quit.h"
#include "TApplicationInterface.h"
#include "TLocator.h"

//-------------------------------------------------------------------------------
TConsoleCommand_Quit::TConsoleCommand_Quit()
{
	m_commandTrigger = "quit";
}

//-------------------------------------------------------------------------------
TConsoleCommand_Quit::~TConsoleCommand_Quit()
{
}

//-------------------------------------------------------------------------------
void TConsoleCommand_Quit::Trigger(const TString& command)
{
	TLocator::GetApplication()->Quit();
}