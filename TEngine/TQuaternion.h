#ifndef __TQUATERNION_H__
#define __TQUATERNION_H__

#ifndef __TMATRIX_H__
#include "TMatrix.h"
#endif

class TQuaternion
{
public:
	TQuaternion();
	TQuaternion(float w, float x, float y, float z);
	TQuaternion(const TQuaternion& q);
	// TODO: matrix ctor

	float GetW() const;
	float GetX() const;
	float GetY() const;
	float GetZ() const;
	void SetW(float w);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);

    void FromRotationMatrix(const TMatrix& rot);
    void ToRotationMatrix(TMatrix& rot) const;

    void FromAngleAxis(const float& angle, const TVector3& axis);
    void ToAngleAxis(float& angle, TVector3& axis) const;

    void FromAxes(const TVector3 axis[3]);
	void FromEulerAnglesXYZ(const TVector3& angles);
	void FromEulerAnglesYXZ(const TVector3& angles);
	void FromEulerAnglesZXY(const TVector3& angles);

    void ToAxes(TVector3 axis[3]) const;
	void Normalize();

	TQuaternion& operator=(const TQuaternion& q);
	TQuaternion operator+(const TQuaternion& q) const;
	TQuaternion operator-(const TQuaternion& q) const;
	TQuaternion operator-() const;
	TQuaternion operator*(const TQuaternion& q) const;
	TQuaternion operator*(float c) const;
	TVector3 operator*(const TVector3& v ) const;
	bool operator==(const TQuaternion& q) const;
	bool operator!=(const TQuaternion& q) const;

    float GetSquaredLength() const;
	float GetLength() const;
	TQuaternion Inverse() const;
	TQuaternion UnitInverse() const;

	TQuaternion Exp() const;
	TQuaternion Log() const;

    static TQuaternion	Slerp(float t, const TQuaternion& p, const TQuaternion& q);

	static const TQuaternion IDENTITY;
	static const TQuaternion ZERO;

	float w;
	float x;
	float y;
	float z;
};

inline float DotProduct(const TQuaternion& p, const TQuaternion& q);

#include "TQuaternion.inl"

#endif
