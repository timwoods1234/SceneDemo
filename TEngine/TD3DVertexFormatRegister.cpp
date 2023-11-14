#include "TD3DVertexFormatRegister.h"
#include "TD3DVertexFormat.h"

//-------------------------------------------------------------------------------
TD3DVertexFormatRegister::TD3DVertexFormatRegister(LPDIRECT3DDEVICE9 device)
:	TVertexFormatRegister(),
	m_device(device)
{
}

//-------------------------------------------------------------------------------
TD3DVertexFormatRegister::~TD3DVertexFormatRegister()
{
}

//-------------------------------------------------------------------------------
TVertexFormat* TD3DVertexFormatRegister::CreateVertexFormat(const char* filepath)
{
	TD3DVertexFormat* result = TNew TD3DVertexFormat(filepath, m_device);
	
	result->Setup();

	return result;
}