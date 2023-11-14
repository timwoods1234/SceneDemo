#ifndef __TSCENEINTERFACE_H__
#define __TSCENEINTERFACE_H__

// base class for a scene of entities
// handles rendering, culling, collision detection

class TRenderableInterface;
class TEntity;
class TCamera;

class TSceneInterface
{
public:
	TSceneInterface() {}
	virtual ~TSceneInterface() {}

	virtual void Clear() = 0;

	virtual void OnRender(TCamera* camera) = 0;	// cull based on Entry->TRenderableInterface->GetBounds

	virtual void PerformCollisionDetection() = 0;	// test based on Entry->Collider (and collision layers)

	virtual void AddEntry(TRenderableInterface* renderable) = 0;

	virtual void RemoveEntry(TRenderableInterface* renderable) = 0;
};

#endif