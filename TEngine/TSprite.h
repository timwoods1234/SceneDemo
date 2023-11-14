#ifndef __TSPRITE_H__
#define __TSPRITE_H__

// a sprite instance

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

#ifndef __TVECTOR4_H__
#include "TVector4.h"
#endif

#ifndef __TSTRING_H__
#include "TString.h"
#endif

class TSpriteDefinition;
class TTexture;
struct TSpriteAnimation;

class TSprite
{
public:
	static TSprite* Load(const char* id);

	static void Unload(TSprite* sprite);

	TSprite(TSpriteDefinition* definition);

	~TSprite();

	void SetAnimation(const TString& animationName);

	bool IsAnimationPlaying() const;

	TSpriteDefinition* GetDefinition() const;
	
	void Render(const TVector2 & position, float rotation=0.0f, float scaleX=1.0f, float scaleY=1.0f);

	const TString& GetCurrentAnimation() const;

private:
	TTexture* CalculateCurrentFrame(unsigned int frame, TVector4& texCoords);

	TSpriteDefinition* m_definition;
	const TSpriteAnimation* m_currentAnimation;

	TVector4 m_texCoords;

	float m_animationStartTime;
};

#endif
