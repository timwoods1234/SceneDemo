#ifndef __TSTRINGPOOLSEARCH_H__
#define __TSTRINGPOOLSEARCH_H__

struct TStringPoolEntry;

class TStringPoolSearch
{
public:
	// returns the new root
	static TStringPoolEntry* Insert(TStringPoolEntry* root, TStringPoolEntry* toInsert);

	// returns the new root
	static TStringPoolEntry* Remove(TStringPoolEntry* root, TStringPoolEntry* toRemove);

	static TStringPoolEntry* FindAllocatedEntry(TStringPoolEntry* root, const char* term, int termLength);

	static TStringPoolEntry* FindFreeEntry(TStringPoolEntry* rRoot, int blockLength);

	static int GetTotalEntries(TStringPoolEntry* root);

private:
	static TStringPoolEntry* GetSmallestEntry(TStringPoolEntry* left, TStringPoolEntry* right, bool useBlockSize);
};

#endif
