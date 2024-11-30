#include "WorldBoxes.h"
#include "ModelPlugin.h"

//-------------------------------------------------------------------------------
WorldBoxes::WorldBoxes()
{
}

//-------------------------------------------------------------------------------
WorldBoxes::~WorldBoxes()
{
	m_worldBoxes.Clear();
}

//-------------------------------------------------------------------------------
void WorldBoxes::AddEntity(TEntity* entity)
{
	if (entity != NULL)
	{
		ModelPlugin* modelPlugin = static_cast<ModelPlugin*>(entity->GetPlugin("Model"));
		
		if (modelPlugin != NULL)
		{
			WorldBox worldBox;
			
			worldBox.entity = entity;
			modelPlugin->ComputeBounds(worldBox.box);
			
			m_worldBoxes.Add(worldBox);
		}
	}
}

//-------------------------------------------------------------------------------
TEntity* WorldBoxes::PickEntity(const TRay& ray) const
{
	// TODO: should do a proper triangle pick if prop meshes are irregular

	unsigned int indexOfClosestBox = -1;
	float closestDistanceSq = FLT_MAX;
	bool inBounds = false;

	TVector3 intersectionPoint(0.f, 0.f, 0.f);

	for (unsigned int index = 0; index < m_worldBoxes.GetSize(); index++)
	{
		if (m_worldBoxes[index].box.IsInside(ray.GetOrigin()))
		{
			const float distanceSq = (m_worldBoxes[index].entity->GetPosition() - ray.GetOrigin()).GetSquaredLength();

			if (!inBounds)
			{
				inBounds = true;

				closestDistanceSq = distanceSq;
				indexOfClosestBox = index;
			}
			else
			{
				// use the closest Entity if we are inside multiple bounding boxes
				if (distanceSq < closestDistanceSq)
				{
					closestDistanceSq = distanceSq;
					indexOfClosestBox = index;
				}
			}
		}
		else if (!inBounds && GetIntersectPoints(ray, m_worldBoxes[index].box, intersectionPoint))
		{
			const float distanceSq = (intersectionPoint - ray.GetOrigin()).GetSquaredLength();

			if (distanceSq < closestDistanceSq)
			{
				closestDistanceSq = distanceSq;
				indexOfClosestBox = index;
			}
		}
	}

	if (indexOfClosestBox != -1)
	{
		return m_worldBoxes[indexOfClosestBox].entity;
	}

	return NULL;
}
