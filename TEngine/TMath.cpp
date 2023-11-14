#include "TMath.h"

//-------------------------------------------------------------------------------
unsigned long FtoDw(float f)
{
	return *((unsigned long*)&f);
}

//-------------------------------------------------------------------------------
int	FastRandom(unsigned int *seed, int min, int max)
{
	int diff = max - min;
	if (diff <= 0) 
	{
		return min;
	}

	int rnd = ((*seed = *seed*214013L + 2531011L) >> 8) & 0xffffff;
	return min + (rnd % diff);
}

//-------------------------------------------------------------------------------
float FastRandom(unsigned int *seed, float min, float max)
{
	int rnd;
	float rndFloat, diff;

	rnd = ((*seed = *seed*214013L + 2531011L) >> 8) & 0xffffff;
	*(reinterpret_cast<int*>(&rndFloat)) = (rnd & 0x007fffff) | 0x3f800000;
	diff = max - min;

	float val = ((rndFloat - 1.0f) * diff + min);
	return val;
}

//-------------------------------------------------------------------------------
unsigned int FastRandom(unsigned int *seed, unsigned int min, unsigned int max)
{
	unsigned int diff = max - min;
	if (diff <= 0) 
	{
		return min;
	}

	int rnd = ((*seed = *seed*214013L + 2531011L) >> 8) & 0xffffff;
	return min + (rnd % diff);
}

//-------------------------------------------------------------------------------
float DegToRad(float x)
{
	return x * PIOVER180;
}

//-------------------------------------------------------------------------------
float RadToDeg(float x)
{
	return x * K180OVERPI;
}

//-------------------------------------------------------------------------------
bool IsPowerOfTwo(int num)
{
	int i = 1;

	while (i != 0) 
	{
		if (i == num) 
		{
			return true;
		}

		i = i << 1;
	}

	return false;
}

//-------------------------------------------------------------------------------
float WrapPi(float a)
{
	// "Wrap" an angle in range -pi...pi
	// by adding the correct multiple of 2 pi
	a += PI;
	a -= floorf(a * ONEOVER2PI) * TWO_PI;
	a -= PI;

	return a;
}

//-------------------------------------------------------------------------------
float ZoomToFov(float fZoom)
{
	return 2.0f * atanf(1.0f / fZoom);
}

//-------------------------------------------------------------------------------
float FovToZoom(float fFov)
{
	return 1.0f / tanf(fFov * 0.5f);
}

//-------------------------------------------------------------------------------
void SinCos(float angle, float& sin, float& cos)
{
#ifdef _M_IX86	// if on Intel, use assembly language
	float *pSine =  &sin;
	float *pCosine = &cos;
	__asm {
		push		ecx
			fld         dword ptr angle
			fsincos
			mov 		ecx, dword ptr[pCosine]
		fstp        dword ptr [ecx]
		mov 		ecx, dword ptr[pSine]
		fstp        dword ptr [ecx]
		pop			ecx
	}
#else
	sin = sinf(angle);
	cos = cosf(angle);
#endif
}
