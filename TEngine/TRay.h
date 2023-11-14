#ifndef __TRAY_H__
#define __TRAY_H__

class TRay
{
public:
	TRay();
	TRay(const TRay& r);
	TRay( const TVector3& origin, const TVector3& direction);
	TRay& operator=(const TRay& r);

	const TVector3& GetOrigin() const;
	void SetOrigin(const TVector3& origin);

	const TVector3& GetDirection() const;
	void SetDirection(const TVector3& direction);

	TVector3 m_origin;
	TVector3 m_direction;	// unit vector
};

#include "TRay.inl"

#endif
