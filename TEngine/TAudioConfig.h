#ifndef __TAUDIOCONFIG_H__
#define __TAUDIOCONFIG_H__

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

class TAudioConfig : public TXMLObject
{
public:
	TAudioConfig();
	~TAudioConfig();

	TXMLObject* HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects);
	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void FinaliseLoad();
	void Write(TXMLWriter& writer);

private:
	float m_volume;
};

#endif
