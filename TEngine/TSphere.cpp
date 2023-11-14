#include "TSphere.h"
#include "TMatrix.h"
#include "TAABB.h"
#include "TMath.h"
#include "Collision.h"

//-------------------------------------------------------------------------------
TSphere::TSphere()
{
}

//-------------------------------------------------------------------------------
void TSphere::Transform( const TMatrix& m )
{
	m.TransformVector(&m_centre, &m_centre);
}

//-------------------------------------------------------------------------------
void TSphere::GetBoundingTAABB( TAABB& aabb ) const
{
	aabb.SetMin( m_centre.x - m_radius, m_centre.y - m_radius, m_centre.z - m_radius );
	aabb.SetMax( m_centre.x + m_radius, m_centre.y + m_radius, m_centre.z + m_radius );
}

//-------------------------------------------------------------------------------
void TSphere::FromAABB( const TAABB& aabb )
{
    m_centre = (aabb.GetMin() + aabb.GetMax()) * 0.5f;
    float radius1 = (aabb.GetMin() - m_centre).GetSquaredLength();
    float radius2 = (aabb.GetMax() - m_centre).GetSquaredLength();
	m_radius = sqrtf(TMax(radius1, radius2));
}

//-------------------------------------------------------------------------------
bool TSphere::Contains( const TVector3& p ) const
{
	TVector3 dist(m_centre);
	dist -= p;

	if (m_radius * m_radius >= dist.GetSquaredLength())
	{
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------
void TSphere::AddSphere(const TSphere& sphere)
{
	/// Work out the sphere that fit both these spheres.
	TVector3 difference = m_centre - sphere.m_centre;

	float distance = difference.GetLength();

	if (m_radius > sphere.m_radius)
	{
		if (distance + sphere.m_radius > m_radius)
		{
			float over = distance + sphere.m_radius - m_radius;

			if (distance > over / 2)
			{
				m_radius += over / 2;
				difference = -difference;
				difference.Normalize();
				difference *= over / 2;
				m_centre += difference;
			}
			else
			{
				m_radius += over;
			}
		}
	}
	else
	{
		if (distance + m_radius > sphere.m_radius)
		{
			float over = distance + m_radius - sphere.m_radius;

			m_centre = sphere.m_centre;
			m_radius = sphere.m_radius;

			if (distance > over / 2)
			{
				m_radius += over / 2;
				difference.Normalize();
				difference *= over / 2;
				m_centre += difference;
			}
			else
			{
				m_radius += over;
			}
		}
	}
}

