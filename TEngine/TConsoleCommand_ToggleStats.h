#ifndef __TCONSOLECOMMAND_TOGGLESTATS_H__
#define __TCONSOLECOMMAND_TOGGLESTATS_H__

#ifndef __TCONSOLECOMMANDBASE_H__
#include "TConsoleCommandBase.h"
#endif

class TConsoleCommand_ToggleStats : public TConsoleCommandBase
{
public:
	TConsoleCommand_ToggleStats();

	~TConsoleCommand_ToggleStats();

private:
	void Trigger(const TString& command);
};

#endif