//------------------------------------------------------------------------
template <class T>
T TLerp(const T& a, const T& b, float fraction)
{
	return (T) (a + ((b - a) * fraction));
}

//------------------------------------------------------------------------
template <class T>
T TMin(const T& v1, const T& v2)
{
	return v1 <= v2 ? v1 : v2;
}

//------------------------------------------------------------------------
template <class T>
T TMax(const T& v1, const T& v2)
{
	return v1 > v2 ? v1 : v2;
}

//------------------------------------------------------------------------
template <class T>
T TClamp(const T& value, const T& min, const T& max)
{
	return TMin(TMax(value, min), max);
}

//------------------------------------------------------------------------
template <class T> 
T TSquare(const T& value)
{
	return value * value;
}
