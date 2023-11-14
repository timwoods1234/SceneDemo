#include "TSprite.h"
#include "TSpriteDefinition.h"
#include "TTimerInterface.h"
#include "TLocator.h"
#include "TRendererInterface.h"

//-------------------------------------------------------------------------------
TSprite* TSprite::Load(const char* id)
{
	TSprite* result = NULL;

	TSpriteDefinition* definition = TSpriteDefinition::Acquire(id);

	if (definition != NULL)
	{
		result = TNew TSprite(definition);
	}

	return result;
}

//-------------------------------------------------------------------------------
void TSprite::Unload(TSprite* sprite)
{
	TSafeDelete(sprite);
}

//-------------------------------------------------------------------------------
TSprite::TSprite(TSpriteDefinition* definition)
:	m_currentAnimation(NULL),
	m_animationStartTime(0.f)
{
	m_definition = definition;

	SetAnimation(definition->GetDefaultAnimation());
}

//-------------------------------------------------------------------------------
TSprite::~TSprite()
{
	TSpriteDefinition::Release(m_definition);
}

//-------------------------------------------------------------------------------
void TSprite::SetAnimation(const TString& animationName)
{
	m_currentAnimation = m_definition->GetAnimation(animationName);

	m_animationStartTime = TLocator::GetTimer()->GetAppTime();
}

//-------------------------------------------------------------------------------
bool TSprite::IsAnimationPlaying() const
{
	if (m_currentAnimation != NULL)
	{
		if (m_currentAnimation->loop)
		{
			return false;
		}

		float animationTime = TLocator::GetTimer()->GetAppTime() - m_animationStartTime;

		return ( (animationTime * m_currentAnimation->frameRate) < m_currentAnimation->numFrames);
	}

	return false;
}

//-------------------------------------------------------------------------------
const TString& TSprite::GetCurrentAnimation() const
{
	if (m_currentAnimation != NULL)
	{
		return m_currentAnimation->name;
	}

	return TString::GetEmptyString();
}

//-------------------------------------------------------------------------------
void TSprite::Render(const TVector2 & position, float rotation, float scaleX, float scaleY)
{
	unsigned int currentFrame = 0;
	TTexture* texture = CalculateCurrentFrame(currentFrame, m_texCoords);

	if (texture != NULL)
	{
		TLocator::GetRenderer()->Draw2D(texture, position, m_texCoords, rotation, m_definition->GetDimensions().x * scaleX, m_definition->GetDimensions().y * scaleY);
	}
}

//-------------------------------------------------------------------------------
TSpriteDefinition* TSprite::GetDefinition() const
{
	return m_definition;
}

//-------------------------------------------------------------------------------
TTexture* TSprite::CalculateCurrentFrame(unsigned int frame, TVector4& texCoords)
{
	TTexture* result = NULL;

	if (m_currentAnimation != NULL)
	{
		float animationTime = TLocator::GetTimer()->GetAppTime() - m_animationStartTime;

		int elapsedFrames = (int)(animationTime * m_currentAnimation->frameRate);

		int totalFrames = m_currentAnimation->numFrames;

		if (m_currentAnimation->loop)
		{
			unsigned int frameIndex = elapsedFrames % totalFrames;

			result = m_currentAnimation->frames[frameIndex];
			texCoords = m_currentAnimation->textureCoords[frameIndex];

			/*if (elapsedFrames >= totalFrames)
			{
				m_animationFinished = true;
			}*/
		}
		else
		{
			if (elapsedFrames >= totalFrames)
			{
				float newStartTime = m_animationStartTime + (totalFrames * m_currentAnimation->frameRate);

				SetAnimation(m_currentAnimation->nextAnim);

				m_animationStartTime = newStartTime;

				result = CalculateCurrentFrame(frame, texCoords);

				//m_animationFinished = true;
			}
			else
			{
				result = m_currentAnimation->frames[elapsedFrames];
				texCoords = m_currentAnimation->textureCoords[elapsedFrames];
			}
		}
	}

	return result;
}
