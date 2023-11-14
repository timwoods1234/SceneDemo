#ifndef __TSCENEENTRY_H__
#define __TSCENEENTRY_H__

class ColliderPlugin;
class TRenderableInterface;

class TSceneEntry
{
public:
	TSceneEntry(TRenderableInterface* renderable);
	~TSceneEntry();

	TRenderableInterface* GetRenderable() const;

	ColliderPlugin* GetCollider() const;

protected:
	ColliderPlugin* m_collider;
	TRenderableInterface* m_renderable;
};

#endif
