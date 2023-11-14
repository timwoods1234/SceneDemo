#include "TLine.h"

//-------------------------------------------------------------------------------
float TLine::GetDistanceToPoint(const TVector3& p) const
{
	TVector3 v = m_p1 - m_p0;
	TVector3 w = p - m_p0;

	float c1 = DotProduct( w, v );
	if ( c1 <= 0.0f )
	{
		return Distance( p, m_p0 );
	}

	float c2 = DotProduct( v, v );
	if( c2 <= c1 )
	{
		return Distance( p, m_p1 );
	}

	float b = c1 / c2;

	TVector3 Pb = m_p0 + v*b;
	return Distance( p, Pb );
}

//-------------------------------------------------------------------------------
TVector3 TLine::GetPointOnLineClosestTo( const TVector3& p ) const
{
	TVector3 v = m_p1 - m_p0;
	TVector3 w = p - m_p0;

	float c1 = DotProduct( w, v );
	if( c1 <= 0.0f )
		return m_p0;

	float c2 = DotProduct( v, v );
	if( c2 <= c1 )
		return m_p1;

	float b = c1 / c2;

	TVector3 Pb = m_p0 + v*b;
	return Pb;
}