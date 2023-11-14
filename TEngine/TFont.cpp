#include "TFont.h"
#include "TResourceManager.h"
#include "TXMLReader.h"
#include "TLocator.h"
#include "TGraphicsFactoryInterface.h"

//-------------------------------------------------------------------------------
TFont* TFont::Acquire(const char* id)
{
    TString filename = TString::Format("Assets/Font/%s.xml", id);

    TFont* result = (TFont*)TResourceManager::Get()->Allocate(ResourceType_Font, filename.GetPointer());

    return result;
}

//-------------------------------------------------------------------------------
void TFont::Release(TFont* font)
{
    TResourceManager::Get()->Release(ResourceType_Font, font);
}

//-------------------------------------------------------------------------------
TRefCountedObject* TFont::Load(const char* id)
{
    TFont* font = TLocator::GetGraphicsFactory()->CreateTFont(id);

    return font;
}

//-------------------------------------------------------------------------------
void TFont::Unload(TRefCountedObject* toDelete)
{
    TFont* font = static_cast<TFont*>(toDelete);

    TLocator::GetGraphicsFactory()->UnloadFont(font);
}

//-------------------------------------------------------------------------------
TFont::TFont(const char* filename)
:   m_size(1)
{
    TXMLReader reader(filename, *this);

    if (reader.WasError())
    {
        TDebugPrint(("[TFont] Failed to parse %s", filename));
    }
}

//-------------------------------------------------------------------------------
TFont::~TFont()
{
}

//-------------------------------------------------------------------------------
unsigned int TFont::GetSize() const
{
	return m_size;
}

//-------------------------------------------------------------------------------
TXMLObject* TFont::HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects)
{
    return NULL;
}

//-------------------------------------------------------------------------------
void TFont::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
    int r = TDataVariant::Find("r", objects).GetInt();
    int g = TDataVariant::Find("g", objects).GetInt();
    int b = TDataVariant::Find("b", objects).GetInt();

    m_color.Set((float)(r / 255), (float)(g / 255), (float)(b / 255), 1.f);

    m_size = TDataVariant::Find("size", objects).GetInt();
}

//-------------------------------------------------------------------------------
void TFont::FinaliseLoad()
{
}

//-------------------------------------------------------------------------------
void TFont::Write(TXMLWriter& writer)
{
}

//-------------------------------------------------------------------------------
const TColor& TFont::GetColor() const
{
	return m_color;
}

//-------------------------------------------------------------------------------
void TFont::SetColor(const TColor& color)
{
	m_color = color;
}