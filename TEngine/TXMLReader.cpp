#include "TXMLReader.h"
#include "TXMLAttribute.h"
#include "TMemory.h"
#include "TError.h"
#include "TDataVariant.h"
#include "TXMLFile.h"

//-------------------------------------------------------------------------------
TXMLReader::TXMLReader(const char* filename, TXMLObject& rootObject)
:	m_error(false),
	m_currentObject(NULL),
	m_rootObject(NULL)
{
	TXMLFile file(filename);

	if (!file.WasError())
	{
		m_rootObject = &rootObject;
		m_currentObject = NULL;

		if (!file.HasMoreAttributes())
		{
			TDebugPrint(("[TXMLReader::TXMLReader] File is empty %s", filename));
		}
		else
		{
			ParseFile(file);
		}
	}
	else
	{
		TDebugPrint(("[TXMLReader::TXMLReader] Failed to open file %s", filename));
		m_error = true;
	}
}

//-------------------------------------------------------------------------------
bool TXMLReader::WasError() const
{
	return m_error;
}

//-------------------------------------------------------------------------------
void TXMLReader::ParseFile(TXMLFile& file)
{
	TDynamicSet<TDataVariant> dataVariants;

	TXMLAttribute currentAttribute = file.GetNextAttribute();

	while (file.HasMoreAttributes() && !file.WasError())
	{
		if (currentAttribute.type == TXMLAttribute::ElementStart)
		{
			TString currentElementId(currentAttribute.id.GetPointer());

			currentAttribute = file.GetNextAttribute();

			while (currentAttribute.type == TXMLAttribute::Attribute)
			{
				TDataVariant currentData(currentAttribute.id.GetPointer(), currentAttribute.value.GetPointer());

				dataVariants.Add(currentData);

				currentAttribute = file.GetNextAttribute();
			}

			if (m_currentObject == NULL && m_loadStack.GetSize() == 0)
			{
				m_currentObject = m_rootObject;
			}
			else
			{
				m_loadStack.Add(m_currentObject);

				if (m_currentObject != NULL)
				{
					m_currentObject = m_currentObject->HandleLoadElement(currentElementId, dataVariants);
				}
			}

			if (m_currentObject != NULL)
			{
				m_currentObject->HandleLoadAttributes(dataVariants);
			}

			dataVariants.Clear();
		}
		else if (currentAttribute.type == TXMLAttribute::ElementEnd)
		{
			ReadEndElement();

			currentAttribute = file.GetNextAttribute();
		}
		else if (currentAttribute.type == TXMLAttribute::Invalid)
		{
			if (file.HasMoreAttributes())
			{
				m_error = true;
			}
		}
		else
		{
			// didn't reconise the type
			m_error = true;
		}
	}

	if (!m_error && currentAttribute.type == TXMLAttribute::ElementEnd)
	{
		ReadEndElement();
	}
}

//-------------------------------------------------------------------------------
void TXMLReader::ReadEndElement()
{
	if (m_currentObject != NULL)
	{
		m_currentObject->FinaliseLoad();
	}

	m_currentObject = NULL;

	if (m_loadStack.GetSize() > 0)
	{
		int nLast = m_loadStack.GetSize() - 1;

		m_currentObject = m_loadStack[nLast];
		m_loadStack.RemoveAt(nLast);
	}
}
