#ifndef __TD3DUTIL_H__
#define __TD3DUTIL_H__

#ifndef __TDIRECT3D_H__
#include "TDirect3D.h"
#endif

namespace TD3DUtil
{
	bool CheckHardwareSupport(LPDIRECT3D9 direct3D, D3DDISPLAYMODE& displayMode);

	unsigned long GetCreateFlags(LPDIRECT3D9 direct3D);
};

#endif
