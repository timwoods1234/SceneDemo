#ifndef __TCURSORMANAGER_H__
#define __TCURSORMANAGER_H__

#ifndef __TCURSORENTRY_H__
#include "TCursorEntry.h"
#endif

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class TCursorManager : public TSingleton<TCursorManager>
{
public:
	TCursorManager();

	~TCursorManager();

	void Update();

	unsigned int GetNumCursors() const;

	const TCursorEntry& GetCursorEntry(int index) const;

private:
	void UpdateCursorList();

	TDynamicSet<TCursorEntry> m_cursorEntries;
};

#endif
