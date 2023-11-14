#include "TLocator.h"
#include "TInputInterface.h"
#include "TInputMappings.h"
#include "TCamera.h"
#include "FreeCamera.h"

//-------------------------------------------------------------------------------
FreeCamera::FreeCamera(TCamera* camera)
:	TCameraController(camera),
	m_cameraPosition(0,0,0),
	m_cameraPitch(0.f),
	m_cameraYaw(0.f),
	m_speed(10.f),
	m_sensitivity(0.5f)
{
	m_cameraTransform.SetIdentity();
}

//-------------------------------------------------------------------------------
FreeCamera::~FreeCamera()
{

}

//-------------------------------------------------------------------------------
void FreeCamera::Update(float elapsedTime)
{
	m_cameraPitch += TLocator::GetInput()->GetYAmt() * m_sensitivity * elapsedTime;
	m_cameraPitch = TClamp(m_cameraPitch, -1.f, 1.f);

	m_cameraYaw	+= TLocator::GetInput()->GetXAmt() * m_sensitivity * elapsedTime;

	m_cameraTransform.RotateXYZ(TVector3(m_cameraPitch, m_cameraYaw, 0.f));

	TVector3 forward = TVector3(0.f, 0.f, 1.f);
	TVector3 up = TVector3(0.f, 1.f, 0.f);
	TVector3 input(0, 0, 0);

	if (TLocator::GetInput()->IsDown(TINPUT_A)) { input.x = -m_speed * elapsedTime; }
	if (TLocator::GetInput()->IsDown(TINPUT_D)) { input.x = m_speed * elapsedTime; }
	if (TLocator::GetInput()->IsDown(TINPUT_W)) { input.z = m_speed * elapsedTime; }
	if (TLocator::GetInput()->IsDown(TINPUT_S)) { input.z = -m_speed * elapsedTime; }
	if (TLocator::GetInput()->IsDown(TINPUT_E)) { input.y = m_speed * elapsedTime; }
	if (TLocator::GetInput()->IsDown(TINPUT_Q)) { input.y = -m_speed * elapsedTime; }

	if (TLocator::GetInput()->IsDown(TINPUT_LSHIFT)) { input *= 10.f; }

	// transform in local co-ordinate system
	m_cameraTransform.TransformVector(&input);
	m_cameraTransform.TransformVector(&forward);
	m_cameraTransform.TransformVector(&up);

	m_cameraPosition += input;

	TVector3 fromPt = m_cameraPosition - forward;
	TVector3 target = m_cameraPosition + forward;

	m_camera->LookAt(fromPt, target, up);
}

//-------------------------------------------------------------------------------
void FreeCamera::SetPosition(const TVector3 & newPosition)
{
	m_cameraPosition = newPosition;
}

//-------------------------------------------------------------------------------
void FreeCamera::SetSensitivity(float newSens)
{
	m_sensitivity = newSens;
}

//-------------------------------------------------------------------------------
const TVector3& FreeCamera::GetPosition() const
{
	return m_cameraPosition;
}

//-------------------------------------------------------------------------------
float FreeCamera::GetSpeed() const
{
	return m_speed;
}

//-------------------------------------------------------------------------------
void FreeCamera::SetSpeed(float speed)
{
	m_speed = speed;
}