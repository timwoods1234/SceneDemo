#ifndef __TD3DVERTEXFORMAT_H__
#define __TD3DVERTEXFORMAT_H__

#ifndef __TDIRECT3D_H__
#include "TDirect3D.h"
#endif

#ifndef __TVERTEXFORMAT_H__
#include "TVertexFormat.h"
#endif

class TD3DVertexFormat : public TVertexFormat
{
public:
	TD3DVertexFormat(const char* filename, LPDIRECT3DDEVICE9 device);
	~TD3DVertexFormat();

	IDirect3DVertexDeclaration9* GetD3DDeclaration() const;

	unsigned long GetFVF() const;

	void Setup();

private:
	unsigned char GetD3DUsage(TVertexFormatUsage usage);
	unsigned char GetD3DSize(TVertexFormatSize size);
	int GetFVF(TVertexFormatUsage usage);

	void ComputeFVF();
	void ComputeDeclaration();

	IDirect3DVertexDeclaration9* m_d3dDeclaration;

	unsigned long m_fvf;

	LPDIRECT3DDEVICE9 m_device;
};

#endif
