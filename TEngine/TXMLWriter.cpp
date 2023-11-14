#include <memory>

#include "TXMLTagType.h"
#include "TXMLWriter.h"
#include "TXMLObject.h"
#include "TDataVariant.h"
#include "TString.h"
#include "TMemory.h"
#include "TXMLTagType.h"
#include "TXMLFile.h"

//-------------------------------------------------------------------------------
TXMLWriter::TXMLWriter(const char* filename, const TString& strRootTagId, TXMLObject& rootObject)
{
	memset(m_formatBuffer, 0, c_formatBufferSize);

	TXMLFile output;
	m_file = &output;

	WriteElement(strRootTagId, rootObject);

	output.Save(filename);
}

//-------------------------------------------------------------------------------
void TXMLWriter::WriteElement(const TString& strTagId, TXMLObject& saveObject)
{
	WriteDummyElementStart(strTagId);

	saveObject.Write(*this);

	WriteDummyElementEnd(strTagId);
}

//-------------------------------------------------------------------------------

void TXMLWriter::WriteDummyElementStart(const TString& strTagId)
{
	TXMLAttribute start;

	start.id = strTagId;
	start.type = TXMLAttribute::ElementStart;

	m_file->AddXMLAttribute(start);
}

//-------------------------------------------------------------------------------
void TXMLWriter::WriteDummyElementEnd(const TString& strTagId)
{
	TXMLAttribute end;

	end.id = strTagId;
	end.type = TXMLAttribute::ElementEnd;

	m_file->AddXMLAttribute(end);
}

//-------------------------------------------------------------------------------
void TXMLWriter::WriteAttribute(const TString& strTagId, const char* value)
{
	TXMLAttribute attr;

	attr.id = strTagId;
	attr.type = TXMLAttribute::Attribute;
	attr.value = value;

	m_file->AddXMLAttribute(attr);
}

//-------------------------------------------------------------------------------
void TXMLWriter::WriteAttribute(const TString& strTagId, int value)
{
	sprintf_s(m_formatBuffer, c_formatBufferSize, "%d", value);

	WriteAttribute(strTagId, m_formatBuffer);
}

//-------------------------------------------------------------------------------
void TXMLWriter::WriteAttribute(const TString& strTagId, float value)
{
	sprintf_s(m_formatBuffer, c_formatBufferSize, "%.3f", value);

	WriteAttribute(strTagId, m_formatBuffer);
}

//-------------------------------------------------------------------------------
void TXMLWriter::WriteAttribute(const TString& strTagId, bool value)
{
	if (value)
	{
		WriteAttribute(strTagId, "true");
	}
	else
	{
		WriteAttribute(strTagId, "false");
	}
}
