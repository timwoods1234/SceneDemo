#ifndef __TSPHERE_H__
#define __TSPHERE_H__

class TMatrix;
class TAABB;
class TRay;

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

class TSphere
{
public:
	TSphere();
	TSphere( const TSphere& s );
	TSphere( const TVector3& cen, float rad );
	TSphere& operator= ( const TSphere& s );

	const TVector3& GetCentre() const;
	void SetCentre( const TVector3& centre );
	float GetRadius() const;
	void SetRadius( float radius );

	void Transform( const TMatrix& m );
	void GetBoundingTAABB( TAABB& aabb ) const;
	void FromAABB( const TAABB& aabb );
	bool Contains( const TVector3& p ) const;

	void AddSphere(const TSphere& sphere);

protected:
	TVector3	m_centre;		/// the center of the sphere
	float		m_radius;		/// the radius of the sphere
};

#include "TSphere.inl"

#endif
