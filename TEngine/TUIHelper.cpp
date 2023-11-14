#include "TUIHelper.h"
#include "TUIGroup.h"

//-------------------------------------------------------------------------------
TDynamicSet<TUIGroup*> TUIHelper::ms_activeGroups;

//-------------------------------------------------------------------------------
void TUIHelper::Show(const char* groupName)
{
	TString filename = TString::Format("Assets/Data/UI/%s.xml", groupName);

    for (unsigned int index = 0; index < ms_activeGroups.GetSize(); index++)
    {
        if (ms_activeGroups[index]->GetId() == filename)
        {
            return;
        }
    }

    TUIGroup* group = TUIGroup::Acquire(groupName);

	if (group != NULL)
	{
		ms_activeGroups.Add(group);
	}
}

//-------------------------------------------------------------------------------
void TUIHelper::Hide(const char* groupName)
{
	TString filename = TString::Format("Assets/Data/UI/%s.xml", groupName);

	TUIGroup* group = NULL;

    for (unsigned int index = 0; index < ms_activeGroups.GetSize(); index++)
    {
        if (ms_activeGroups[index]->GetId() == filename)
        {
			group = ms_activeGroups[index];

            ms_activeGroups.RemoveAt(index);

            break;
        }
    }

	if (group != NULL)
	{
		TUIGroup::Release(group);

		if (ms_activeGroups.GetSize() == 0)
		{
			ms_activeGroups.ReleaseMemory();
		}
	}
}
