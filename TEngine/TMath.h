#ifndef __TMATH_H__
#define __TMATH_H__

// helper functions (min, max, etc)

// TODO: tidy up/reorganize these

#include "float.h"
#include <math.h>

//+-----------------------------------------------------------------------
enum TCullingFlag
{
	CULLING_OUTSIDE,
	CULLING_INTERSECT,
	CULLING_INSIDE
};

//+-----------------------------------------------------------------------
//| Constants 
//+-----------------------------------------------------------------------
const float EPSILON		= 0.001f;
const float PI			= 3.1415926535897932384626433832795f;
const float TWO_PI		= (PI*2.0f);
const float HALF_PI		= (PI*0.5f);
const float QUARTER_PI	= (PI*0.25f);
const float ONEOVERPI	= (1.0f / PI);
const float ONEOVER2PI	= (1.0f / TWO_PI);
const float PIOVER180	= (PI / 180.0f);
const float K180OVERPI	= (180.0f / PI);

#define FLT_EQ(a,b)	(fabsf(a - b) < EPSILON)

//+-----------------------------------------------------------------------
//| General
//+-----------------------------------------------------------------------
int				FastRandom(unsigned int *seed, int min, int max);
float			FastRandom(unsigned int *seed, float min, float max);
unsigned int	FastRandom(unsigned int *seed, unsigned int min, unsigned int max);
float			DegToRad(float x);
float			RadToDeg(float x);
bool			IsPowerOfTwo(int num);
float			WrapPi(float f);
float			ZoomToFov(float fZoom);
float			FovToZoom(float fFov);
void			SinCos(float angle, float& sin, float& cos);

//------------------------------------------------------------------------
//| Templated 
//+-----------------------------------------------------------------------
template <class T> 
T TClamp(const T& value, const T& min, const T& max);

template <class T> 
T TSquare(const T& value);

template <class T>
T TMin(const T& v1, const T& v2);

template <class T>
T TMax(const T& v1, const T& v2);

template <class T>
T TLerp(const T& a, const T& b, float fraction);

#include "TMath.inl"

#endif
