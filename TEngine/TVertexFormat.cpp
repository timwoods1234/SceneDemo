#include "TVertexFormat.h"
#include "TXMLReader.h"

//-------------------------------------------------------------------------------
static const TString c_formatEntryId = "VertexElement";
static const TString c_formatSizeId = "size";
static const TString c_formatUsageId = "usage";
static const TString c_formatUsageIndexId = "usageIndex";
static const TString c_formatId = "id";

//-------------------------------------------------------------------------------
TVertexFormat::TVertexFormat(const char* filename)
{
	TXMLReader reader(filename, *this);
}

//-------------------------------------------------------------------------------
TVertexFormat::~TVertexFormat()
{
}

//-------------------------------------------------------------------------------
const TString& TVertexFormat::GetId() const
{
	return m_id;
}

//-------------------------------------------------------------------------------
unsigned int TVertexFormat::GetStride() const
{
	return m_stride;
}

//-------------------------------------------------------------------------------
TXMLObject* TVertexFormat::HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects)
{
	if (c_formatEntryId == strID)
	{
		TString sizeData = TDataVariant::Find(c_formatSizeId, objects).GetString();
		TString usageData = TDataVariant::Find(c_formatUsageId, objects).GetString();
		int usageIndex = TDataVariant::Find(c_formatUsageIndexId, objects).GetInt();

		TVertexFormatSize size = TVertexFormatEntry::GetVertexElementSize(sizeData);
		TVertexFormatUsage usage = TVertexFormatEntry::GetVertexElementUsage(usageData);

		TVertexFormatEntry entry;
		entry.size = size;
		entry.usage = usage;
		entry.usageIndex = usageIndex;

		m_formatEntries.Add(entry);
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void TVertexFormat::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_id = TDataVariant::Find(c_formatId, objects).GetString();
}

//-------------------------------------------------------------------------------
void TVertexFormat::FinaliseLoad()
{
	ComputeStride();
}

//-------------------------------------------------------------------------------
void TVertexFormat::Write(TXMLWriter& writer)
{
}

//-------------------------------------------------------------------------------
void TVertexFormat::ComputeStride()
{
	m_stride = 0;

	for (unsigned int index = 0; index < m_formatEntries.GetSize(); index++)
	{
		m_stride += (int)m_formatEntries[index].size;
	}
}