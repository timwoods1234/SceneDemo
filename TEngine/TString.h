#ifndef __TSTRING_H__
#define __TSTRING_H__

#ifndef __TSTRINGPOOL_H__
#include "TStringPool.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TSTRINGHELPER_H__
#include "TStringHelper.h"
#endif

class TString
{
public:
	static const TString& GetEmptyString();

	static TString Format(const char* format, ...);

	TString();
	TString(const char* data);
	TString(const TString& other);
	~TString();
	
	inline TString& operator=(const char* data);
	TString& operator=(const TString& other);

	inline bool operator==(const TString& other) const;
	bool operator==(const char* data) const;

	bool operator!=(const TString& other) const;
	bool operator!=(const char* data) const;

	const TString operator+(const TString& other);
	const TString operator+(const char* data);

	TString& operator+=(const char* data);
	TString& operator+=(const TString& other);

	int Find(const char* text, int startIndex = 0) const;
	int IndexOf(char toFind) const;
	int LastIndexOf(char toFind) const;
	int GetLength() const;

	bool IsEmpty() const;
	const char* GetPointer() const;
	void Split(char splitter, TDynamicSet<TString>& output) const;
	TString SubString(int start, int length = -1) const;
	bool Contains(const char* text) const;

	void Remove(int index, int count = -1);
	void Remove(char c);
	void Clear();

private:
	TStringPoolEntry* m_poolEntry;
};

#include "TString.inl"

#endif
