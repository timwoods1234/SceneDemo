#include "TConsole.h"
#include "TScreenOutputStream.h"
#include "TLocator.h"
#include "TInputInterface.h"
#include "TInputMappings.h"
#include "TConsoleCommandBase.h"
#include "TTimerInterface.h"
#include "TGameStats.h"

#include "TConsoleCommand_Clear.h"
#include "TConsoleCommand_ToggleStats.h"
#include "TConsoleCommand_Quit.h"
#include "TConsoleCommand_LogMemoryUsage.h"

//-------------------------------------------------------------------------------
DefineSingleton(TConsole);

//-------------------------------------------------------------------------------
TConsole::TConsole()
:	m_visible(false),
	m_maxVisibleHistory(18)
{
	m_outputStream = TNew TScreenOutputStream();
	m_outputStream->SetOffset(24);

	AddCommandHandler(TNew TConsoleCommand_Clear());
    AddCommandHandler(TNew TConsoleCommand_ToggleStats());
    AddCommandHandler(TNew TConsoleCommand_Quit());
    AddCommandHandler(TNew TConsoleCommand_LogMemoryUsage());

    m_displayHistory.Add("TConsole");
}

//-------------------------------------------------------------------------------
TConsole::~TConsole()
{
    for (unsigned int index = 0; index < m_commandHandlers.GetSize(); index++)
    {
        TSafeDelete(m_commandHandlers[index]);
    }

	TSafeDelete(m_outputStream);
}

//-------------------------------------------------------------------------------
void TConsole::Update()
{
	if (TLocator::GetInput()->IsPressed(TINPUT_RETURN))
	{
		if (m_currentCommand.GetLength() > 0)
		{
			m_previousCommand = m_currentCommand.GetResult();
            m_currentCommand.Clear();

            m_displayHistory.Add(m_previousCommand);

			for (unsigned int index = 0; index < m_commandHandlers.GetSize(); index++)
			{
				m_commandHandlers[index]->ReceiveCommand(m_previousCommand);
			}

			while (m_displayHistory.GetSize() > m_maxVisibleHistory)
			{
				m_displayHistory.RemoveAt(0, true);
			}
		}
	}
	else
	{
		if (TLocator::GetInput()->IsAnyKeyPressed())
		{
			if (TLocator::GetInput()->IsPressed(TINPUT_UP))
			{
				m_currentCommand.Clear();

				m_currentCommand.Append(m_previousCommand.GetPointer());
			}
			else
			{
				char c = TLocator::GetInput()->GetPressedChar();

				if (c == 8)
				{
					// backspace
                    if (m_currentCommand.GetLength() > 0)
                    {
                        m_currentCommand.Remove(m_currentCommand.GetLength() - 1, 1);
                    }
				}
				else
				{
					m_currentCommand.Append(c);
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------
void TConsole::Render()
{
	m_outputStream->SetPosition(10, 0);

	unsigned int numEntries = m_displayHistory.GetSize();

	for (unsigned int index = 0; index < numEntries; index++)
	{
		m_outputStream->WriteString(m_displayHistory[index].GetPointer());
	}

    TVector2 position = m_outputStream->GetPosition();
    int appTime = (int)TLocator::GetTimer()->GetAppTime();

    if ( (appTime % 2) == 0)
    {
        m_outputStream->WriteString(">");
    }
    else
    {
        position.y += m_outputStream->GetLineSpacing();

        m_outputStream->SetPosition((int)position.x, (int)position.y);
    }

	if (m_currentCommand.GetLength() != 0)
	{
        position.Set(10.f, -(float)m_outputStream->GetLineSpacing());
        position += m_outputStream->GetPosition();

        m_outputStream->SetPosition((int)position.x, (int)position.y);

		m_outputStream->WriteString(m_currentCommand.GetResult());
	}
}

//-------------------------------------------------------------------------------
void TConsole::AddLine(TString& newLine)
{
	m_displayHistory.Add(newLine);
}

//-------------------------------------------------------------------------------
void TConsole::AddCommandHandler(TConsoleCommandBase* command)
{
    m_commandHandlers.Add(command);
}

//-------------------------------------------------------------------------------
void TConsole::Clear()
{
	m_displayHistory.Clear();
}

//-------------------------------------------------------------------------------
bool TConsole::IsVisible() const
{
	return m_visible;
}

//-------------------------------------------------------------------------------
void TConsole::SetVisible(bool visible)
{
    if (m_visible != visible)
    {
        if (visible)
        {
            m_currentCommand.Clear();
        }

        m_visible = visible;
    }
}