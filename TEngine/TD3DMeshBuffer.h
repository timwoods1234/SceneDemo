#ifndef __TD3DMESHBUFFER_H__
#define __TD3DMESHBUFFER_H__

#ifndef __TMESHBUFFERINTERFACE_H__
#include "TMeshBufferInterface.h"
#endif

#ifndef __TDIRECT3D_H__
#include "TDirect3D.h"
#endif

class TD3DVertexFormat;

class TD3DMeshBuffer : public TMeshBufferInterface
{
public:
	TD3DMeshBuffer(LPDIRECT3DDEVICE9 device, TD3DVertexFormat* vertexFormat);

	~TD3DMeshBuffer();

	void SetVertices(const void* vertices, unsigned int numVertices);

	void SetIndices(const unsigned short* indices, unsigned int numIndices);

	void MarkDynamic();

	const LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer() const;
	
	const LPDIRECT3DINDEXBUFFER9 GetIndexBuffer() const;

	// TODO: maybe move to base class
	unsigned int GetStride() const;

private:
    void ReleaseIndexBuffer();

    void ReleaseVertexBuffer();

	LPDIRECT3DDEVICE9 m_device;

	LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;

	LPDIRECT3DINDEXBUFFER9 m_indexBuffer;

	unsigned int m_stride;

	unsigned long m_fvf;
};

#endif
