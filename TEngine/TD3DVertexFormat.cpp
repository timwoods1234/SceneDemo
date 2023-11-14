#include "TD3DVertexFormat.h"

//-------------------------------------------------------------------------------
TD3DVertexFormat::TD3DVertexFormat(const char* filename, LPDIRECT3DDEVICE9 device)
:	TVertexFormat(filename),
	m_d3dDeclaration(NULL),
	m_fvf(0),
	m_device(device)
{
}

//-------------------------------------------------------------------------------
TD3DVertexFormat::~TD3DVertexFormat()
{
}


//-------------------------------------------------------------------------------
IDirect3DVertexDeclaration9* TD3DVertexFormat::GetD3DDeclaration() const
{
	return m_d3dDeclaration;
}

//-------------------------------------------------------------------------------
unsigned long TD3DVertexFormat::GetFVF() const
{
	return m_fvf;
}

//-------------------------------------------------------------------------------
void TD3DVertexFormat::Setup()
{
	ComputeFVF();

	ComputeDeclaration();
}

//-------------------------------------------------------------------------------
unsigned char TD3DVertexFormat::GetD3DUsage(TVertexFormatUsage usage)
{
	switch (usage)
	{
		case Usage_Position:
			{
				return D3DDECLUSAGE_POSITION;
			}
			break;
			
		case Usage_Normal:
			{
				return D3DDECLUSAGE_NORMAL;
			}
			break;
			
		case Usage_Texcoord:
			{
				return D3DDECLUSAGE_TEXCOORD;
			}
			break;
			
		case Usage_Color:
			{
				return D3DDECLUSAGE_COLOR;
			}
			break;

		default:
			{
				TDebugPrint(("Failed to get d3d usage from TFormat"));
			}
			break;
	}

	return 0;
}

//-------------------------------------------------------------------------------
unsigned char TD3DVertexFormat::GetD3DSize(TVertexFormatSize size)
{
	unsigned char result = 0;

	switch (size)
	{
		case Float1:
			{
				return D3DDECLTYPE_FLOAT1;
			}
			break;
			
		case Float2:
			{
				return D3DDECLTYPE_FLOAT2;
			}
			break;
			
		case Float3:
			{
				return D3DDECLTYPE_FLOAT3;
			}
			break;
			
		case Float4:
			{
				return D3DDECLTYPE_FLOAT4;
			}
			break;

		default:
			{
				TDebugPrint(("Failed to get d3d size from TFormat"));
			}
			break;
	}

	return result;
}

//-------------------------------------------------------------------------------
int TD3DVertexFormat::GetFVF(TVertexFormatUsage usage)
{
	int result = 0;

	switch (usage)
	{
		case Usage_Position:
			{
				result = D3DFVF_XYZ;
			}
			break;
			
		case Usage_Normal:
			{
				result = D3DFVF_NORMAL;
			}
			break;
			
		case Usage_Texcoord:
			{
				result = D3DFVF_TEX1;
			}
			break;
			
		case Usage_Color:
			{
				result = D3DFVF_DIFFUSE;
			}
			break;
			
		default:
			{
				TDebugPrint(("Unable to convert TFormat to fvf"));
			}
			break;
	}

	return result;
}

//-------------------------------------------------------------------------------
void TD3DVertexFormat::ComputeFVF()
{
	m_fvf = 0;

	for (unsigned int index = 0; index < m_formatEntries.GetSize(); index++)
	{
		unsigned long fvf = GetFVF(m_formatEntries[index].usage);

		m_fvf |= fvf;
	}
}

//-------------------------------------------------------------------------------
void TD3DVertexFormat::ComputeDeclaration()
{
	D3DVERTEXELEMENT9* declVertex = TNewArray D3DVERTEXELEMENT9[m_formatEntries.GetSize() + 1];

	unsigned int prevSize = 0;
	unsigned int index = 0;

	for (; index < m_formatEntries.GetSize(); index++)
	{
		unsigned char size = GetD3DSize(m_formatEntries[index].size);
		unsigned char usage = GetD3DUsage(m_formatEntries[index].usage);

		declVertex[index].Stream = 0;
		declVertex[index].Offset = prevSize;
		declVertex[index].Type = size;
		declVertex[index].Method = D3DDECLMETHOD_DEFAULT;
		declVertex[index].Usage = usage;
		declVertex[index].UsageIndex = m_formatEntries[index].usageIndex;

		prevSize += (int)m_formatEntries[index].size;
	}

	//{0xFF,0,D3DDECLTYPE_UNUSED,0,0,0}
	declVertex[index].Stream = 0xFF;
	declVertex[index].Offset = 0;
	declVertex[index].Type = D3DDECLTYPE_UNUSED;
	declVertex[index].Method = 0;
	declVertex[index].Usage = 0;
	declVertex[index].UsageIndex = 0;


	HRESULT hr = m_device->CreateVertexDeclaration(declVertex, &m_d3dDeclaration);

	if (FAILED(hr))
	{
		TASSERT(false, "[TD3DVertexFormat::ComputeDeclaration] Failed to create declaration");
	}

	TDeleteArray(declVertex);
}