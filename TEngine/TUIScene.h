#ifndef __TUISCENE_H__
#define __TUISCENE_H__

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

struct TUISceneEntry;
class TRenderableInterface;

class TUIScene : public TSingleton<TUIScene>,
				 public TEventListener
{
public:
	TUIScene();
	~TUIScene();

	void AddEntry(TRenderableInterface* renderable);

	void RemoveEntry(TRenderableInterface* renderable);

	void OnRender();

private:
	TUISceneEntry* m_sceneRoot;
};

#endif
