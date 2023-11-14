#ifndef __TDATAVARIANT_H__
#define __TDATAVARIANT_H__

#ifndef __TSTRING_H__
#include "TString.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class TDataVariant
{
public:
	TDataVariant();
	TDataVariant(const char* id, const char* data);

	~TDataVariant();

	void Setup(const char* id, const char* data);

	const char* GetString() const;
	int			GetInt() const;
	float		GetFloat(float defaultValue = 0.f) const;
	bool		GetBool() const;

	static const TDataVariant& Find(const char* tagId, TDynamicSet<TDataVariant>& data);
	static const TDataVariant& Find(const TString& tagId, TDynamicSet<TDataVariant>& data);

private:
	static const TDataVariant s_default;

	TString m_tagId;
	TString m_data;
};

#endif
