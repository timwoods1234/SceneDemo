#include "TWindowsApplication.h"
#include "TWindowsDebug.h"
#include "TConfig.h"
#include "TError.h"
#include "TLocator.h"
#include "TServiceCreator.h"

//-------------------------------------------------------------------------------
TWindowsApplication* s_currentApplication = NULL;

//-------------------------------------------------------------------------------
LRESULT TWindowsApplication::MsgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool minOrMaxed = false;

	RECT clientRect = {0, 0, 0, 0};

	switch (msg)
	{
		case WM_PAINT:
			{
				ValidateRect(m_window, NULL);
			}
			return 0;

		case WM_ACTIVATE:
			{
				if (LOWORD(wParam) == WA_INACTIVE)
				{
					m_paused = true;
				}
				else
				{
					m_paused = false;
				}
			}
			return 0;

		case WM_CLOSE:
			{
				DestroyWindow(m_window);
			}
			return 0;

		case WM_SYSCOMMAND:							// Intercept System Commands
			{
				switch (wParam)						// Check System Calls
				{
					case SC_KEYMENU:
					case SC_SCREENSAVE:
					case SC_MONITORPOWER:
					{
						return 0;						// Prevent From Happening
					}
				}
			}
			break;

		case WM_DESTROY:
			{
				DestroyWindow(m_window);
				Quit();
			}
			return 0;
	}

	return DefWindowProc(m_window, msg, wParam, lParam);
}

//-------------------------------------------------------------------------------
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (s_currentApplication != NULL)
	{
		return s_currentApplication->MsgProc(msg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

//-------------------------------------------------------------------------------
TWindowsApplication::TWindowsApplication(HINSTANCE hInst, const char* title)
:	TApplicationInterface()
{
	TWindowsDebug* debugSystem = TNew TWindowsDebug();
	TLocator::RegisterDebugSystem(debugSystem);

	if (!SetupWindow(hInst, title))
	{
		return;
	}

	s_currentApplication = this;
	m_initialized = true;

	TLocator::RegisterApplication(this);

	TServiceCreator::CreateServices();
}

//-------------------------------------------------------------------------------
TWindowsApplication::~TWindowsApplication()
{
	TServiceCreator::DestroyServices();

	TDebugInterface* debugSystem = TLocator::GetDebugSystem();
	TSafeDelete(debugSystem);
}

//-------------------------------------------------------------------------------
bool TWindowsApplication::SetupWindow(HINSTANCE hInst, const char* title)
{
	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = MainWndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInst;
	wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = "TGameWndClassName";

	if (!RegisterClass(&wc))
	{
		TASSERT(false, "RegisterClass FAILED");
		PostQuitMessage(0);

		return false;
	}

	HWND hWindow = CreateWindow("TGameWndClassName", title, 
		WS_OVERLAPPEDWINDOW, 0, 0, 
		(int)TConfig::Get()->GetScreenWidth(), 
		(int)TConfig::Get()->GetScreenHeight(), 
		NULL, NULL, hInst, NULL);

	if (!hWindow)
	{
		TASSERT(false, "CreateWindow FAILED");
		Quit();

		return false;
	}

	SetWindowLong(hWindow, GWL_STYLE, GetWindowLong(hWindow, GWL_STYLE) & ~WS_MINIMIZEBOX);
	SetWindowLong(hWindow, GWL_STYLE, GetWindowLong(hWindow, GWL_STYLE) & ~WS_THICKFRAME);
	SetWindowLong(hWindow, GWL_STYLE, GetWindowLong(hWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX);

	ShowWindow(hWindow, SW_SHOWDEFAULT);
	UpdateWindow(hWindow);

	m_instance = hInst;
	m_window = hWindow;

	return true;
}

//-------------------------------------------------------------------------------
void TWindowsApplication::Run()
{
    MSG msg; 
	msg.message = WM_NULL;

    while((msg.message != WM_QUIT))
    {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{	
			// If there are Window messages then process them.
            TranslateMessage( &msg );
            DispatchMessage( &msg );
		}
		else
		{
			if (m_paused)
			{
				Sleep(20);
				continue;
			}

			TApplicationInterface::Run();
		}
    }

	//return (int)msg.wParam;
}

//-------------------------------------------------------------------------------
void TWindowsApplication::Quit()
{
	PostQuitMessage(0);
}

//-------------------------------------------------------------------------------
HWND TWindowsApplication::GetWindow() const
{
	return m_window;
}

//-------------------------------------------------------------------------------
HINSTANCE TWindowsApplication::GetInstance() const
{
	return m_instance;
}
