#ifndef __ANCHOREDCAMERA_H__
#define __ANCHOREDCAMERA_H__

#ifndef __TCAMERACONTROLLERINTERFACE_H__
#include "TCameraController.h"
#endif

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

#ifndef __TMATRIX_H__
#include "TMatrix.h"
#endif

class TEntity;

class AnchoredCamera : public TCameraController
{
public:
	AnchoredCamera(TCamera* camera);
	~AnchoredCamera();

	void Update(float elapsedTime);

	void SetZoomSpeed(float speed);
	float GetZoomSpeed() const;

	void SetMaxDistance(float maxDistance);
	float GetMaxDistance() const;

	void EnableAxis(bool x, bool y);

	void SetTarget(TEntity* entity);
	void SetTarget(const TVector3& targetPosition);
	const TVector3& GetTarget() const;

private:
	void ProcessInput(float elapsedTime);

	TEntity* m_targetEntity;
	TVector3 m_targetPosition;

	bool m_enableX;
	bool m_enableY;

	TMatrix m_orientation;
	float m_distance;
	float m_maxDistance;
	float m_zoomSpeed;
	float m_moveSpeed;
	float m_pitch;
	float m_yaw;
};

#endif
