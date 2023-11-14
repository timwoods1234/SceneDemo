#include "TConsoleCommandBase.h"
#include "TStringHelper.h"

//-------------------------------------------------------------------------------
TConsoleCommandBase::TConsoleCommandBase()
{
}

//-------------------------------------------------------------------------------
TConsoleCommandBase::~TConsoleCommandBase()
{
}

//-------------------------------------------------------------------------------
void TConsoleCommandBase::ReceiveCommand(const TString& command)
{
	if (ShouldTrigger(command))
	{
		Trigger(command);
	}
}

//-------------------------------------------------------------------------------
bool TConsoleCommandBase::ShouldTrigger(const TString& command) const
{
	TString commandToTest = command;

	if (command.Contains(" "))
	{
		commandToTest = command.SubString(0, command.IndexOf(' '));
	}

	if (m_commandTrigger == commandToTest)
	{
		return true;
	}

	return false;
}
