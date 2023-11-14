
#ifndef __TDEBUGRENDERENTRIES_H__
#define __TDEBUGRENDERENTRIES_H__

#ifndef __TCOLOR_H__
#include "TColor.h"
#endif

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

#ifndef __TSTRING_H__
#include "TString.h"
#endif

enum TDebugRenderEntryType
{
	Cube,
	Sphere,
	Line,
};

struct TDebugRenderEntry
{
	TDebugRenderEntryType type;

	TColor color;

	TVector3 start;
	
	TVector3 end;

	float radius;

	float expiryTime;
};

struct TDebugTextEntry
{
	TString text;

	TColor color;

	float expiryTime;
};

#endif
