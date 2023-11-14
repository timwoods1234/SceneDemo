#ifndef __TVERTEX_H__
#define __TVERTEX_H__

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

// default, generic vertex format shared by most meshes

struct TVertex
{
	TVertex()
	:	position(0,0,0),
		normal(0,0,0),
		texture(0,0)
	{
	}

	TVertex(TVector3 pos, TVector3 norm, TVector2 tex)
	:	position(pos),
		normal(norm),
		texture(tex)
	{
	}

	TVector3 position;
	TVector3 normal;
	TVector2 texture;
};

#endif