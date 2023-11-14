#ifndef __TCONSOLECOMMAND_CLEAR_H__
#define __TCONSOLECOMMAND_CLEAR_H__

#ifndef __TCONSOLECOMMANDBASE_H__
#include "TConsoleCommandBase.h"
#endif

class TConsoleCommand_Clear : public TConsoleCommandBase
{
public:
	TConsoleCommand_Clear();

	~TConsoleCommand_Clear();

private:
	void Trigger(const TString& command);
};

#endif
