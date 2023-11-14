#ifndef __TATLAS_H__
#define __TATLAS_H__

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

#ifndef __TSTRING_H__
#include "TString.h"
#endif

class TAtlasEntry;

class TAtlas : public TXMLObject
{
public:
	TAtlas();
	~TAtlas();

	void SetName(const char* name);
	const TString& GetName() const;

	void AddEntry(TAtlasEntry* entry);
	const TAtlasEntry* GetAtlasEntry(const TString& filename) const;

	unsigned int GetNumEntries() const;
	const TAtlasEntry* GetAtlasEntry(unsigned int index) const;

	TXMLObject* HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects);
	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void FinaliseLoad();
	void Write(TXMLWriter& writer);

private:
	TString m_name;

	TDynamicSet<TAtlasEntry*> m_entries;
};

#endif
