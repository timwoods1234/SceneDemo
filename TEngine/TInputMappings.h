#ifndef __TINPUTMAPPINGS_H__
#define __TINPUTMAPPINGS_H__

// per-platform input mappings
#include "TPlatform.h"

#ifdef TPLATFORM_WIN
#	define TINPUT_MOUSE_LEFT	0x70
#	define TINPUT_MOUSE_RIGHT	0x73
#	define TINPUT_CONSOLE		0x29	//DIK_GRAVE
#	define TINPUT_RETURN		0x1C	//DIK_RETURN
#	define TINPUT_PGDN			0xD1	//DIK_PGDN
#	define TINPUT_PGUP			0xC9	//DIK_PGUP
#	define TINPUT_LEFT			0xCB	//DIK_LEFT
#	define TINPUT_RIGHT			0xCD	//DIK_RIGHT
#	define TINPUT_UP			0xC8	//DIK_UP
#	define TINPUT_DOWN			0xD0	//DIK_DOWN
#	define TINPUT_BACKSPACE		0x0E	//DIK_BACKSPACE
#	define TINPUT_SPACEBAR		0x39	//DIK_SPACE
#	define TINPUT_1				0x02	//DIK_1
#	define TINPUT_2				0x03	//DIK_2
#	define TINPUT_3				0x04	//DIK_3
#	define TINPUT_4				0x05	//DIK_4
#	define TINPUT_LSHIFT		0x2A	//DIK_LSHIFT
#	define TINPUT_W				0x11	//DIK_W
#	define TINPUT_A				0x1E	//DIK_A
#	define TINPUT_S				0x1F	//DIK_S
#	define TINPUT_D				0x20	//DIK_D
#	define TINPUT_Q				0x10	//DIK_Q
#	define TINPUT_E				0x12	//DIK_E

#else
#	define TINPUT_MOUSE_LEFT	0
#	define TINPUT_MOUSE_RIGHT	0
#	define TINPUT_CONSOLE		0
#	define TINPUT_RETURN		0
#	define TINPUT_PGDN			0
#	define TINPUT_PGUP			0
#	define TINPUT_LEFT			0
#	define TINPUT_RIGHT			0
#	define TINPUT_UP			0
#	define TINPUT_DOWN			0
#	define TINPUT_BACKSPACE		0
#	define TINPUT_SPACEBAR		0
#	define TINPUT_1				0
#	define TINPUT_2				0
#	define TINPUT_3				0
#	define TINPUT_4				0
#	define TINPUT_LSHIFT		0
#	define TINPUT_W				0
#	define TINPUT_A				0
#	define TINPUT_S				0
#	define TINPUT_D				0
#	define TINPUT_Q				0
#	define TINPUT_E				0

#endif	// #ifndef TPLATFORM_WIN

#endif
