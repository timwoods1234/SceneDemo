#include "TConsoleCommand_ToggleStats.h"
#include "TLocator.h"
#include "TApplicationInterface.h"
#include "TConsole.h"
#include "TGameStats.h"

//-------------------------------------------------------------------------------
TConsoleCommand_ToggleStats::TConsoleCommand_ToggleStats()
{
	m_commandTrigger = "stats";
}

//-------------------------------------------------------------------------------
TConsoleCommand_ToggleStats::~TConsoleCommand_ToggleStats()
{
}

//-------------------------------------------------------------------------------
void TConsoleCommand_ToggleStats::Trigger(const TString& command)
{
	bool enableStats = !TGameStats::Get()->Enabled();

	TGameStats::Get()->Enable(enableStats);

    TString output;

    if (enableStats)
    {
        output = "Metrics Enabled";
    }
    else
    {
        output = "Metrics Disabled";
    }

    TConsole::Get()->AddLine(output);
}