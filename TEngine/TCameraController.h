#ifndef __TCAMERACONTROLLERINTERFACE_H__
#define __TCAMERACONTROLLERINTERFACE_H__

// Base class for camera controllers.

class TCamera;

class TCameraController
{
public:
	TCameraController(TCamera* camera);
	virtual ~TCameraController();

	virtual void Update(float elapsedTime) = 0;

	const TCamera* GetCamera() const;

protected:
	TCamera* m_camera;
};

#endif
