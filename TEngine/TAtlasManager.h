#ifndef __TATLASMANAGER_H__
#define __TATLASMANAGER_H__

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class TAtlasEntry;
class TString;
class TAtlas;

class TAtlasManager : public TSingleton<TAtlasManager>
{
public:
	TAtlasManager();

	~TAtlasManager();

	const TAtlasEntry* GetEntry(const TString& filename) const;

private:
	TDynamicSet<TAtlas*> m_atlases;
};



#endif
