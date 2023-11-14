#ifndef __TDIRECTIONALLIGHT_H__
#define __TDIRECTIONALLIGHT_H__

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

#ifndef __TCOLOR_H__
#include "TColor.h"
#endif

struct TDirectionalLight
{
	TDirectionalLight()
	{
		ambient.Set(1.f, 1.f, 1.f, 1.f);
		diffuse.Set(1.f, 1.f, 1.f, 1.f);
		specular.Set(1.f, 1.f, 1.f, 1.f);

		direction.Set(0.f, 0.f, 0.f);
	}

	TColor ambient;
	TColor diffuse;
	TColor specular;

	TVector3 direction;  
};

#endif
