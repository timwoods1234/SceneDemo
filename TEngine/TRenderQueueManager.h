#ifndef __TRENDERQUEUEMANAGER_H__
#define __TRENDERQUEUEMANAGER_H__

#ifndef __TSTRING_H__
#include "TString.h"
#endif

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

class TRenderQueue;

class TRenderQueueManager : public TSingleton<TRenderQueueManager>
{
public:
	TRenderQueueManager();

	~TRenderQueueManager();

	TRenderQueue* GetRenderQueue(const TString& id);

	void ProcessRenderQueue();
	
private:
	TRenderQueue* CreateRenderQueue(const TString& id);

	TRenderQueue* m_headQueue;
};

#endif
