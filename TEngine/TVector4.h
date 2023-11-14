#ifndef __TVECTOR4_H__
#define __TVECTOR4_H__

class TVector4
{
public:
	static const TVector4& Zero();
	static const TVector4& One();

	TVector4();
	inline TVector4(const TVector4& v);
	inline TVector4(float _x, float _y, float _z, float _w);

	inline TVector4& operator=(const TVector4& v);
	inline TVector4& operator+=(const TVector4& v);
	inline TVector4& operator-=(const TVector4& v);
	inline TVector4& operator*=(const TVector4& v);
	inline TVector4& operator*=(float s);
	TVector4& operator/=(float s);
	TVector4 operator+(const TVector4& v) const;
	TVector4 operator-(const TVector4& v) const;
	TVector4 operator*(float s) const;
	TVector4 operator*(const TVector4& v) const;
	TVector4 operator/(float s) const;
	TVector4 operator-() const;
	bool operator==(const TVector4& v) const;
	bool operator!=(const TVector4& v) const;
	float& operator[](unsigned int i);
	float  operator[](unsigned int i) const;
	float& operator[](int i);
	float  operator[](int i) const;

	float GetLength() const;
	float GetSquaredLength() const;

	void Set(float x, float y, float z, float w);
	float Normalize();
	bool IsNormalized() const;

	float x;
	float y;
	float z;
	float w;

	const char* GetStr() const;		// string representation
};

TVector4 Normalize(const TVector4& v);
float DotProduct(const TVector4& a, const TVector4& b);
float Distance(const TVector4& a, const TVector4& b);
float SquaredDistance(const TVector4& a, const TVector4& b);
TVector4 GetRandomVec4(unsigned int* seed, const TVector4& min, const TVector4& max);
TVector4 GetRandomUnitVec4(unsigned int* seed);

#include "TVector4.inl"

#endif
