#ifndef __TEVENTUPDATE_H__
#define __TEVENTUPDATE_H__

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

#ifndef __TEVENTPARAM_H__
#include "TEventParam.h"
#endif

#ifndef __TERROR_H__
#include "TError.h"
#endif

class TEventUpdate : public TEventParam<float>, public TSingleton<TEventUpdate>
{
public:

	TEventUpdate();

	~TEventUpdate();
};

#endif
