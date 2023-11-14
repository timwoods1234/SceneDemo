#ifndef __TPOINTLIGHT_H__
#define __TPOINTLIGHT_H__

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

#ifndef __TCOLOR_H__
#include "TColor.h"
#endif

struct TPointLight
{
	TPointLight()
	{
		diffuse.Set(1.f, 1.f, 1.f, 1.f);
		ambient.Set(1.f, 1.f, 1.f, 1.f);
		specular.Set(1.f, 1.f, 1.f, 1.f);

		attenuation.Set(0.f, 0.f, 0.f);
		position.Set(0.f, 0.f, 0.f);
	}

	TColor diffuse;
	TColor ambient;
	TColor specular;

	TVector3 position;
	TVector3 attenuation;
};

#endif