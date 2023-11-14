#ifndef __TSIMPLESCENE_H__
#define __TSIMPLESCENE_H__

#ifndef __TSCENEINTERFACE_H__
#include "TSceneInterface.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

class TSceneEntry;

class TSimpleScene : public TSceneInterface,
					 public TEventListener
{
public:
	TSimpleScene();
	~TSimpleScene();

	void Clear();
	void OnRender(TCamera* camera);
	void AddEntry(TRenderableInterface* renderable);
	void RemoveEntry(TRenderableInterface* renderable);

	// TODO: register for update event when a callback gets set
	// let the program code handle collisions itself
	void PerformCollisionDetection();

private:
	void PerformCleanup();

	TDynamicSet<TSceneEntry*> m_sceneEntries;
	TDynamicSet<TSceneEntry*> m_removeEntries;
};

#endif
