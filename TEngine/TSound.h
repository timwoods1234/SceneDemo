#ifndef __TSOUND_H__
#define __TSOUND_H__

#ifndef __TREFCOUNTEDOBJECT_H__
#include "TRefCountedObject.h"
#endif

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

class TSound : public TRefCountedObject,
               public TXMLObject
{
public:
    static TSound* Acquire(const char* id);

    static void Release(TSound* sound);

    TSound(const char* filename);

    virtual ~TSound();

    virtual void Play() = 0;

    virtual void Stop() = 0;

	virtual void SetPaused(bool pause) = 0;

	virtual bool IsPaused() = 0;

    virtual bool IsPlaying() = 0;

    TXMLObject*		HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects);

    void			HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);

    void			FinaliseLoad();

    void			Write(TXMLWriter& writer);

protected:
    bool m_loop;

	bool m_paused;

private:
    friend class TResourceManager;

    static TRefCountedObject* Load(const char* id);

    static void Unload(TRefCountedObject* toDelete);

    static TString GetXMLFilename(const char* filename);
};

#endif
