#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include "TDirectInput.h"
#include "TMemory.h"
#include "TConfig.h"
#include "TLocator.h"
#include "TWindowsApplication.h"
#include "TVector2.h"

//-------------------------------------------------------------------------------
TDirectInput::TDirectInput(HWND window, HINSTANCE instance)
{
	m_window = window;

    m_directInput = NULL;
    m_keyboard = NULL;
	m_mouse = NULL;

	if (!(Init(instance, window)))
	{
		TASSERT(false, "Failed to initialize TDirectInput");

		TLocator::GetApplication()->Quit();
	}
}

//-------------------------------------------------------------------------------
TDirectInput::~TDirectInput()
{
	Release();
}

//-------------------------------------------------------------------------------
bool TDirectInput::Init(HINSTANCE instance, HWND window)
{
	//Clear Memory
	memset(m_oldKeys, 0, sizeof(m_oldKeys));
	memset(m_keys, 0, sizeof(m_keys));

	ZeroMemory(&m_mouseInput, sizeof(m_mouseInput));
	m_xamt = m_yamt = 0;

	DWORD coopFlags = DISCL_NONEXCLUSIVE|DISCL_FOREGROUND;

	if (!TConfig::Get()->IsWindowed())
	{
		coopFlags = DISCL_EXCLUSIVE|DISCL_FOREGROUND;
	}

	//Create the MouseKeyboardInput object
	if(FAILED(DirectInput8Create(instance, DIRECTINPUT_VERSION,
			  IID_IDirectInput8, (void**)&m_directInput, NULL)))
	{
		return false;
	}

	//Obtain interface to keyboard
	if(FAILED(m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL)))
	{
		return false;
	}

	//Set the data format for the keyboard
	if(FAILED(m_keyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return false;
	}

	//Set the cooperative level for the keyboard
	if(FAILED(m_keyboard->SetCooperativeLevel(window, DISCL_NONEXCLUSIVE|DISCL_FOREGROUND)))
	{
		return false;
	}

	//Acquire the keyboard
	if(m_keyboard)
	{
		m_keyboard->Acquire();
	}

    // Obtain an interface to the system mouse device.
    if( FAILED(m_directInput->CreateDevice( GUID_SysMouse, &m_mouse, NULL ) ) )
	{
        return false;
	}

    // Set the data format for the mouse
    if( FAILED(m_mouse->SetDataFormat( &c_dfDIMouse2 ) ) )
	{
        return false;
	}

    // Set the cooperative level on the mouse
    if(FAILED(m_mouse->SetCooperativeLevel(window, coopFlags)))
	{
        return false;
	}

	//Initial Values
	Update();

	return true;
}

//-------------------------------------------------------------------------------
void TDirectInput::Release()
{
	if (m_keyboard)
	{
        m_keyboard->Unacquire();
	}

    SafeRelease(m_keyboard);
	SafeRelease(m_mouse);
    SafeRelease(m_directInput);
}

//-------------------------------------------------------------------------------
bool TDirectInput::Update()
{
	memcpy(m_oldKeys, m_keys, sizeof(m_keys));

	if (FAILED(m_keyboard->GetDeviceState( sizeof(m_keys), &m_keys )))
	{
		ZeroMemory(m_keys, sizeof(m_keys));

		if (FAILED(m_keyboard->Acquire()))
		{
			return false;
		}
	}

	if (FAILED(m_mouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void**)&m_mouseInput)))
    {
		ZeroMemory(&m_mouseInput, sizeof(m_mouseInput));

        if (FAILED(m_mouse->Acquire()))
		{
			return false;
		}
    }

	m_keys[0x70]	= m_mouseInput.rgbButtons[0];
	m_keys[0x73]	= m_mouseInput.rgbButtons[1];

	m_xamt = m_mouseInput.lX;
	m_yamt = m_mouseInput.lY;

	return true;
}

//-------------------------------------------------------------------------------
bool TDirectInput::IsDown(unsigned int nID)
{
	if ((m_keys[nID] & 0x80) == 0x80)
	{
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------
bool TDirectInput::IsPressed(unsigned int nID)
{
	if ((m_keys[nID] & 0x80) && !(m_oldKeys[nID] & 0x80))
	{
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------
bool TDirectInput::IsReleased(unsigned int nID)
{
	if ((m_oldKeys[nID] & 0x80) && !(m_keys[nID] & 0x80))
	{
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------
bool TDirectInput::IsAnyKeyDown()
{
	for (int i=0; i<256; ++i)
	{
		if (IsDown(i))
		{
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------------------
bool TDirectInput::IsAnyKeyPressed()
{
	for (int i=0; i<256; ++i)
	{
		if (IsPressed(i))
		{
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------------------
char TDirectInput::GetPressedChar()
{
	HKL layout = GetKeyboardLayout(0);

	if (IsPressed(DIK_BACKSPACE))
	{
		return 8;	// backspace value
	}

	char c = 0;

	if		(IsPressed(DIK_Q))	c =  'q';
	else if (IsPressed(DIK_W))	c =  'w';
	else if (IsPressed(DIK_E))	c =  'e';
	else if (IsPressed(DIK_R))	c =  'r';
	else if (IsPressed(DIK_T))	c =  't';
	else if (IsPressed(DIK_Y))	c =  'y';
	else if (IsPressed(DIK_U))	c =  'u';
	else if (IsPressed(DIK_I))	c =  'i';
	else if (IsPressed(DIK_O))	c =  'o';
	else if (IsPressed(DIK_P))	c =  'p';
	else if (IsPressed(DIK_A))	c =  'a';
	else if (IsPressed(DIK_S))	c =  's';
	else if (IsPressed(DIK_D))	c =  'd';
	else if (IsPressed(DIK_F))	c =  'f';
	else if (IsPressed(DIK_G))	c =  'g';
	else if (IsPressed(DIK_H))	c =  'h';
	else if (IsPressed(DIK_J))	c =  'j';
	else if (IsPressed(DIK_K))	c =  'k';
	else if (IsPressed(DIK_L))	c =  'l';
	else if (IsPressed(DIK_Z))	c =  'z';
	else if (IsPressed(DIK_X))	c =  'x';
	else if (IsPressed(DIK_C))	c =  'c';
	else if (IsPressed(DIK_V))	c =  'v';
	else if (IsPressed(DIK_B))	c =  'b';
	else if (IsPressed(DIK_N))	c =  'n';
	else if (IsPressed(DIK_M))	c =  'm';
	else if (IsPressed(DIK_1))	c =  '1';
	else if (IsPressed(DIK_2))	c =  '2';
	else if (IsPressed(DIK_3))	c =  '3';
	else if (IsPressed(DIK_4))	c =  '4';
	else if (IsPressed(DIK_5))	c =  '5';
	else if (IsPressed(DIK_6))	c =  '6';
	else if (IsPressed(DIK_7))	c =  '7';
	else if (IsPressed(DIK_8))	c =  '8';
	else if (IsPressed(DIK_9))	c =  '9';
	else if (IsPressed(DIK_0))	c =  '0';

	// upper case
	if (c!=0 && (IsDown(DIK_LSHIFT) || IsDown(DIK_RSHIFT)) )
	{
		c -= ('a' - 'A');
	}

	// special characters
	if		(IsPressed(DIK_PERIOD))	c = '.';
	else if (IsPressed(DIK_MINUS))	c = '-';
	else if (IsPressed(DIK_EQUALS))	c = '=';
	else if (IsPressed(DIK_SPACE))	c = ' ';

	return c;
}

//-------------------------------------------------------------------------------
long TDirectInput::GetXAmt() 
{
	return m_xamt;
}

//-------------------------------------------------------------------------------
long TDirectInput::GetYAmt()
{
	return m_yamt; 
}

//-------------------------------------------------------------------------------
void TDirectInput::GetMousePosition(TVector2& outputPosition)
{
	POINT point;
	RECT windowRect;

	GetCursorPos(&point);
	GetWindowRect(m_window, &windowRect);

	outputPosition.x = (float)point.x - windowRect.left;
	outputPosition.y = (float)point.y - windowRect.top;
}
