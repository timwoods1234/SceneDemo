#ifndef __TVECTOR3_H__
#define __TVECTOR3_H__

class TVector3
{
public:
	static const TVector3& Zero();
	static const TVector3& One();

	explicit TVector3();	// no initialization
	inline TVector3(float _x, float _y, float _z);
	inline TVector3(const TVector3& v);

	inline TVector3& operator=(const TVector3& v);
	inline TVector3& operator+=(const TVector3& v);
	inline TVector3& operator-=(const TVector3& v);
	inline TVector3& operator*=(const TVector3& v);
	inline TVector3& operator*=(float s);
	TVector3& operator/=(float s);
	TVector3 operator+(const TVector3& v) const;
	TVector3 operator-(const TVector3& v) const;
	TVector3 operator*(float s) const;
	TVector3 operator*(const TVector3& v) const;
	TVector3 operator/(float s) const;
	TVector3 operator-() const;
	bool operator==(const TVector3& v) const;
	bool operator!=(const TVector3& v) const;
	float& operator[](unsigned int i);
	float  operator[](unsigned int i) const;

	float GetLength() const;
	float GetSquaredLength() const;

	void Set(float x, float y, float z);
	float Normalize();
	bool IsNormalized() const;

	float x;
	float y;
	float z;

	const char* GetStr() const;		// string representation
};

//-------------------------------------------------------------------------------
// Non-member functions
TVector3	CalculateTriangleNormal(const TVector3& a, const TVector3& b, const TVector3& c);
TVector3	Normalize(const TVector3& v);
TVector3	CrossProduct(const TVector3& a, const TVector3& b);
float		DotProduct(const TVector3& a, const TVector3& b);
float		Distance(const TVector3& a, const TVector3& b);
float		SquaredDistance(const TVector3& a, const TVector3& b);
TVector3	GetRandomVec3(unsigned int* seed, const TVector3& min, const TVector3& max);
TVector3	GetRandomUnitVec3(unsigned int* seed);
TVector3	GetPerpVector(const TVector3& v);

#include "TVector3.inl"

#endif
