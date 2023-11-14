#ifndef __POSVERTEX_H__
#define __POSVERTEX_H__

#ifndef __TENGINEINCLUDED_H__
#include "TEngine.h"
#endif

struct PosVertex
{
	PosVertex()
	{
		position.Set(0, 0, 0);
	}

	PosVertex(TVector3 pos)
	:	position(pos)
	{

	}

	TVector3 position;
};

#endif