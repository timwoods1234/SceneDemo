#ifndef __TRACKINGCAMERA_H__
#define __TRACKINGCAMERA_H__

// A movable camera that always faces a target entity

#ifndef __FREECAMERA_H__
#include "FreeCamera.h"
#endif

class TEntity;

class TrackingCamera : public FreeCamera
{
public:
	TrackingCamera(TCamera* camera);
	~TrackingCamera();

	void Update(float elapsedTime);
	void SetTarget(TEntity* target);

private:
	TEntity* m_target;
};

#endif