#ifndef __TCOLOR_H__
#define __TCOLOR_H__

#ifndef __TMATH_H__
#include "TMath.h"
#endif

struct TColor
{
	TColor()
	{
		Set(1.f, 1.f, 1.f, 1.f);
	}

	TColor(float r, float g, float b, float a)
	{
		Set(r, g, b, a);
	}

	union
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		float c[4];
	};

	void Set(float r, float g, float b, float a)
	{
		c[0] = r;
		c[1] = g;
		c[2] = b;
		c[3] = a;
	}

	static const TColor& White()
	{
		static TColor result = TColor(1.f, 1.f, 1.f, 1.f);
		return result;
	}

};

static bool TColorEqual(const TColor& a, const TColor& b)
{
	return FLT_EQ(a.a, b.a) && FLT_EQ(a.b, b.b) && FLT_EQ(a.g, b.g) && FLT_EQ(a.r, b.r);
}

#endif
