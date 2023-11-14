#ifndef __TSTRINGLIST_H__
#define __TSTRINGLIST_H__

#include <stdio.h>

#ifndef __TSTRING_H__
#include "TString.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class TStringList
{
public:
	TStringList();
	~TStringList();

	void AddString(const TString& str);

	void Clear();

	unsigned int GetNumStrings() const;

	const TString& GetString(unsigned int index) const;

	void Print(FILE* file = NULL) const;

private:
	TDynamicSet<TString*> m_strings;
};

#endif
