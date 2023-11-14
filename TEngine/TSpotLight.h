#ifndef __TSPOTLIGHT_H__
#define __TSPOTLIGHT_H__

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

#ifndef __TCOLOR_H__
#include "TColor.h"
#endif

struct TSpotLight
{
	TSpotLight()
	{
		diffuse.Set(1.f, 1.f, 1.f, 1.f);
		ambient.Set(1.f, 1.f, 1.f, 1.f);
		specular.Set(1.f, 1.f, 1.f, 1.f);

		attenuation.Set(0.f, 0.f, 0.f);
		direction.Set(0.f, 0.f, 0.f);
		position.Set(0.f, 0.f, 0.f);

		power = 1.f;
	}

	TColor diffuse;
	TColor ambient;
	TColor specular;

	TVector3 direction;
	TVector3 attenuation;
	TVector3 position;

	float power;
};

#endif
