#ifndef __TGAMESTATE_H__
#define __TGAMESTATE_H__

// a state the game can be in
// main menu, options, etc

#ifndef __TSTRING_H__
#include "TString.h"
#endif

class TGameState
{
public:
	TGameState() {}
	virtual ~TGameState() {}

	virtual void OnEntry() {}
	virtual void OnExit() {}

	const TString& GetStateName() const
	{
		return m_stateName;
	};

protected:
	TString m_stateName;
};

#endif