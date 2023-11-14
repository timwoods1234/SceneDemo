#include "TXMLWriter.h"
#include "TAtlasEntry.h"

//-------------------------------------------------------------------------------
static const TString s_filenameID = "filename";
static const TString s_texturePageID = "texturePage";

static const TString s_widthID = "width";
static const TString s_heightID = "height";

static const TString s_texXID = "texCoordX";
static const TString s_texYID = "texCoordY";
static const TString s_texZID = "texCoordZ";
static const TString s_texWID = "texCoordW";

//-------------------------------------------------------------------------------
TAtlasEntry::TAtlasEntry()
:	m_size(0, 0),
	m_texCoords(0, 0, 0, 0)
{
}

//-------------------------------------------------------------------------------
TAtlasEntry::~TAtlasEntry()
{
}

//-------------------------------------------------------------------------------
TXMLObject* TAtlasEntry::HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects)
{
	return NULL;
}

//-------------------------------------------------------------------------------
void TAtlasEntry::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_filename = TDataVariant::Find(s_filenameID, objects).GetString();
	m_texturePage = TDataVariant::Find(s_texturePageID, objects).GetString();
	
	m_size.x = TDataVariant::Find(s_widthID, objects).GetFloat();
	m_size.y = TDataVariant::Find(s_heightID, objects).GetFloat();
	
	m_texCoords.x = TDataVariant::Find(s_texXID, objects).GetFloat();
	m_texCoords.y = TDataVariant::Find(s_texYID, objects).GetFloat();
	m_texCoords.z = TDataVariant::Find(s_texZID, objects).GetFloat();
	m_texCoords.w = TDataVariant::Find(s_texWID, objects).GetFloat();
}

//-------------------------------------------------------------------------------
void TAtlasEntry::FinaliseLoad()
{
}

//-------------------------------------------------------------------------------
void TAtlasEntry::Write(TXMLWriter& writer)
{
	writer.WriteAttribute(s_filenameID, m_filename.GetPointer());
	writer.WriteAttribute(s_texturePageID, m_texturePage.GetPointer());

	writer.WriteAttribute(s_widthID, m_size.x);
	writer.WriteAttribute(s_heightID, m_size.y);

	writer.WriteAttribute(s_texXID, m_texCoords.x);
	writer.WriteAttribute(s_texYID, m_texCoords.y);
	writer.WriteAttribute(s_texZID, m_texCoords.z);
	writer.WriteAttribute(s_texWID, m_texCoords.w);
}

//-------------------------------------------------------------------------------
void TAtlasEntry::SetFilename(const char* filename)
{
	m_filename = filename;
}

//-------------------------------------------------------------------------------
void TAtlasEntry::SetTexturePage(const char* filename)
{
	m_texturePage = filename;
}

//-------------------------------------------------------------------------------
void TAtlasEntry::SetSize(int x, int y)
{
	m_size.Set((float)x, (float)y);
}

//-------------------------------------------------------------------------------
const TString& TAtlasEntry::GetTexturePage() const
{
	return m_texturePage;
}

//-------------------------------------------------------------------------------
void TAtlasEntry::SetTextureCoords(float x, float y, float z, float w)
{
	m_texCoords.Set(x, y, z, w);
}

//-------------------------------------------------------------------------------
const TString& TAtlasEntry::GetFilename() const
{
	return m_filename;
}

//-------------------------------------------------------------------------------
const TVector2& TAtlasEntry::GetSize() const
{
	return m_size;
}

//-------------------------------------------------------------------------------
const TVector4& TAtlasEntry::GetTextureCoords() const
{
	return m_texCoords;
}
