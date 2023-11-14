#ifndef __TUIHELPER_H__
#define __TUIHELPER_H__

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class TUIGroup;

class TUIHelper
{
public:
    static void Show(const char* groupName);

    static void Hide(const char* groupName);

private:
    static TDynamicSet<TUIGroup*> ms_activeGroups;
};

#endif

