#ifndef __TUIVARIABLERESULT_H__
#define __TUIVARIABLERESULT_H__

#ifndef __TSTRING_H__
#include "TString.h"
#endif

struct TUIVariableResult
{
	TString stringValue;

	float floatValue;

	int intValue;
};

#endif
