//-------------------------------------------------------------------------------
inline TAABB::TAABB()
{
	Clear();
}

//-------------------------------------------------------------------------------
inline TAABB::TAABB( const TAABB& TAABB )
{
	*this = TAABB;
}

//-------------------------------------------------------------------------------
inline TAABB::TAABB( const TVector3& min, const TVector3& max )
 : m_min( min ),
   m_max( max )
{
}

//-------------------------------------------------------------------------------
inline TAABB& TAABB::operator = ( const TAABB& TAABB )
{
	m_min = TAABB.m_min;
	m_max = TAABB.m_max;
	return *this;
}

//-------------------------------------------------------------------------------
inline const TVector3& TAABB::GetMin() const
{
	return m_min;
}

//-------------------------------------------------------------------------------
inline TVector3& TAABB::GetMin()
{
	return m_min;
}

//-------------------------------------------------------------------------------
inline void TAABB::SetMin( const TVector3& min )
{
	m_min = min;
}

//-------------------------------------------------------------------------------
inline void TAABB::SetMin( float x, float y, float z )
{
	m_min.x = x;
	m_min.y = y;
	m_min.z = z;
}

//-------------------------------------------------------------------------------
inline const TVector3& TAABB::GetMax() const
{
	return m_max;
}

//-------------------------------------------------------------------------------
inline TVector3& TAABB::GetMax()
{
	return m_max;
}

//-------------------------------------------------------------------------------
inline void TAABB::SetMax( const TVector3& max )
{
	m_max = max;
}

//-------------------------------------------------------------------------------
inline void TAABB::SetupMinMax( const TVector3& p0, const TVector3& p1 )
{
// X
	if( p0.x <= p1.x )
	{
		m_min.x = p0.x;
		m_max.x = p1.x;
	}
	else
	{
		m_min.x = p1.x;
		m_max.x = p0.x;
	}
// Y
	if( p0.y <= p1.y )
	{
		m_min.y = p0.y;
		m_max.y = p1.y;
	}
	else
	{
		m_min.y = p1.y;
		m_max.y = p0.y;
	}
// Z
	if( p0.z <= p1.z )
	{
		m_min.z = p0.z;
		m_max.z = p1.z;
	}
	else
	{
		m_min.z = p1.z;
		m_max.z = p0.z;
	}
}

//-------------------------------------------------------------------------------
inline void TAABB::SetMax( float x, float y, float z )
{
	m_max.x = x;
	m_max.y = y;
	m_max.z = z;
}

//-------------------------------------------------------------------------------
inline TVector3 TAABB::GetCentre() const
{
	TVector3 result = m_max + m_min;
	result *= 0.5f;
	return result;
}

//-------------------------------------------------------------------------------
inline TVector3 TAABB::GetExtent() const
{
	TVector3 result = m_max - m_min;
	result *= 0.5f;
	return result;
}

