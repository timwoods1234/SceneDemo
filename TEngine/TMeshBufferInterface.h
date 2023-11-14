#ifndef __TMESHBUFFERINTERFACE_H__
#define __TMESHBUFFERINTERFACE_H__

class TMeshBufferInterface
{
public:
	TMeshBufferInterface();

	virtual ~TMeshBufferInterface();

	virtual void SetVertices(const void* vertices, unsigned int numVertices) = 0;

	virtual void SetIndices(const unsigned short* indices, unsigned int numIndices) = 0;

	virtual void MarkDynamic();

	unsigned int GetNumVertices() const;
	
	unsigned int GetNumIndices() const;

protected:
	bool m_dynamic;

	unsigned int m_numVertices;

	unsigned int m_numIndices;
};

#endif
