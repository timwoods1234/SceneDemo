#include "TPlane.h"
#include "TMatrix.h"

//-------------------------------------------------------------------------------
void TPlane::Transform(const TMatrix& transform)
{
	TVector3 normal = m_normal;
	float constant = m_constant;

	m_normal.x = transform.m[0][0] * normal.x + transform.m[1][0] * normal.y + transform.m[2][0] * normal.z + + transform.m[3][0] * constant;
	m_normal.y = transform.m[0][1] * normal.x + transform.m[1][1] * normal.y + transform.m[2][1] * normal.z + + transform.m[3][1] * constant;
	m_normal.z = transform.m[0][2] * normal.x + transform.m[1][2] * normal.y + transform.m[2][2] * normal.z + + transform.m[3][2] * constant;
	m_constant = transform.m[0][3] * normal.x + transform.m[1][3] * normal.y + transform.m[2][3] * normal.z + + transform.m[3][3] * constant;
}

//-------------------------------------------------------------------------------
float& TPlane::operator[](unsigned int i)
{
	return ((float*)this)[i];
}

//-------------------------------------------------------------------------------
float TPlane::operator[](unsigned int i) const
{
	return ((float*)this)[i];
}