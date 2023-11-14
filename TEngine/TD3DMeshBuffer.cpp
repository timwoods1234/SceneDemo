#include "TD3DMeshBuffer.h"
#include "TD3DVertexFormat.h"

//-------------------------------------------------------------------------------
TD3DMeshBuffer::TD3DMeshBuffer(LPDIRECT3DDEVICE9 device, TD3DVertexFormat* vertexFormat)
:	m_vertexBuffer(NULL),
	m_indexBuffer(NULL),
	m_device(device)
{
	m_stride = vertexFormat->GetStride();
	m_fvf = vertexFormat->GetFVF();
}

//-------------------------------------------------------------------------------
TD3DMeshBuffer::~TD3DMeshBuffer()
{
	ReleaseIndexBuffer();
	ReleaseVertexBuffer();
}

//-------------------------------------------------------------------------------
void TD3DMeshBuffer::SetVertices(const void* vertices, unsigned int numVertices)
{
    if (numVertices > m_numVertices)
    {
        ReleaseVertexBuffer();
    }

	if (m_vertexBuffer == NULL)
	{
		if (m_dynamic)
		{
			m_device->CreateVertexBuffer(numVertices * m_stride, D3DUSAGE_DYNAMIC, m_fvf, D3DPOOL_DEFAULT, &m_vertexBuffer, NULL);
		}
		else
		{
			m_device->CreateVertexBuffer(numVertices * m_stride, 0, m_fvf, D3DPOOL_DEFAULT, &m_vertexBuffer, NULL);
		}
	}

    unsigned long lockFlags = D3DLOCK_DISCARD;
	void* tempVerts = NULL;

	if (FAILED(m_vertexBuffer->Lock(0, numVertices * m_stride, &tempVerts, lockFlags)))
	{
		TASSERT(false, "[TD3DMeshEntry::SetVertices] failed to lock vertex buffer");
	}
	
	memcpy(tempVerts, vertices, numVertices * m_stride);
	
	if (FAILED(m_vertexBuffer->Unlock()))
	{
		TASSERT(false, "[TD3DMeshEntry::SetVertices] failed to unlock vertex buffer");
	}

	m_numVertices = numVertices;
}

//-------------------------------------------------------------------------------
void TD3DMeshBuffer::SetIndices(const unsigned short* indices, unsigned int numIndices)
{
    if (numIndices > m_numIndices)
    {
        ReleaseIndexBuffer();
    }

	if (m_indexBuffer == NULL)
	{
		if (m_dynamic)
		{
			m_device->CreateIndexBuffer(numIndices * sizeof(unsigned short), D3DUSAGE_DYNAMIC, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, NULL);
		}
		else
		{
			m_device->CreateIndexBuffer(numIndices * sizeof(unsigned short), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, NULL);
		}
	}

    unsigned long lockFlags = D3DLOCK_DISCARD;
	unsigned short* tempInds = NULL;
	
	if (FAILED(m_indexBuffer->Lock(0, numIndices * sizeof(unsigned short), (void**)&tempInds, lockFlags)))
	{
		TASSERT(false, "[TD3DMeshEntry::SetVertices] failed to lock index buffer");
	}

	memcpy(tempInds, indices, numIndices * sizeof(unsigned short));

	if (FAILED(m_indexBuffer->Unlock()))
	{
		TASSERT(false, "[TD3DMeshEntry::SetVertices] failed to unlock index buffer");
	}

	m_numIndices = numIndices;
}

//-------------------------------------------------------------------------------
void TD3DMeshBuffer::MarkDynamic()
{
	if (!m_dynamic)
	{
		ReleaseIndexBuffer();
		ReleaseVertexBuffer();

		m_dynamic = true;
	}
}

//-------------------------------------------------------------------------------
const LPDIRECT3DVERTEXBUFFER9 TD3DMeshBuffer::GetVertexBuffer() const
{
	return m_vertexBuffer;
}

//-------------------------------------------------------------------------------
const LPDIRECT3DINDEXBUFFER9 TD3DMeshBuffer::GetIndexBuffer() const
{
	return m_indexBuffer;
}

//-------------------------------------------------------------------------------
unsigned int TD3DMeshBuffer::GetStride() const
{
	return m_stride;
}

//-------------------------------------------------------------------------------
void TD3DMeshBuffer::ReleaseIndexBuffer()
{
    SafeRelease(m_indexBuffer);
    m_numIndices = 0;
}

//-------------------------------------------------------------------------------
void TD3DMeshBuffer::ReleaseVertexBuffer()
{
    SafeRelease(m_vertexBuffer);
    m_numVertices = 0;
}
