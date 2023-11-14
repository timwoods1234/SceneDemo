#include "TStringList.h"

//-------------------------------------------------------------------------------
TStringList::TStringList()
{
}

//-------------------------------------------------------------------------------
TStringList::~TStringList()
{
	Clear();
}

//-------------------------------------------------------------------------------
void TStringList::AddString(const TString& str)
{
	TString* newString = TNew TString(str);

	m_strings.Add(newString);
}

//-------------------------------------------------------------------------------
unsigned int TStringList::GetNumStrings() const
{
	return m_strings.GetSize();
}

//-------------------------------------------------------------------------------
const TString& TStringList::GetString(unsigned int index) const
{
	return *(m_strings[index]);
}

//-------------------------------------------------------------------------------
void TStringList::Clear()
{
	for (unsigned int index = 0; index < m_strings.GetSize(); index++)
	{
		TSafeDelete(m_strings[index]);
	}

	m_strings.Clear();
}

//-------------------------------------------------------------------------------
void TStringList::Print(FILE* file) const
{
	unsigned int numStrings = m_strings.GetSize();

	for (unsigned int index = 0; index < numStrings; index++)
	{
		if (file != NULL)
		{
			fprintf_s(file, "%s", m_strings[index]->GetPointer());
		}
		else
		{
			printf(m_strings[index]->GetPointer());
		}
	}
}
