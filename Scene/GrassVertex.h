#ifndef __GRASSVERTEX_H__
#define __GRASSVERTEX_H__

#ifndef __TENGINEINCLUDED_H__
#include "TEngine.h"
#endif

struct GrassVertex
{
	GrassVertex()
	:	position(0, 0, 0),
		billboardPosition(0, 0, 0),
		textureCoords(0, 0),
		amplitude(0.f),
		colourOffset(0, 0, 0, 0)
	{
	}

	GrassVertex(const TVector3& pos, const TVector2& texCoords, float ampl, const TVector4& colour)
	{
		position = pos;
		textureCoords = texCoords;
		amplitude = ampl;
		colourOffset = colour;
	}

	TVector3 position;
	TVector3 billboardPosition;
	TVector2 textureCoords;
	float amplitude;
	TVector4 colourOffset;
};

#endif
