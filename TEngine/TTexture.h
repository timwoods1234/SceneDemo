#ifndef __TTEXTURE_H__
#define __TTEXTURE_H__

#ifndef __TREFCOUNTEDOBJECT_H__
#include "TRefCountedObject.h"
#endif

#ifndef __TSTRING_H__
#include "TString.h"
#endif

class TTexture : public TRefCountedObject
{
public:
    static TTexture* Acquire(const char* id);

    static void Release(TTexture* texture);

	static TTexture* LoadCubeMap(const char* id);

	static void UnloadCubeMap(TTexture* texture);

	TTexture();

	~TTexture();

	unsigned int GetWidth()const;

	unsigned int GetHeight() const;

	void SetWidth(unsigned int width);

	void SetHeight(unsigned int height);

	void* GetData() const;

	void SetData(void* data);

	void SetPixelData(void* pixelData);

private:
    friend class TResourceManager;

    static TRefCountedObject* Load(const char* id);

    static void Unload(TRefCountedObject* texture);

	unsigned int m_width;
	unsigned int m_height;
	
	// for d3d, will contain LPDIRECT3DTEXTURE9
	void* m_data;
};

#endif
