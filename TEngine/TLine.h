#ifndef __TLINE_H__
#define __TLINE_H__

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

class TLine
{
public:
	TLine();
	TLine(const TLine& line);
	TLine(const TVector3& p0, const TVector3& p1);
	TLine& operator=(const TLine& line);

	const TVector3& GetP0() const;
	const TVector3& GetP1() const;
	void SetP0(const TVector3& p);
	void SetP1(const TVector3& p);

	float		GetDistanceToPoint(const TVector3& p) const;
	TVector3	GetPointOnLineClosestTo(const TVector3& p) const;

	TVector3 m_p0;
	TVector3 m_p1;
};

#include "TLine.inl"

#endif
