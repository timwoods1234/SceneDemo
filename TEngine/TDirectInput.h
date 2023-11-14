#ifndef __TDIRECTINPUT_H__
#define __TDIRECTINPUT_H__

// Keyboard & Mouse using Direct Input

#ifndef __TINPUTINTERFACE_H__
#include "TInputInterface.h"
#endif

#ifndef __DINPUT_INCLUDED__
#	define DIRECTINPUT_VERSION 0x0800
#	include <dinput.h>
#endif

class TDirectInput : public TInputInterface
{
public:
	TDirectInput(HWND window, HINSTANCE instance);

	~TDirectInput();

	bool					Init(HINSTANCE instance, HWND window);

	bool					Update();

	bool					IsDown(unsigned int nID);

	bool					IsPressed(unsigned int nID);

	bool					IsReleased(unsigned int nID);

	bool					IsAnyKeyPressed();

	bool					IsAnyKeyDown();

	char					GetPressedChar();

	long					GetXAmt();

	long					GetYAmt();

	void					GetMousePosition(TVector2& outputPosition);

private:
	void					Release();

	HWND					m_window;

	LPDIRECTINPUT8			m_directInput; 
	LPDIRECTINPUTDEVICE8	m_keyboard;
    LPDIRECTINPUTDEVICE8	m_mouse;
	DIMOUSESTATE2			m_mouseInput;

	char					m_keys[256];		//key states
	char					m_oldKeys[256];
	long					m_xamt;
	long					m_yamt;
};

#endif
