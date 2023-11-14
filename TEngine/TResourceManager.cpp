#include "TResourceManager.h"
#include "TTexture.h"
#include "TSpriteDefinition.h"
#include "TMesh.h"
#include "TShader.h"
#include "TUIGroup.h"
#include "TSound.h"
#include "TEntityDefinition.h"
#include "TFont.h"
#include "TSkin.h"

//-------------------------------------------------------------------------------
DefineSingleton(TResourceManager);

//-------------------------------------------------------------------------------
TResourceManager::TResourceManager()
{
    SetupPool(ResourceType_Texture, "Texture", TTexture::Load, TTexture::Unload);
    SetupPool(ResourceType_SpriteDefinition, "SpriteDefinition", TSpriteDefinition::Load, TSpriteDefinition::Unload);
    SetupPool(ResourceType_Mesh, "Mesh", TMesh::Load, TMesh::Unload);
    SetupPool(ResourceType_Shader, "Shader", TShader::Load, TShader::Unload);
    SetupPool(ResourceType_UIGroup, "UIGroup", TUIGroup::Load, TUIGroup::Unload);
	SetupPool(ResourceType_Sound, "Sound", TSound::Load, TSound::Unload);
	SetupPool(ResourceType_EntityDefinition, "EntityDefinition", TEntityDefinition::Load, TEntityDefinition::Unload);
	SetupPool(ResourceType_Font, "Font", TFont::Load, TFont::Unload);
	SetupPool(ResourceType_Skin, "Skin", TSkin::Load, TSkin::Unload);
}

//-------------------------------------------------------------------------------
TResourceManager::~TResourceManager()
{
	for (unsigned int index = 0; index < ResourceType_MAX; index++)
	{
		TSafeDelete(m_resourcePools[index]);
	}
}

//-------------------------------------------------------------------------------
void TResourceManager::SetupPool(TResourceType type, const char* id, LoadResourceCallback loadCallback, UnloadResourceCallback unloadCallback)
{
	m_resourcePools[type] = TNew TResourcePool(id, loadCallback, unloadCallback);
}

//-------------------------------------------------------------------------------
TRefCountedObject* TResourceManager::Allocate(TResourceType type, const char* id)
{
	TRefCountedObject* result = NULL;

	unsigned int typeIndex = (unsigned int)type;

	if (typeIndex >= 0 && typeIndex < ResourceType_MAX)
	{
		result = m_resourcePools[typeIndex]->Allocate(id);
	}

	return result;
}

//-------------------------------------------------------------------------------
void TResourceManager::Release(TResourceType type, TRefCountedObject* resource)
{
	if (resource != NULL)
	{
		unsigned int typeIndex = (unsigned int)type;

		if (typeIndex >= 0 && typeIndex < ResourceType_MAX)
		{
			m_resourcePools[typeIndex]->Release(resource);
		}
	}
}