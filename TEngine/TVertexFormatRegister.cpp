#include "TVertexFormatRegister.h"
#include "TVertexFormat.h"
#include "TError.h"
#include "TLocator.h"
#include "TFileSystemInterface.h"

//-------------------------------------------------------------------------------
TVertexFormatRegister::TVertexFormatRegister()
{
}

//-------------------------------------------------------------------------------
TVertexFormatRegister::~TVertexFormatRegister()
{
	for (unsigned int index = 0; index < m_vertexFormats.GetSize(); index++)
	{
		TSafeDelete(m_vertexFormats[index]);
	}
}

//-------------------------------------------------------------------------------
TVertexFormat* TVertexFormatRegister::GetVertexFormat(const TString& formatName)
{
	for (unsigned int index = 0; index < m_vertexFormats.GetSize(); index++)
	{
		if (formatName == m_vertexFormats[index]->GetId())
		{
			return m_vertexFormats[index];
		}
	}

	TDebugPrint(("Unable to find vertex format: %s", formatName.GetPointer()));

	return NULL;
}

//-------------------------------------------------------------------------------
void TVertexFormatRegister::LoadAllFormats()
{
	TDynamicSet<TString> filenames;

	TLocator::GetFileSystem()->GetFileList("Assets/Shader/VertexFormats", "xml", filenames);

	for (unsigned int index = 0; index < filenames.GetSize(); index++)
	{
		TVertexFormat* format = CreateVertexFormat(filenames[index].GetPointer());

		if (format != NULL)
		{
			m_vertexFormats.Add(format);
		}
	}
}