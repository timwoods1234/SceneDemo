#ifndef __TSPRITEANIMATION_H__
#define __TSPRITEANIMATION_H__

#ifndef __TSTRING_H__
#include "TString.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TVECTOR4_H__
#include "TVector4.h"
#endif

class TTexture;

struct TSpriteAnimation
{
public:
	TString			name;
	bool			loop;
	TString			nextAnim;
	float			frameRate;
	unsigned int	numFrames;

	TDynamicSet<TTexture*> frames;
	TDynamicSet<TVector4> textureCoords;
};

#endif
