#ifndef __TGAMESTATEMANAGER_H__
#define __TGAMESTATEMANAGER_H__

// Contains a list of game states 
// handles activation and de-activation

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class TGameState;

class TGameStateManager : public TSingleton<TGameStateManager>
{
public:
	TGameStateManager();

	~TGameStateManager();

	void AddState(TGameState* state);

	bool SwitchState(const char* stateName);

	const char* GetCurrentStateName();

private:
	TGameState* m_currentState;
	TDynamicSet<TGameState*> m_stateList;
};

DefineSingleton(TGameStateManager);


#endif
