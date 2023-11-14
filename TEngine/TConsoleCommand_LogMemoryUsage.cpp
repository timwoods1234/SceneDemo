#include "TConsoleCommand_LogMemoryUsage.h"
#include "TConsole.h"
#include "TMemoryManager.h"

//-------------------------------------------------------------------------------
TConsoleCommand_LogMemoryUsage::TConsoleCommand_LogMemoryUsage()
{
    m_commandTrigger = "memory";
}

//-------------------------------------------------------------------------------
TConsoleCommand_LogMemoryUsage::~TConsoleCommand_LogMemoryUsage()
{
}

//-------------------------------------------------------------------------------
void TConsoleCommand_LogMemoryUsage::Trigger(const TString& command)
{
    int heapAllocations;
    int heapBytes;
    int poolAllocations;
    int poolBytes;

    TMemoryManager::GetSummary(heapAllocations, heapBytes, poolAllocations, poolBytes);

    TString heapSummary = TString::Format("Heaped Memory allocated: %d bytes in %d allocations", heapBytes, heapAllocations);
    TString poolSummary = TString::Format("Pooled Memory allocated: %d bytes in %d allocations", poolBytes, poolAllocations);

    TConsole::Get()->AddLine(heapSummary);
    TConsole::Get()->AddLine(poolSummary);


    int stringAllocations = TStringPool::GetNumAllocations();
    int stringBytes = TStringPool::GetAllocatedBytes();
    TString stringSummary = TString::Format("String Memory allocated: %d bytes in %d allocations", stringBytes, stringAllocations);
    
    TConsole::Get()->AddLine(stringSummary);
}