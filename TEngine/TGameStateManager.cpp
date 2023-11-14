#include "TGameState.h"
#include "TGameStateManager.h"
#include "TMemory.h"
#include "TError.h"

//-------------------------------------------------------------------------------
TGameStateManager::TGameStateManager()
{
	m_currentState = NULL;
}

//-------------------------------------------------------------------------------
TGameStateManager::~TGameStateManager()
{
	if (m_currentState != NULL)
	{
		m_currentState->OnExit();
	}

	for (unsigned int index = 0; index < m_stateList.GetSize(); index++)
	{
		TSafeDelete(m_stateList[index]);
	}
}

//-------------------------------------------------------------------------------
void TGameStateManager::AddState(TGameState *pState)
{
	for (unsigned int index = 0; index < m_stateList.GetSize(); index++)
	{
		if(m_stateList[index]->GetStateName() == pState->GetStateName())
		{
			TDebugPrint(("[TGameStateManager::AddState] Attempted to add state twice (%s)", pState->GetStateName().GetPointer() ));
			return;
		}
	}

	m_stateList.Add(pState);
}

//-------------------------------------------------------------------------------
bool TGameStateManager::SwitchState(const char* stateName)
{
	for (unsigned int index = 0; index < m_stateList.GetSize(); index++)
	{
		if(m_stateList[index]->GetStateName() == stateName)
		{
			if(m_currentState)
			{
				m_currentState->OnExit();
			}

			m_currentState = m_stateList[index];
			m_currentState->OnEntry();

			return true;
		}
	}

	TDebugPrint(("[TGameStateManager::SwitchState] Couldn't find state '%s'", stateName));
	return false;
}

//-------------------------------------------------------------------------------
const char* TGameStateManager::GetCurrentStateName()
{
	return m_currentState->GetStateName().GetPointer();
}
