#include "TAtlasManager.h"
#include "TAtlas.h"
#include "TXMLReader.h"
#include "TConfig.h"

//-------------------------------------------------------------------------------
DefineSingleton(TAtlasManager);

//-------------------------------------------------------------------------------
TAtlasManager::TAtlasManager()
{
	unsigned int numAtlases = TConfig::Get()->GetNumAtlases();

	for (unsigned int index = 0; index < numAtlases; index++)
	{
		const TString& atlasName = TConfig::Get()->GetAtlasFilename(index);
		TAtlas* newAtlas = TNew TAtlas();

		TXMLReader reader(atlasName.GetPointer(), *newAtlas);

        if (reader.WasError())
        {
            TASSERT(false, "TAtlasManager failed to load atlas");
        }
        else
        {
            m_atlases.Add(newAtlas);
        }
	}
}

//-------------------------------------------------------------------------------
TAtlasManager::~TAtlasManager()
{
	for (unsigned int index = 0; index < m_atlases.GetSize(); index++)
	{
		TSafeDelete(m_atlases[index]);
	}
}

//-------------------------------------------------------------------------------
const TAtlasEntry* TAtlasManager::GetEntry(const TString& filename) const
{
	const TAtlasEntry* result = NULL;
	unsigned int numAtlases = m_atlases.GetSize();

	for (unsigned int index = 0; index < numAtlases; index++)
	{
		result = m_atlases[index]->GetAtlasEntry(filename);

		if (result != NULL)
		{
			break;
		}
	}

	if (result == NULL)
	{
		TDebugPrint(("[TAtlasManager::GetEntry] Entry not found: %s", filename.GetPointer()));
	}

	return result;
}
