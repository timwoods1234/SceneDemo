#ifndef __TREFCOUNTEDOBJECT_H__
#define __TREFCOUNTEDOBJECT_H__

#ifndef __TSTRING_H__
#include "TString.h"
#endif

class TRefCountedObject
{
public:
	TRefCountedObject();

	virtual ~TRefCountedObject();

	void AddRef();

	void RemoveRef();

	int GetRefCount() const;

	const TString& GetId() const;

	void SetId(const char* id);

protected:
	TString m_id;

	int m_refCount;
};

#endif
