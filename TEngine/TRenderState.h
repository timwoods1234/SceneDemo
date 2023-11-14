#ifndef __TRENDERSTATE_H__
#define __TRENDERSTATE_H__

enum TDepthState
{
	RS_DEPTH_UNSET,
	RS_DEPTH_READWRITE,	// read and write depth buffer
	RS_DEPTH_READONLY,	// no writes to depth buffer
	RS_DEPTH_NONE,		// no reads or writes to depth buffer
};

enum TShadeState
{
	RS_SHADE_UNSET,
	RS_SHADE_POINTS,	// render vertices as points
	RS_SHADE_TRIWIRE,	// render wireframe triangles
	RS_SHADE_HULLWIRE,	// render wireframe polygons
	RS_SHADE_SOLID,		// solid triangles
};

enum TZCompareState
{
	RS_ZFUNC_UNSET,
	RS_ZFUNC_LESSEQUAL,
	RS_ZFUNC_ALWAYS,
	RS_ZFUNC_GREATER,
};

enum TCullMode
{
	RS_CULL_UNSET,
	RS_CULL_NONE,
	RS_CULL_CW,
	RS_CULL_CCW,
};

#endif
