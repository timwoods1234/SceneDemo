#include "TSkin.h"
#include "TResourceManager.h"
#include "TTexture.h"

//-------------------------------------------------------------------------------
TSkin* TSkin::Acquire(const char* id)
{
	if (id == NULL)
	{
		TSkin* result = TNew TSkin();

		result->AddRef();

		// TODO: set default (white) skin here?

		return result;
	}

	return (TSkin*)TResourceManager::Get()->Allocate(ResourceType_Skin, id);
}

//-------------------------------------------------------------------------------
void TSkin::Release(TSkin* skin)
{
	TResourceManager::Get()->Release(ResourceType_Skin, skin);
}

//-------------------------------------------------------------------------------
TSkin::TSkin()
{
}

//-------------------------------------------------------------------------------
TSkin::~TSkin()
{
	for (unsigned int index = 0; index < m_textures.GetSize(); index++)
	{
		TTexture::Release(m_textures[index]);
	}
}

//-------------------------------------------------------------------------------
void TSkin::SetMaterial(const TMaterial& material)
{
	m_material = material;
}

//-------------------------------------------------------------------------------
void TSkin::AddTexture(const char* propertyName, const char* textureId)
{
	m_textureProperties.Add(propertyName);
	m_textures.Add(TTexture::Acquire(textureId));
}

//-------------------------------------------------------------------------------
const TMaterial& TSkin::GetMaterial() const
{
	return m_material;
}

//-------------------------------------------------------------------------------
unsigned int TSkin::GetNumTextures() const
{
	return m_textures.GetSize();
}

//-------------------------------------------------------------------------------
const TTexture* TSkin::GetTexture(unsigned int index) const
{
	if (index >= 0 && index < m_textures.GetSize())
	{
		return m_textures[index];
	}

	return NULL;
}

//-------------------------------------------------------------------------------
const char* TSkin::GetTextureProperty(unsigned int index) const
{
	if (index >= 0 && index < m_textures.GetSize())
	{
		return m_textureProperties[index].GetPointer();
	}

	return NULL;
}

//-------------------------------------------------------------------------------
TRefCountedObject* TSkin::Load(const char* filename)
{
	// TODO: if file exists, read it
	// e.g. for editable skins (bump map, etc)

	TSkin* skin = TNew TSkin();

	return skin;
}

//-------------------------------------------------------------------------------
void TSkin::Unload(TRefCountedObject* object)
{
	TSkin* skin = static_cast<TSkin*>(object);

	TSafeDelete(skin);
}