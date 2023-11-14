#ifndef __TMATRIX_H__
#define __TMATRIX_H__

class TVector3;
class TVector2;
class TVector4;

class TMatrix
{
public:
	static const TMatrix& GetIdentity();

	TMatrix();

	TMatrix(
		float _m00, float _m01, float _m02, float _m03,
		float _m10, float _m11, float _m12, float _m13, 
		float _m20, float _m21, float _m22, float _m23, 
		float _m30, float _m31, float _m32, float _m33 );

	TMatrix(const TMatrix& other);

	TMatrix(const TVector3& xAxis, const TVector3& yAxis, const TVector3& zAxis, const TVector3& trans);

	// Rotation Matrix
	TMatrix(const TVector3& xAxis, const TVector3& yAxis, const TVector3& zAxis); 

	// Translation Matrix
	explicit TMatrix(const TVector3& trans);

	// Rotation around an axis
	TMatrix(const TVector3& axis, float angle);
	TMatrix(const TVector3& axis, float sinAngle, float cosAngle);

	void Set(float _m00, float _m01, float _m02, float _m03,
	         float _m10, float _m11, float _m12, float _m13, 
			 float _m20, float _m21, float _m22, float _m23, 
			 float _m30, float _m31, float _m32, float _m33);

	void SetIdentity();
	void Translate(const TVector3& translation);
	void Translate(float x, float y, float z);
	void SetTranslation(const TVector3& translation);	// does not change 3x3 part
	void Scale(const TVector3& scale);
	void Scale(const float scale);
	void Rotate(const TVector3& axis, float angle);
	void Rotate(const TVector3& axis, float sinAngle, float cosAngle);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void RotateXYZ(const TVector3& angles);
	void RotateZXY(const TVector3& angles);
	void RotateYXZ(const TVector3& angles);
	bool IsIdentity() const;

	void SetLookAtMatrix(const TVector3& pos, const TVector3& target, const TVector3& up);    
	void SetOrthoProjection(float width, float height, float nearPlane = -1.0f, float farPlane = 1.0f);
	void SetPerspectiveProjection(float verticalFovRadians, float aspectRatio, float nearPlane, float farPlane); 

	TVector4& operator[](unsigned int i);
	const TVector4& operator[](unsigned int i) const;
	TVector4& operator[](int i);
	const TVector4& operator[](int i) const;

	const TVector3& GetRight() const;                                                     
	const TVector3& GetUp() const;
	const TVector3& GetAt() const;
	const TVector3& GetPos() const;

	void SetRight(const TVector3& v);
	void SetUp(const TVector3& v);
	void SetAt(const TVector3& v);
	void SetPos(const TVector3& v);

	__forceinline TMatrix& operator=(const TMatrix& other);
	__forceinline TMatrix operator*(const TMatrix& other) const;
	TVector2 operator*(const TVector2& v) const;
	TVector3 operator*(const TVector3& v) const;
	bool operator==(const TMatrix& other) const;
	bool operator!=(const TMatrix& other) const;

	__forceinline void FastMultiplyNoW(const TMatrix& m1, const TMatrix& m2);

	void Invert();
	void Invert(const TMatrix& other);
	void FastInvert();
	void FastInvert(const TMatrix& other);

	inline void TransformVector(TVector3* vector) const;
	__forceinline void TransformVector(const TVector3* inVector, TVector3* outVector) const;
	inline void RotateVector(TVector3* vector) const;
	inline void RotateVector(const TVector3* inVector, TVector3* outVector) const;

	TVector3 GetRotation() const;
	TVector3 GetScale() const;
	float GetDeterminant(const TMatrix& in);

	void Transpose3x3();
	void Transpose3x3(const TMatrix& other);
	void Transpose();
	void Transpose(const TMatrix& other);

	bool IsOrthoNormal() const;
	void OrthoNormalize();

	const char *GetStr() const; 
	void Lerp(const TMatrix& in, float weight);

	float m[4][4];
};

// decided to make some of these static to prevent re-declaring them in game code during rendering
extern TMatrix g_matWorld;
extern TMatrix g_matScale; 
extern TMatrix g_matRotate;
extern TMatrix g_matTranslate;

#include "TMatrix.inl"

#endif
