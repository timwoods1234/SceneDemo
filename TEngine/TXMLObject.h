#ifndef __TXMLOBJECT_H__
#define __TXMLOBJECT_H__

#ifndef __TDATAVARIANT_H__
#include "TDataVariant.h"
#endif

class TString;
class TXMLWriter;

class TXMLObject
{
public:
	virtual ~TXMLObject()	{}

	virtual TXMLObject*		HandleLoadElement(const TString& strId, TDynamicSet<TDataVariant>& objects) = 0;
	virtual void			HandleLoadAttributes(TDynamicSet<TDataVariant>& objects) = 0;
	virtual void			FinaliseLoad() = 0;
	virtual void			Write(TXMLWriter& writer) = 0;
};

#endif
