#ifndef __TTRIANGLE_H__
#define __TTRIANGLE_H__

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

class TTriangle
{
public:
	TVector3 v1, v2, v3;
	TVector3 normal;
};

#endif
