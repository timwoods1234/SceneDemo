#ifndef __TVERTEXUI_H__
#define __TVERTEXUI_H__

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

struct TVertexUI
{
	TVertexUI()
	:	position(0,0,0),
		texture(0,0)
	{
	}

	TVertexUI(TVector3 pos, TVector2 tex)
	:	position(pos),
		texture(tex)
	{
	}

	TVector3 position;
	TVector2 texture;
};

#endif