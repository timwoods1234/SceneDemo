#include "TTexture.h"
#include "TLocator.h"
#include "TGraphicsFactoryInterface.h"
#include "TResourceManager.h"

//-------------------------------------------------------------------------------
TTexture* TTexture::Acquire(const char* id)
{
    return (TTexture*)TResourceManager::Get()->Allocate(ResourceType_Texture, id);
}

//-------------------------------------------------------------------------------
void TTexture::Release(TTexture* texture)
{
    TResourceManager::Get()->Release(ResourceType_Texture, texture);
}

//-------------------------------------------------------------------------------
TTexture* TTexture::LoadCubeMap(const char* id)
{
	TTexture* result = TNew TTexture();

	TString filepath = TString::Format("Assets/2D/%s", id);
	TLocator::GetGraphicsFactory()->LoadCubeTexture(filepath.GetPointer(), result);

	return result;
}

//-------------------------------------------------------------------------------
void TTexture::UnloadCubeMap(TTexture* texture)
{
	TLocator::GetGraphicsFactory()->UnloadTexture(*texture);
	TSafeDelete(texture);
}

//-------------------------------------------------------------------------------
TRefCountedObject* TTexture::Load(const char* id)
{
	TTexture* result = TNew TTexture();

	if (!TLocator::GetGraphicsFactory()->LoadTexture(id, result))
	{
		TDebugPrint(("[TTexture::Load] Failed to load %s", id));
		TSafeDelete(result);
	}

	return result;
}

//-------------------------------------------------------------------------------
void TTexture::Unload(TRefCountedObject* texture)
{
	TTexture* textureAsTexture = static_cast<TTexture*>(texture);

	TLocator::GetGraphicsFactory()->UnloadTexture(*textureAsTexture);

	TSafeDelete(texture);
}

//-------------------------------------------------------------------------------
TTexture::TTexture()
:	m_width(0),
	m_height(0),
	m_data(0)
{
}

//-------------------------------------------------------------------------------
TTexture::~TTexture()
{
}

//-------------------------------------------------------------------------------
unsigned int TTexture::GetWidth()const
{
	return m_width;
}

//-------------------------------------------------------------------------------
unsigned int TTexture::GetHeight() const
{
	return m_height;
}

//-------------------------------------------------------------------------------
void TTexture::SetWidth(unsigned int width)
{
	m_width = width;
}

//-------------------------------------------------------------------------------
void TTexture::SetHeight(unsigned int height)
{
	m_height = height;
}

//-------------------------------------------------------------------------------
void* TTexture::GetData() const
{
	return m_data;
}

//-------------------------------------------------------------------------------
void TTexture::SetData(void* data)
{
	m_data = data;
}
