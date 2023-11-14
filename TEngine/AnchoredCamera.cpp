#include "AnchoredCamera.h"
#include "TCamera.h"
#include "TLocator.h"
#include "TInputMappings.h"
#include "TInputInterface.h"
#include "TEntity.h"

//-------------------------------------------------------------------------------
AnchoredCamera::AnchoredCamera(TCamera* camera)
:	TCameraController(camera),
	m_targetEntity(NULL),
	m_targetPosition(0,0,0),
	m_distance(5.f),
	m_zoomSpeed(20.f),
	m_moveSpeed(1.f),
	m_pitch(0.f),
	m_yaw(0.f),
	m_enableX(true),
	m_enableY(true),
	m_maxDistance(50.f)
{
	m_orientation.SetIdentity();
}

//-------------------------------------------------------------------------------
AnchoredCamera::~AnchoredCamera()
{
}

//-------------------------------------------------------------------------------
void AnchoredCamera::Update(float elapsedTime)
{
	ProcessInput(elapsedTime);

	TVector3 displacement(0.f, 0.f, m_distance);

	TMatrix yaw;
	TMatrix pitch;

	yaw.RotateY(m_yaw);
	pitch.RotateX(m_pitch);

	m_orientation = pitch * yaw;
	m_orientation.RotateVector(&displacement);

	if (m_targetEntity != NULL)
	{
		m_targetPosition = m_targetEntity->GetPosition();
	}

	m_camera->LookAt(displacement, m_targetPosition, TCamera::Up());
}

//-------------------------------------------------------------------------------
void AnchoredCamera::EnableAxis(bool x, bool y)
{
	m_enableX = x;
	m_enableY = y;
}

//-------------------------------------------------------------------------------
float AnchoredCamera::GetMaxDistance() const
{
	return m_maxDistance;
}

//-------------------------------------------------------------------------------
void AnchoredCamera::SetMaxDistance(float maxDistance)
{
	m_maxDistance = maxDistance;
}

//-------------------------------------------------------------------------------
void AnchoredCamera::SetZoomSpeed(float speed)
{
	m_zoomSpeed = speed;
}

//-------------------------------------------------------------------------------
float AnchoredCamera::GetZoomSpeed() const
{
	return m_zoomSpeed;
}

//-------------------------------------------------------------------------------
void AnchoredCamera::ProcessInput(float elapsedTime)
{
	float speedModifier = 1.f;

	if (TLocator::GetInput()->IsDown(TINPUT_LSHIFT))
	{
		speedModifier = 10.f;
	}

	if (TLocator::GetInput()->IsDown(TINPUT_UP))
	{
		m_distance -= elapsedTime * m_zoomSpeed * speedModifier;
	}
	else if (TLocator::GetInput()->IsDown(TINPUT_DOWN))
	{
		m_distance += elapsedTime * m_zoomSpeed * speedModifier;
	}

	m_distance = TClamp(m_distance, 0.1f, m_maxDistance);

	if (m_enableX && TLocator::GetInput()->GetXAmt() != 0)
	{
		m_yaw -= elapsedTime * m_moveSpeed * TLocator::GetInput()->GetXAmt();
	}

	if (m_enableY && TLocator::GetInput()->GetYAmt() != 0)
	{
		m_pitch += elapsedTime * m_moveSpeed * TLocator::GetInput()->GetYAmt();

		m_pitch = TClamp(m_pitch, -1.1f, 1.1f);
	}
}

//-------------------------------------------------------------------------------
void AnchoredCamera::SetTarget(TEntity* entity)
{
	m_targetEntity = entity;
}
//-------------------------------------------------------------------------------
void AnchoredCamera::SetTarget(const TVector3& targetPosition)
{
	m_targetPosition = targetPosition;
}

//-------------------------------------------------------------------------------
const TVector3& AnchoredCamera::GetTarget() const
{
	return m_targetPosition;
}