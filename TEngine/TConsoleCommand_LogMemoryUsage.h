#ifndef __TCONSOLECOMMAND_LOGMEMORYUSAGE_H__
#define __TCONSOLECOMMAND_LOGMEMORYUSAGE_H__

#ifndef __TCONSOLECOMMANDBASE_H__
#include "TConsoleCommandBase.h"
#endif

class TConsoleCommand_LogMemoryUsage : public TConsoleCommandBase
{
public:
    TConsoleCommand_LogMemoryUsage();

    ~TConsoleCommand_LogMemoryUsage();

private:
    void Trigger(const TString& command);
};

#endif

