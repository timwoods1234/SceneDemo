#ifndef __TVERTEXFORMATTYPES_H__
#define __TVERTEXFORMATTYPES_H__

enum TVertexFormatUsage
{
	Usage_Invalid,
	Usage_Position,
	Usage_Normal,
	Usage_Texcoord,
	Usage_Color,
};

enum TVertexFormatSize
{
	// use the enum as the size too
	Invalid = 0,
	Float1 = 4,
	Float2 = 8,
	Float3 = 12,
	Float4 = 16,
};

#endif
