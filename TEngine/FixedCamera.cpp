#include "FixedCamera.h"
#include "TCamera.h"
#include "TEntity.h"

//-------------------------------------------------------------------------------
FixedCamera::FixedCamera(TCamera* camera)
:	TCameraController(camera),
	m_offset(0,0,0),
	m_target(NULL),
	m_targetPosition(0,0,0)
{

}

//-------------------------------------------------------------------------------
FixedCamera::~FixedCamera()
{

}

//-------------------------------------------------------------------------------
void FixedCamera::Update(float elapsedTime)
{
	if (m_target != NULL)
	{
		m_targetPosition = m_target->GetPosition();
	}

	m_camera->LookAt(( m_targetPosition + m_offset ), m_targetPosition, TCamera::Up() );
}

//-------------------------------------------------------------------------------
void FixedCamera::SetOffset(const TVector3 & newOffset)
{
	m_offset = newOffset;
}

//-------------------------------------------------------------------------------
void FixedCamera::SetTarget(const TVector3 & targetPosition)
{
	m_targetPosition = targetPosition;
}

//-------------------------------------------------------------------------------
void FixedCamera::SetTarget(TEntity* target)
{
	m_target = target;
}
