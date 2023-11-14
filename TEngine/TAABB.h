#ifndef __TAABB_H__
#define __TAABB_H__

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

class TMatrix;
class TRay;

class TAABB
{
public:
	TAABB();
	TAABB( const TAABB& TAABB );
	TAABB( const TVector3& min, const TVector3& max );
	TAABB& operator = ( const TAABB& TAABB );

	const TVector3&	GetMin() const;
	TVector3& GetMin();
	const TVector3&	GetMax() const;
	TVector3& GetMax();
	TVector3 GetCentre() const;
	TVector3 GetExtent() const;
	void GetSize(TVector3& size) const;
	TVector3 GetCorner(unsigned int i) const;

	void SetMin( const TVector3& min );
	void SetMin( float x, float y, float z );
	void SetMax( const TVector3& max );
	void SetMax( float x, float y, float z );
	void SetupMinMax( const TVector3& p0, const TVector3& p1 );

	void Transform( const TMatrix& M );
	bool IsInside( const TVector3& p ) const;
	TVector3 GetClosestPoint(const TVector3& p) const;

	void Clear();
	void AddPoint(const TVector3& point);

protected:
	TVector3	m_min;
	TVector3	m_max;
};

#include "TAABB.inl"

#endif
