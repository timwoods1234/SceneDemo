#ifndef __WORLDBOXES_H__
#define __WORLDBOXES_H__

#ifndef __TENGINEINCLUDED_H__
#include "TEngine.h"
#endif

class WorldBoxes
{
public:
	WorldBoxes();

	~WorldBoxes();
	
	void AddEntity(TEntity* entity);
	
	TEntity* PickEntity(const TRay& ray) const;

private:

	struct WorldBox
	{
		TEntity* entity;
		TAABB box;
	};
	
	TDynamicSet<WorldBox> m_worldBoxes;
};

#endif
