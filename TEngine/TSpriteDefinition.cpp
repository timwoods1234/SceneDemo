#include "TSpriteDefinition.h"
#include "TXMLReader.h"
#include "TTexture.h"
#include "TAtlasManager.h"
#include "TAtlasEntry.h"
#include "TResourceManager.h"
#include "TShader.h"

//-------------------------------------------------------------------------------
static const TString s_animationID = "Animation";
static const TString s_nameID = "name"; 
static const TString s_animationName = "animationName";
static const TString s_animationLoop = "loop";
static const TString s_animationNext = "nextAnimation";
static const TString s_frameRate = "frameRate";
static const TString s_numFrames = "numFrames";

//-------------------------------------------------------------------------------
TSpriteDefinition* TSpriteDefinition::Acquire(const char* id)
{
    TString filename = TString::Format("Assets/2D/%s/definition.xml", id);

    TSpriteDefinition* result = (TSpriteDefinition*)TResourceManager::Get()->Allocate(ResourceType_SpriteDefinition, filename.GetPointer());

	if (result != NULL && result->GetRefCount() == 1)
    {
        result->LoadAllAnimationFrames(id);
    }

    return result;
}

//-------------------------------------------------------------------------------
void TSpriteDefinition::Release(TSpriteDefinition* sprite)
{
    TResourceManager::Get()->Release(ResourceType_SpriteDefinition, sprite);
}

//-------------------------------------------------------------------------------
TRefCountedObject* TSpriteDefinition::Load(const char* path)
{
	TSpriteDefinition* result = TNew TSpriteDefinition();

    TXMLReader spriteReader(path, *result);

    if (spriteReader.WasError())
    {
        TDebugPrint(("[TSpriteDefinition::Load] Failed to load %s", path));

        TSafeDelete(result);
    }

	return result;
}

//-------------------------------------------------------------------------------
void TSpriteDefinition::Unload(TRefCountedObject* toDelete)
{
	TSpriteDefinition* spriteDefinition = static_cast<TSpriteDefinition*>(toDelete);

    TSafeDelete(spriteDefinition);
}

//-------------------------------------------------------------------------------
TSpriteDefinition::TSpriteDefinition()
:	m_dimensions(0.f, 0.f)
{
}

//-------------------------------------------------------------------------------
TSpriteDefinition::~TSpriteDefinition()
{
	for (unsigned int animationIndex = 0; animationIndex < m_animations.GetSize(); animationIndex++)
	{
		for (unsigned int frameIndex = 0; frameIndex < m_animations[animationIndex].frames.GetSize(); frameIndex++)
		{
			TTexture::Release(m_animations[animationIndex].frames[frameIndex]);
		}
	}
}

//-------------------------------------------------------------------------------
const TVector2& TSpriteDefinition::GetDimensions() const
{
	return m_dimensions;
}

//-------------------------------------------------------------------------------
const TSpriteAnimation* TSpriteDefinition::GetAnimation(const TString& animationName) const
{
	for (unsigned int animationIndex = 0; animationIndex < m_animations.GetSize(); animationIndex++)
	{
		if (m_animations[animationIndex].name == animationName)
		{
			return &m_animations[animationIndex];
		}
	}

	return NULL;
}

//-------------------------------------------------------------------------------
const TString& TSpriteDefinition::GetDefaultAnimation() const
{
	if (m_animations.GetSize() > 0)
	{
		return m_animations[0].name;
	}

	return TString::GetEmptyString();
}

//-------------------------------------------------------------------------------
TXMLObject* TSpriteDefinition::HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects)
{
	if (s_animationID == id)
	{
		TSpriteAnimation newAnimation;

		newAnimation.name = TDataVariant::Find(s_animationName, objects).GetString();
		newAnimation.loop = TDataVariant::Find(s_animationLoop, objects).GetBool();
		newAnimation.nextAnim = TDataVariant::Find(s_animationNext, objects).GetString();
		newAnimation.frameRate = TDataVariant::Find(s_frameRate, objects).GetFloat();
		newAnimation.numFrames = TDataVariant::Find(s_numFrames, objects).GetInt();

		m_animations.Add(newAnimation);
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void TSpriteDefinition::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_spriteName = TDataVariant::Find(s_nameID, objects).GetString();
}

//-------------------------------------------------------------------------------
void TSpriteDefinition::FinaliseLoad()
{
}

//-------------------------------------------------------------------------------
void TSpriteDefinition::Write(TXMLWriter& writer)
{
}

//-------------------------------------------------------------------------------
void TSpriteDefinition::LoadAllAnimationFrames(const char* relativePath)
{
    for (unsigned int animationIndex = 0; animationIndex < m_animations.GetSize(); animationIndex++)
    {
        LoadAnimationFrames(m_animations[animationIndex], relativePath);
    }
}

//-------------------------------------------------------------------------------
void TSpriteDefinition::LoadAnimationFrames(TSpriteAnimation& animation, const char* relativePath)
{
	TString filePath = TString::Format("Assets/2D/%s/%s/%s_%s_", 
        relativePath,
		animation.name.GetPointer(), 
		m_spriteName.GetPointer(),  // TODO: think about removing this by embedding it in the animation name
		animation.name.GetPointer());

	TTexture* currentFrameTexture;
	TVector4 texCoords;
	TString currentFramePath;

	for (unsigned int frameIndex = 0; frameIndex < animation.numFrames; frameIndex++)
	{
		currentFramePath = TString::Format("%s%02d.png", filePath.GetPointer(), frameIndex);

		const TAtlasEntry* atlasEntry = TAtlasManager::Get()->GetEntry(currentFramePath);

		if (atlasEntry != NULL)
		{
			currentFrameTexture = TTexture::Acquire(atlasEntry->GetTexturePage().GetPointer());

			texCoords = atlasEntry->GetTextureCoords();

			if (m_dimensions.x == 0.f)
			{
				m_dimensions = atlasEntry->GetSize();
			}
		}
		else
		{
			// load the individual texture, although this will reduce batching
			currentFrameTexture = TTexture::Acquire(currentFramePath.GetPointer());

			if (currentFrameTexture != NULL)
			{
				m_dimensions.Set((float)currentFrameTexture->GetWidth(), (float)currentFrameTexture->GetHeight());
			}

			texCoords.Set(0, 0, 1, 1);
		}

		animation.frames.Add(currentFrameTexture);
		animation.textureCoords.Add(texCoords);
	}

	TASSERT((animation.frames.GetSize() > 0), "[TSpriteDefinition::LoadAnimationFrames] No frames loaded");
}
