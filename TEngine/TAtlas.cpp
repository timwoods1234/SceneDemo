#include "TXMLWriter.h"
#include "TAtlasEntry.h"
#include "TAtlas.h"

//-------------------------------------------------------------------------------
static const TString s_atlasEntryID = "AtlasEntry";
static const TString s_nameID = "name";

//-------------------------------------------------------------------------------
TAtlas::TAtlas()
{
}

//-------------------------------------------------------------------------------
TAtlas::~TAtlas()
{
	for (unsigned int index = 0; index < m_entries.GetSize(); index++)
	{
		TSafeDelete(m_entries[index]);
	}
}

//-------------------------------------------------------------------------------
void TAtlas::SetName(const char* name)
{
	m_name = name;
}

//-------------------------------------------------------------------------------
const TString& TAtlas::GetName() const
{
	return m_name;
}

//-------------------------------------------------------------------------------
void TAtlas::AddEntry(TAtlasEntry* entry)
{
	m_entries.Add(entry);
}

//-------------------------------------------------------------------------------
const TAtlasEntry* TAtlas::GetAtlasEntry(const TString& filename) const
{
	for (unsigned int index = 0; index < m_entries.GetSize(); index++)
	{
		if (filename == m_entries[index]->GetFilename())
		{
			return m_entries[index];
		}
	}

	return NULL;
}

//-------------------------------------------------------------------------------
unsigned int TAtlas::GetNumEntries() const
{
	return m_entries.GetSize();
}

//-------------------------------------------------------------------------------
const TAtlasEntry* TAtlas::GetAtlasEntry(unsigned int index) const
{
	if (index >= 0 && index < m_entries.GetSize())
	{
		return m_entries[index];
	}

	return NULL;;
}

//-------------------------------------------------------------------------------
TXMLObject* TAtlas::HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects)
{
	if (s_atlasEntryID == id)
	{
		TAtlasEntry* newEntry = TNew TAtlasEntry();

		m_entries.Add(newEntry);

		return newEntry;
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void TAtlas::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_name = TDataVariant::Find(s_nameID, objects).GetString();
}

//-------------------------------------------------------------------------------
void TAtlas::FinaliseLoad()
{
}

//-------------------------------------------------------------------------------
void TAtlas::Write(TXMLWriter& writer)
{
	writer.WriteAttribute(s_nameID, m_name.GetPointer());

	for (unsigned int index = 0; index < m_entries.GetSize(); index++)
	{
		writer.WriteElement(s_atlasEntryID, *m_entries[index]);
	}
}
