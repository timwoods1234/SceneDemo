#ifndef __TCONSOLE_H__
#define __TCONSOLE_H__ 

// In-game console

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TSTRINGBUILDER_H__
#include "TStringBuilder.h"
#endif

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

class TScreenOutputStream;
class TConsoleCommandBase;

class TConsole : public TSingleton<TConsole>
{
public:
	TConsole();

	~TConsole();

	void Update();

	void Render();

	void AddLine(TString& newLine);

    void AddCommandHandler(TConsoleCommandBase* command);

	void Clear();

	bool IsVisible() const;

	void SetVisible(bool visible);

protected:
	TDynamicSet<TString> m_displayHistory;

	TDynamicSet<TConsoleCommandBase*> m_commandHandlers;

	TScreenOutputStream* m_outputStream;

	TString m_previousCommand;

	TStringBuilder m_currentCommand;

	bool m_visible;

	unsigned int m_maxVisibleHistory;
};

#endif
