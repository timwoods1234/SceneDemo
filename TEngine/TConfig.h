#ifndef __TCONFIG_H__
#define __TCONFIG_H__

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class TConfig : public TXMLObject,
				public TSingleton<TConfig>
{
public:
	TConfig();

	~TConfig();

	float GetScreenWidth() const;

	float GetScreenHeight() const;

	bool IsWindowed() const;

	bool UseBatching() const;

	unsigned int GetNumAtlases() const;

	const TString& GetAtlasFilename(unsigned int index) const;

	TXMLObject* HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects);

	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);

	void FinaliseLoad();

	void Write(TXMLWriter& writer);

private:
	float m_screenWidth;
	float m_screenHeight;
	bool m_windowed;
	bool m_useBatching;

	TDynamicSet<TString> m_atlasNames;
};

#endif
