#include "TCursorManager.h"
#include "TLocator.h"
#include "TInputInterface.h"
#include "TInputMappings.h"

//-------------------------------------------------------------------------------
DefineSingleton(TCursorManager);

#ifdef _WINDOWS_
//-------------------------------------------------------------------------------
unsigned int GetTouchCount()
{
	if (TLocator::GetInput()->IsDown(TINPUT_MOUSE_LEFT) || TLocator::GetInput()->IsDown(TINPUT_MOUSE_RIGHT))
	{
		return 1;
	}

	return 0;
}

//-------------------------------------------------------------------------------
unsigned int GetTouchId(int touchIndex)
{
	return 0;
}

//-------------------------------------------------------------------------------
int GetTouchIndex(int touchId)
{
	if (GetTouchCount() > 0)
	{
		return 0;
	}

	return -1;
}

//-------------------------------------------------------------------------------
TouchPhase GetTouchPhase(int touchIndex)
{
	if (TLocator::GetInput()->IsPressed(TINPUT_MOUSE_LEFT) || TLocator::GetInput()->IsPressed(TINPUT_MOUSE_RIGHT))
	{
		return Began;
	}
	else if (TLocator::GetInput()->IsReleased(TINPUT_MOUSE_LEFT) || TLocator::GetInput()->IsReleased(TINPUT_MOUSE_RIGHT))
	{
		return Ended;
	}
	else
	{
		return Moved;
	}
}

//-------------------------------------------------------------------------------
void GetTouchPosition(int touchIndex, TVector2& result)
{
	TLocator::GetInput()->GetMousePosition(result);
}
#else	// #ifdef _WINDOWS_
//-------------------------------------------------------------------------------
unsigned int GetTouchCount()
{
	return 0;
}

//-------------------------------------------------------------------------------
unsigned int GetTouchId(int touchIndex)
{
	return 0;
}

//-------------------------------------------------------------------------------
int GetTouchIndex(int touchId)
{
	return -1;
}

//-------------------------------------------------------------------------------
TouchPhase GetTouchPhase(int touchIndex)
{
	return Moved;
}

//-------------------------------------------------------------------------------
void GetTouchPosition(int touchIndex, TVector2& result)
{
}
#endif	// #ifdef _WINDOWS_

//-------------------------------------------------------------------------------
TCursorManager::TCursorManager()
{
}

//-------------------------------------------------------------------------------
TCursorManager::~TCursorManager()
{
}

//-------------------------------------------------------------------------------
unsigned int TCursorManager::GetNumCursors() const
{
	return m_cursorEntries.GetSize();
}

//-------------------------------------------------------------------------------
void TCursorManager::Update()
{
	UpdateCursorList();
}

//-------------------------------------------------------------------------------
const TCursorEntry& TCursorManager::GetCursorEntry(int index) const
{
	return m_cursorEntries[index];
}

//-------------------------------------------------------------------------------
void TCursorManager::UpdateCursorList()
{
	for (unsigned int index = 0; index < m_cursorEntries.GetSize(); index++)
	{
		if (!m_cursorEntries[index].down)
		{
			m_cursorEntries.RemoveAt(index);
			index--;
		}
		else
		{
			m_cursorEntries[index].wasDown = true;
		}
	}

	unsigned int numCursorEntries = m_cursorEntries.GetSize();

	for (unsigned int index = 0; index < numCursorEntries; index++)
	{
		int touchIndex = GetTouchIndex(m_cursorEntries[index].id);
		
		if (touchIndex != -1)
		{
			if (GetTouchPhase(touchIndex) == Began)
			{
				m_cursorEntries[index].down = false;
				m_cursorEntries[index].wasDown = true;					
				m_cursorEntries[index].dead = true;
			}
			else
			{
    			m_cursorEntries[index].oldPosition = m_cursorEntries[index].position;

				GetTouchPosition(touchIndex, m_cursorEntries[index].position);
			}
		}
		else
		{
    		TVector2 delta = m_cursorEntries[index].position - m_cursorEntries[index].oldPosition;
    		m_cursorEntries[index].position += delta;
			m_cursorEntries[index].down = false;
		}
	}

	unsigned int touchCount = GetTouchCount();

	for (unsigned int index = 0; index < touchCount; index++)
	{
		bool isNewTouch = true;
		int touchId = GetTouchId(index);

		for (unsigned int testIndex = 0; testIndex < numCursorEntries; testIndex++)
		{
			if (touchId == m_cursorEntries[testIndex].id && !m_cursorEntries[testIndex].dead)
			{
				isNewTouch = false;
				break;
			}
		}

		if (isNewTouch)
		{
			TCursorEntry newCursor;
			
			newCursor.id = touchId;
			newCursor.oldPosition = newCursor.position;
			newCursor.down = true;
			newCursor.wasDown = false;
			newCursor.dead = false;
			
			GetTouchPosition(index, newCursor.position);
			
			m_cursorEntries.Add(newCursor);
		}
	}
}
