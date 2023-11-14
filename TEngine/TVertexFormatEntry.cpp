#include "TVertexFormatEntry.h"
#include "TError.h"

//-------------------------------------------------------------------------------
TVertexFormatSize TVertexFormatEntry::GetVertexElementSize(const TString& data)
{
	if (data == "float1")
	{
		return Float1;
	}
	if (data == "float2")
	{
		return Float2;
	}
	else if (data == "float3")
	{
		return Float3;
	}
	else if (data == "float4")
	{
		return Float4;
	}
	else
	{
		TASSERT(false, "Unable to parse vertex size");
		return Invalid;
	}
}

//-------------------------------------------------------------------------------
TVertexFormatUsage TVertexFormatEntry::GetVertexElementUsage(const TString& data)
{
	if (data == "position")
	{
		return Usage_Position;
	}
	else if (data == "normal")
	{
		return Usage_Normal;
	}
	else if (data == "texcoord")
	{
		return Usage_Texcoord;
	}
	else if (data == "color")
	{
		return Usage_Color;
	}
	else
	{
		TASSERT(false, "Unable to parse vertex usage");
		return Usage_Invalid;
	}
}