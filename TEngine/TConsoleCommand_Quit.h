#ifndef __TCONSOLECOMMAND_QUIT_H__
#define __TCONSOLECOMMAND_QUIT_H__

#ifndef __TCONSOLECOMMANDBASE_H__
#include "TConsoleCommandBase.h"
#endif

class TConsoleCommand_Quit : public TConsoleCommandBase
{
public:
	TConsoleCommand_Quit();

	~TConsoleCommand_Quit();

private:
	void Trigger(const TString& command);
};

#endif
