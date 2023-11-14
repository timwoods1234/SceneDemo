#ifndef __TRENDERQUEUE_H__
#define __TRENDERQUEUE_H__

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TRENDERQUEUEENTRY_H__
#include "TRenderQueueEntry.h"
#endif

class TShader;

class TRenderQueue
{
public:
	TRenderQueue(TShader* shader);

	~TRenderQueue();
	
	void AddEntry(const TEntity* entity, const TMesh* mesh);

	void ExecuteRender();

	void Clear();
	
	TShader* GetShader() const;

	void SetNextQueue(TRenderQueue* queue);

	TRenderQueue* GetNext() const;

private:
	TRenderQueue* m_nextQueue;

	TShader* m_shader;
	
	TDynamicSet<TRenderQueueEntry> m_renderQueueEntries;
};

#endif
