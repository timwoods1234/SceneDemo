#ifndef __TFONT_H__
#define __TFONT_H__

// TODO: make this like mesh/sprite
// so one renderQueued function, called from UILabel, which assumes shader is set
// one renderNow function, called everywhere else, which sets shader manually

#ifndef __TREFCOUNTEDOBJECT_H__
#include "TRefCountedObject.h"
#endif

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

#ifndef __TCOLOR_H__
#include "TColor.h"
#endif

class TVector2;

class TFont : public TRefCountedObject,
              public TXMLObject
{
public:
    static TFont* Acquire(const char* id);

    static void Release(TFont* font);

    TFont(const char* filename);

	unsigned int GetSize() const;

	const TColor& GetColor() const;

	void SetColor(const TColor& color);

    virtual ~TFont();

    virtual void PrintText(const TVector2& position, const char* formattedText, ...) = 0;

    virtual TXMLObject* HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects);

    virtual void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);

    virtual void FinaliseLoad();

    virtual void Write(TXMLWriter& writer);

protected:
	const static int c_formatBufferSize = 1024;
    char m_formatBuffer[c_formatBufferSize];

    TColor m_color;

    unsigned int m_size;

private:
    friend class TResourceManager;

    static TRefCountedObject* Load(const char* id);

    static void Unload(TRefCountedObject* toDelete);
};

#endif

