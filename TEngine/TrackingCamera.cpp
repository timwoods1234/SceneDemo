#include "TCamera.h"
#include "TrackingCamera.h"
#include "TEntity.h"

//-------------------------------------------------------------------------------
TrackingCamera::TrackingCamera(TCamera* camera)
:	FreeCamera(camera),
	m_target(NULL)
{
}

//-------------------------------------------------------------------------------
TrackingCamera::~TrackingCamera()
{

}

//-------------------------------------------------------------------------------
void TrackingCamera::Update(float elapsedTime)
{
	FreeCamera::Update(elapsedTime);

	if (m_target != NULL)
	{
		m_camera->LookAt(m_camera->GetPosition(), m_target->GetPosition(), TCamera::Up());
	}
}

//-------------------------------------------------------------------------------
void TrackingCamera::SetTarget(TEntity* target)
{
	m_target = target;
}
