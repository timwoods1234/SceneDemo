#include "TMeshBufferInterface.h"

//-------------------------------------------------------------------------------
TMeshBufferInterface::TMeshBufferInterface()
:	m_dynamic(false),
	m_numVertices(0),
	m_numIndices(0)
{
}

//-------------------------------------------------------------------------------
TMeshBufferInterface::~TMeshBufferInterface()
{
}

//-------------------------------------------------------------------------------
void TMeshBufferInterface::MarkDynamic()
{
}

//-------------------------------------------------------------------------------
unsigned int TMeshBufferInterface::GetNumVertices() const
{
	return m_numVertices;
}

//-------------------------------------------------------------------------------
unsigned int TMeshBufferInterface::GetNumIndices() const
{
	return m_numIndices;
}