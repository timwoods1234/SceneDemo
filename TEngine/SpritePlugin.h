#ifndef __SPRITEPLUGIN_H__
#define __SPRITEPLUGIN_H__

#ifndef __TRENDERABLEINTERFACE_H__
#include "TRenderableInterface.h"
#endif

#ifndef __SPRITEPLUGINDEFINITION_H__
#include "SpritePluginDefinition.h"
#endif

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

class TSprite;

class SpritePlugin : public TRenderableInterface,
					 public TEventListener
{
public:
	static void Register();

	SpritePlugin(TEntity* entity, TPluginDefinition* definition);
	~SpritePlugin();

	float GetRotation() const;
	void SetRotation(float rotation);

	void OnRender();
	void ComputeBounds(TAABB& box);

	const TVector2& GetRenderOffset() const;
	void SetRenderOffset(const TVector2& offset);

	const TString& GetCurrentAnimation() const;
	void SetAnimation(const TString& animationName);

	bool IsAnimationPlaying() const;

private:
	TSprite* m_sprite;
	TVector2 m_renderOffset;
	float m_rotation;
};

#endif
