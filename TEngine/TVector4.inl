//-------------------------------------------------------------------------------
inline TVector4::TVector4(float _x, float _y, float _z, float _w)
:	x(_x),
	y(_y),
	z(_z),
	w(_w)
{
}

//-------------------------------------------------------------------------------
inline TVector4::TVector4(const TVector4& v)
:	x(v.x),
	y(v.y),
	z(v.z),
	w(v.w)
{
}

//-------------------------------------------------------------------------------	
inline TVector4& TVector4::operator=(const TVector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

//-------------------------------------------------------------------------------
inline TVector4& TVector4::operator+=(const TVector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

//-------------------------------------------------------------------------------
inline TVector4& TVector4::operator-=(const TVector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

//-------------------------------------------------------------------------------
inline TVector4& TVector4::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

//-------------------------------------------------------------------------------
inline TVector4& TVector4::operator*=(const TVector4& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	return *this;
}
