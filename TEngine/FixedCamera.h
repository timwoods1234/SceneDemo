#ifndef __FIXEDCAMERA_H__
#define __FIXEDCAMERA_H__

// A camera controller that sits at a fixed offset from a target.

#ifndef __TCAMERACONTROLLERINTERFACE_H__
#include "TCameraController.h"
#endif

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

class TEntity;

class FixedCamera : public TCameraController
{
public:
	FixedCamera(TCamera* camera);
	~FixedCamera();

	void Update(float elapsedTime);
	void SetOffset(const TVector3 & newOffset);
	void SetTarget(TEntity* target);
	void SetTarget(const TVector3& targetPosition);

private:
	TEntity* m_target;
	TVector3 m_targetPosition;
	TVector3 m_offset;
};

#endif
