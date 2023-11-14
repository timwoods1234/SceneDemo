//-------------------------------------------------------------------------------
inline TSphere::TSphere( const TSphere& s )
{
	*this = s;
}

//-------------------------------------------------------------------------------
inline TSphere::TSphere( const TVector3& cen, float rad )
: m_centre( cen ),
   m_radius( rad )
{
}

//-------------------------------------------------------------------------------
inline TSphere& TSphere::operator= ( const TSphere& s )
{
	m_centre = s.m_centre;
	m_radius = s.m_radius;
	return *this;
}

//-------------------------------------------------------------------------------
inline const TVector3& TSphere::GetCentre() const
{
	return m_centre;
}

//-------------------------------------------------------------------------------
inline void TSphere::SetCentre( const TVector3& centre )
{
	m_centre = centre;
}

//-------------------------------------------------------------------------------
inline float TSphere::GetRadius() const
{
	return m_radius;
}

//-------------------------------------------------------------------------------
inline void TSphere::SetRadius( float radius )
{
	m_radius = radius;
}
