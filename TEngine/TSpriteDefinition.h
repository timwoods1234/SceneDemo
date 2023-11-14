#ifndef __TSPRITEDEFINITION_H__
#define __TSPRITEDEFINITION_H__

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

#ifndef __TSTRING_H__
#include "TString.h"
#endif

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

#ifndef __TSPRITEANIMATION_H__
#include "TSpriteAnimation.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TREFCOUNTEDOBJECT_H__
#include "TRefCountedObject.h"
#endif

class TSpriteDefinition : public TXMLObject, 
						  public TRefCountedObject
{
public:
    static TSpriteDefinition* Acquire(const char* id);

    static void Release(TSpriteDefinition* sprite);

	TSpriteDefinition();
	~TSpriteDefinition();

	const TVector2& GetDimensions() const;
	const TSpriteAnimation* GetAnimation(const TString& animationName) const;
	const TString& GetDefaultAnimation() const;

	TXMLObject* HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects);
	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void FinaliseLoad();
	void Write(TXMLWriter& writer);

protected:
    friend class TResourceManager;
    static TRefCountedObject* Load(const char* path);
    static void Unload(TRefCountedObject* toDelete);

    void LoadAllAnimationFrames(const char* relativePath);
	void LoadAnimationFrames(TSpriteAnimation& animation, const char* relativePath);

	TDynamicSet<TSpriteAnimation> m_animations;

	TVector2			m_dimensions;

	TString				m_spriteName;
};

#endif