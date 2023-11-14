#ifndef __TUIVERTEXCACHE_H__
#define __TUIVERTEXCACHE_H__

// staging area for dynamic UI vertex data construction

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TVERTEXUI_H__
#include "TVertexUI.h"
#endif

#ifndef __TSTRING_H__
#include "TString.h"
#endif

class TSkin;

class TUIVertexCache
{
public:
    TUIVertexCache(const char* textureId);

    ~TUIVertexCache();

    void AddVertexData(TVertexUI* vertices, unsigned int numVertices, unsigned short* indices, unsigned int numIndices);

    void Clear();

    const void* GetVertexData() const;

    const unsigned short* GetIndexData() const;

    unsigned int GetNumIndices() const;

    unsigned int GetNumVertices() const;

	const TString& GetId() const;

	TSkin* GetSkin() const;

private:
	TString m_id;

	TSkin* m_skin;

    TDynamicSet<TVertexUI> m_vertices;
    unsigned int m_numVertices;

    TDynamicSet<unsigned short> m_indices;
    unsigned int m_numIndices;
};

#endif
