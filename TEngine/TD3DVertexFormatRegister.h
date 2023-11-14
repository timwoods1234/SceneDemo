#ifndef __TD3DVERTEXFORMATREGISTER_H__
#define __TD3DVERTEXFORMATREGISTER_H__

#ifndef __TDIRECT3D_H__
#include "TDirect3D.h"
#endif

#ifndef __TVERTEXFORMATREGISTER_H__
#include "TVertexFormatRegister.h"
#endif

class TD3DVertexFormatRegister : public TVertexFormatRegister
{
public:
	TD3DVertexFormatRegister(LPDIRECT3DDEVICE9 device);
	
	~TD3DVertexFormatRegister();

protected:
	TVertexFormat* CreateVertexFormat(const char* filepath);

private:
	LPDIRECT3DDEVICE9 m_device;
};

#endif
