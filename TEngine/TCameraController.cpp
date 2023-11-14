#include "TCamera.h"
#include "TCameraController.h"

//-------------------------------------------------------------------------------
TCameraController::TCameraController(TCamera* camera)
{
	m_camera = camera;
}

//-------------------------------------------------------------------------------
TCameraController::~TCameraController()
{

}

//-------------------------------------------------------------------------------
const TCamera* TCameraController::GetCamera() const
{
	return m_camera;
}