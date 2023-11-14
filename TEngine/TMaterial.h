#ifndef __TMATERIAL_H__
#define __TMATERIAL_H__

#ifndef __TCOLOR_H__
#include "TColor.h"
#endif

struct TMaterial
{
	TColor diffuseColor;
	TColor ambientColor;
	TColor specularColor;
	TColor emissiveColor;

	float power;
};

static bool TMaterialEqual(const TMaterial& a, const TMaterial& b)
{
	return	TColorEqual(a.diffuseColor, b.diffuseColor) && 
			TColorEqual(a.ambientColor, b.ambientColor) &&
			TColorEqual(a.specularColor, b.specularColor) &&
			TColorEqual(a.emissiveColor, b.emissiveColor) &&
			FLT_EQ(a.power, b.power);
}

#endif
