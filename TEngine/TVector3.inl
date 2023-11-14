//-------------------------------------------------------------------------------
inline TVector3::TVector3(float _x, float _y, float _z)
:	x(_x),
	y(_y),
	z(_z)
{
}

//-------------------------------------------------------------------------------
inline TVector3::TVector3(const TVector3& v)
:	x(v.x),
	y(v.y),
	z(v.z)
{
}

//-------------------------------------------------------------------------------	
inline TVector3& TVector3::operator=(const TVector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

//-------------------------------------------------------------------------------
inline TVector3& TVector3::operator+=(const TVector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

//-------------------------------------------------------------------------------
inline TVector3& TVector3::operator-=(const TVector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

//-------------------------------------------------------------------------------
inline TVector3& TVector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

//-------------------------------------------------------------------------------
inline TVector3& TVector3::operator*=(const TVector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}
