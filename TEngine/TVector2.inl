//-------------------------------------------------------------------------------
inline TVector2::TVector2(float _x, float _y)
:	x(_x),
	y(_y)
{
}

//-------------------------------------------------------------------------------
inline TVector2::TVector2(const TVector2& v)
:	x(v.x),
	y(v.y)
{
}

//-------------------------------------------------------------------------------	
inline TVector2& TVector2::operator=(const TVector2& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

//-------------------------------------------------------------------------------
inline TVector2& TVector2::operator+=(const TVector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

//-------------------------------------------------------------------------------
inline TVector2& TVector2::operator-=(const TVector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

//-------------------------------------------------------------------------------
inline TVector2& TVector2::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this;
}

//-------------------------------------------------------------------------------
inline TVector2& TVector2::operator*=(const TVector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}
