//-----------------------------------------------------------------------------------------
inline TRay::TRay()
{
}

//-----------------------------------------------------------------------------------------
inline TRay::TRay( const TRay& r )
{
	*this = r;
}

//-----------------------------------------------------------------------------------------
inline TRay::TRay(const TVector3& origin, const TVector3& direction) : 
	m_origin(origin),
	m_direction(direction)
{
}

//-----------------------------------------------------------------------------------------
inline TRay& TRay::operator=(const TRay& r)
{
	SetOrigin(r.GetOrigin());
	SetDirection(r.GetDirection());
	return *this;
}

//-----------------------------------------------------------------------------------------
inline const TVector3& TRay::GetOrigin() const
{
	return m_origin;
}

//-----------------------------------------------------------------------------------------
inline void TRay::SetOrigin(const TVector3& origin)
{
	m_origin = origin;
}

//-----------------------------------------------------------------------------------------
inline const TVector3& TRay::GetDirection() const
{
	return m_direction;
}

//-----------------------------------------------------------------------------------------
inline void TRay::SetDirection(const TVector3& direction)
{
	m_direction = direction;
}