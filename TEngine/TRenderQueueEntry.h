#ifndef __TRENDERQUEUEENTRY_H__
#define __TRENDERQUEUEENTRY_H__

class TEntity;
class TMesh;

struct TRenderQueueEntry
{
	const TEntity* entity;
	const TMesh* mesh;
};

#endif
