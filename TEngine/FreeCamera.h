#ifndef __FREECAMERA_H__
#define __FREECAMERA_H__

// A camera controller that can be manipulated with the keyboard & mouse.

#ifndef __TCAMERACONTROLLERINTERFACE_H__
#include "TCameraController.h"
#endif

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

class FreeCamera : public TCameraController
{
public:
	FreeCamera(TCamera* camera);

	~FreeCamera();

	virtual void Update(float elapsedTime);

	void SetPosition(const TVector3& newPosition);

	void SetSensitivity(float newSens);

	const TVector3& GetPosition() const;

	float GetSpeed() const;

	void SetSpeed(float speed);

protected:
	TVector3			m_cameraPosition;
	TMatrix				m_cameraTransform;
	float				m_cameraPitch;
	float				m_cameraYaw;
	float				m_speed;
	float				m_sensitivity;
};

#endif
