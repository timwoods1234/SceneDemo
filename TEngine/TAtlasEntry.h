#ifndef __TATLASENTRY_H__
#define __TATLASENTRY_H__

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

#ifndef __TSTRING_H__
#include "TString.h"
#endif

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

#ifndef __TVECTOR4_H__
#include "TVector4.h"
#endif

class TAtlasEntry : public TXMLObject
{
public:
	// TODO: catch output folder not existing
	TAtlasEntry();
	~TAtlasEntry();

	void SetFilename(const char* filename);
	void SetTexturePage(const char* filename);
	void SetSize(int x, int y);
	void SetTextureCoords(float x, float y, float z, float w);

	const TString& GetTexturePage() const;
	const TString& GetFilename() const;
	const TVector2& GetSize() const;
	const TVector4& GetTextureCoords() const;

	TXMLObject* HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects);
	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void FinaliseLoad();
	void Write(TXMLWriter& writer);

private:
	TString m_filename;
	TString m_texturePage;

	TVector2 m_size;
	TVector4 m_texCoords;
};

#endif
