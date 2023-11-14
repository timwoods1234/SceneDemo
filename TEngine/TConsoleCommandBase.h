#ifndef __TCONSOLECOMMANDBASE_H__
#define __TCONSOLECOMMANDBASE_H__

#ifndef __TSTRING_H__
#include "TString.h"
#endif

class TConsoleCommandBase
{
public:
	TConsoleCommandBase();

	~TConsoleCommandBase();

	virtual void ReceiveCommand(const TString& command);

protected:
	virtual void Trigger(const TString& command) = 0;

	bool ShouldTrigger(const TString& command) const;

	TString m_commandTrigger;
};

#endif
