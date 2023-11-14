#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#ifndef __TENGINEINCLUDED_H__
#include "TEngine.h"
#endif

class Terrain;

class GameWorld : public TXMLObject
{
public:
		GameWorld(const Terrain* terrain);

		~GameWorld();

		TXMLObject* HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects);

		void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);

		void FinaliseLoad();

		void Write(TXMLWriter& writer);

private:
	void BuildGrassPatch(const TVector3& center);

	const Terrain* m_terrain;

	TDynamicSet<TEntity*> m_scenery;

	void GetAngularDistance(float distance, float angle, TVector3& result);
};

#endif
