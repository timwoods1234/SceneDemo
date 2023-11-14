#ifndef __TDIRECT3D_H__
#define __TDIRECT3D_H__

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#if defined(DEBUG) | defined(_DEBUG)
#	ifndef D3D_DEBUG_INFO
#	define D3D_DEBUG_INFO
#	endif
#endif

#ifndef __D3DX9_H__
#include <d3dx9.h>
#endif

#endif
