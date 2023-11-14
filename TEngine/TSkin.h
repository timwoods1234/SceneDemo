#ifndef __TSKIN_H__
#define __TSKIN_H__

#ifndef __TREFCOUNTEDOBJECT_H__
#include "TRefCountedObject.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TMATERIAL_H__
#include "TMaterial.h"
#endif

class TTexture;

class TSkin : public TRefCountedObject
{
public:
	static TSkin* Acquire(const char* id = NULL);

	static void Release(TSkin* skin);

	~TSkin();

	void SetMaterial(const TMaterial& material);

	void AddTexture(const char* propertyName, const char* textureId);

	const TMaterial& GetMaterial() const;

	unsigned int GetNumTextures() const;

	const TTexture* GetTexture(unsigned int index) const;

	const char* GetTextureProperty(unsigned int index) const;

private:
	TSkin();

	friend class TResourceManager;

	static TRefCountedObject* Load(const char* filename);

	static void Unload(TRefCountedObject* object);

	TMaterial m_material;

	TDynamicSet<TTexture*> m_textures;

	TDynamicSet<TString> m_textureProperties;
};

#endif
