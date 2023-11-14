#ifndef __TXMLATTRIBUTE_H__
#define __TXMLATTRIBUTE_H__

#ifndef __TSTRING_H__
#include "TString.h"
#endif

struct TXMLAttribute
{
	enum TXMLAttributeType
	{
		Invalid,
		ElementStart,
		Attribute,
		ElementEnd,
	};

	TXMLAttributeType type;

	TString id;
	TString value;
};

#endif
