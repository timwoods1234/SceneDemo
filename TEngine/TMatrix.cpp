#include <stdio.h>

#include "TDirect3D.h"
#include "TMatrix.h"
#include "TVector3.h"
#include "TVector2.h"
#include "TVector4.h"
#include "TMath.h"
#include "TQuaternion.h"

//-------------------------------------------------------------------------------
TMatrix g_matWorld;
TMatrix g_matScale;
TMatrix g_matRotate;
TMatrix g_matTranslate;

//-------------------------------------------------------------------------------
const TMatrix& TMatrix::GetIdentity()
{
	static TMatrix identity(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	return identity;	    
}

//-------------------------------------------------------------------------------
TMatrix::TMatrix()
{
}

//-------------------------------------------------------------------------------
TMatrix::TMatrix(
	float _m00, float _m01, float _m02, float _m03, 
	float _m10, float _m11, float _m12, float _m13, 
	float _m20, float _m21, float _m22, float _m23, 
	float _m30, float _m31, float _m32, float _m33)
{
	m[0][0] = _m00;
	m[0][1] = _m01;
	m[0][2] = _m02;
	m[0][3] = _m03;

	m[1][0] = _m10;
	m[1][1] = _m11;
	m[1][2] = _m12;
	m[1][3] = _m13;

	m[2][0] = _m20;
	m[2][1] = _m21;
	m[2][2] = _m22;
	m[2][3] = _m23;

	m[3][0] = _m30;
	m[3][1] = _m31;
	m[3][2] = _m32;
	m[3][3] = _m33;
}

//-------------------------------------------------------------------------------
TMatrix::TMatrix(const TMatrix& other)
{
	m[0][0] = other.m[0][0];
	m[0][1] = other.m[0][1];
	m[0][2] = other.m[0][2];
	m[0][3] = other.m[0][3];

	m[1][0] = other.m[1][0];
	m[1][1] = other.m[1][1];
	m[1][2] = other.m[1][2];
	m[1][3] = other.m[1][3];

	m[2][0] = other.m[2][0];
	m[2][1] = other.m[2][1];
	m[2][2] = other.m[2][2];
	m[2][3] = other.m[2][3];

	m[3][0] = other.m[3][0];
	m[3][1] = other.m[3][1];
	m[3][2] = other.m[3][2];
	m[3][3] = other.m[3][3];
}

//-------------------------------------------------------------------------------
TMatrix::TMatrix(const TVector3& xAxis, const TVector3& yAxis, const TVector3& zAxis, const TVector3& trans)
{
	Set(xAxis.x,	xAxis.y,	xAxis.z,	0.0f,
		yAxis.x,	yAxis.y,	yAxis.z,	0.0f,
		zAxis.x,	zAxis.y,	zAxis.z,	0.0f,
		trans.x,	trans.y,	trans.z,	1.0f);
}

//-------------------------------------------------------------------------------
TMatrix::TMatrix(const TVector3& xAxis, const TVector3& yAxis, const TVector3& zAxis)
{
	Set(xAxis.x,	xAxis.y,	xAxis.z,	0.0f,
		yAxis.x,	yAxis.y,	yAxis.z,	0.0f,
		zAxis.x,	zAxis.y,	zAxis.z,	0.0f,
		0.0f,		0.0f,		0.0f,		1.0f);
}

//-------------------------------------------------------------------------------
TMatrix::TMatrix(const TVector3& trans)
{
	Translate(trans);
}

//-------------------------------------------------------------------------------
TMatrix::TMatrix(const TVector3& axis, float angle)
{
	Rotate(axis, angle);
}

//-------------------------------------------------------------------------------
TMatrix::TMatrix(const TVector3& axis, float sinAngle, float cosAngle)
{
	Rotate(axis, sinAngle, cosAngle);
}

//-------------------------------------------------------------------------------
void TMatrix::Rotate(const TVector3& axis, float angle)
{
	float sinAngle;
	float cosAngle;
	SinCos(angle, sinAngle, cosAngle);
	Rotate(axis, sinAngle, cosAngle);
}

//-------------------------------------------------------------------------------
void TMatrix::Rotate(const TVector3& axis, float sinAngle, float cosAngle)
{
	const float& x = axis.x;
	const float& y = axis.y;
	const float& z = axis.z;
	float invCosAngle = 1.0f - cosAngle;
	float xyInvCos = (x * y) * invCosAngle;
	float xzInvCos = (x * z) * invCosAngle;
	float yzInvCos = (y * z) * invCosAngle;
	float xSin = x * sinAngle;
	float ySin = y * sinAngle;
	float zSin = z * sinAngle;

	m[0][0] = cosAngle + ((x * x) * invCosAngle);
	m[0][1] = xyInvCos + zSin;
	m[0][2] = xzInvCos - ySin;
	m[0][3] = 0.0f;

	m[1][0] = xyInvCos - zSin;
	m[1][1] = cosAngle + ((y * y) * invCosAngle);
	m[1][2] = yzInvCos + xSin;
	m[1][3] = 0.0f;

	m[2][0] = xzInvCos + ySin;
	m[2][1] = yzInvCos - xSin;
	m[2][2] = cosAngle + ((z * z) * invCosAngle);
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

//-------------------------------------------------------------------------------
void TMatrix::RotateX(float angle)
{
	float sinAngle;
	float cosAngle;
	SinCos(angle, sinAngle, cosAngle);
	Set(1.0f,	0.0f,		0.0f,		0.0f,
		0.0f,	cosAngle,	sinAngle,	0.0f,
		0.0f,	-sinAngle,	cosAngle,	0.0f,
		0.0f,	0.0f,		0.0f,		1.0f);
}

//-------------------------------------------------------------------------------
void TMatrix::RotateY(float angle)
{
	float sinAngle;
	float cosAngle;
	SinCos(angle, sinAngle, cosAngle);
	Set(cosAngle,	0.0f,	-sinAngle,	0.0f,
		0.0f,		1.0f,	0.0f,		0.0f,
		sinAngle,	0.0f,	cosAngle,	0.0f,
		0.0f,		0.0f,	0.0f,		1.0f);
}

//-------------------------------------------------------------------------------
void TMatrix::RotateZ(float angle)
{
	float sinAngle;
	float cosAngle;
	SinCos(angle, sinAngle, cosAngle);
	Set(cosAngle,	sinAngle,	0.0f,	0.0f,
		-sinAngle,	cosAngle,	0.0f,	0.0f,
		0.0f,		0.0f,		1.0f,	0.0f,
		0.0f,		0.0f,		0.0f,	1.0f);    
}

//-------------------------------------------------------------------------------
void TMatrix::Scale(const TVector3& scale)
{
	Set(scale.x,	0.0f,		0.0f,		0.0f,
		0.0f,		scale.y,	0.0f,		0.0f,
		0.0f,		0.0f,		scale.z,	0.0f,
		0.0f,		0.0f,		0.0f,		1.0f);
}

//-------------------------------------------------------------------------------
void TMatrix::Scale(const float scale)
{
	Set(scale,		0.0f,		0.0f,		0.0f,
		0.0f,		scale,		0.0f,		0.0f,
		0.0f,		0.0f,		scale,		0.0f,
		0.0f,		0.0f,		0.0f,		1.0f);
}

//-------------------------------------------------------------------------------
void TMatrix::Translate(const TVector3& trans)
{
	Set(1.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		1.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		1.0f,		0.0f,
		trans.x,	trans.y,	trans.z,	1.0f);
}

//-------------------------------------------------------------------------------
void TMatrix::Translate(float x, float y, float z)
{
	Set(1.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		1.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		1.0f,		0.0f,
		x,			y,			z,			1.0f);
}

//-------------------------------------------------------------------------------
void TMatrix::SetTranslation(const TVector3& translation)
{
	// just set the translation component
	// do not change the 3x3 part
	m[3][0] = translation.x;
	m[3][1] = translation.y;
	m[3][2] = translation.z;
	m[3][3] = 1.f;
}

//-------------------------------------------------------------------------------
void TMatrix::SetLookAtMatrix(const TVector3& pos, const TVector3& target, const TVector3& up)
{
	SetAt(Normalize(target - pos));
	SetRight(Normalize(CrossProduct(up, GetAt())));
	SetUp(CrossProduct(GetAt(), GetRight()));
	SetPos(pos);
}

//-------------------------------------------------------------------------------
void TMatrix::SetOrthoProjection(float width, float height, float nearPlane, float farPlane)
{
	// non-d3d
	SetIdentity();

	m[0][0] = 2.0f / width;
	m[1][1] = 2.0f / height;
	m[2][2] = 1.0f / (nearPlane - farPlane);
	m[3][2] = m[2][2] * nearPlane;

	//D3DXMatrixOrthoLH((D3DXMATRIX*)this, width, height, nearPlane, farPlane );
}

//-------------------------------------------------------------------------------
void TMatrix::SetPerspectiveProjection(float verticalFovRadians, float aspectRatio, float nearPlane, float farPlane)
{
	float nearToFar = nearPlane - farPlane;
	float viewSpaceHeight = 1.0f / tanf(verticalFovRadians * 0.5f);
	float viewSpaceWidth = viewSpaceHeight / aspectRatio;

	float z2 = farPlane / (farPlane - nearPlane);
	float z3 = -1 * nearPlane * farPlane / (farPlane - nearPlane);

	Set(viewSpaceWidth,	0.0f,				0.0f,		0.0f, 
		0.0f,			viewSpaceHeight,	0.0f,		0.0f,
		0.0f,			0.0f,				z2,			1.0f,
		0.0f,			0.0f,				z3,			0.0f);

	//D3DXMatrixPerspectiveFovLH((D3DXMATRIX*)this, verticalFovRadians, aspectRatio, nearPlane, farPlane);
}

//-------------------------------------------------------------------------------
bool TMatrix::IsIdentity() const
{
	return 
		FLT_EQ(m[0][0], 1.0f) &&
		FLT_EQ(m[1][1], 1.0f) &&
		FLT_EQ(m[2][2], 1.0f) &&
		FLT_EQ(m[3][3], 1.0f) &&
		FLT_EQ(m[0][1], 0.0f) &&
		FLT_EQ(m[0][2], 0.0f) &&
		FLT_EQ(m[0][3], 0.0f) &&
		FLT_EQ(m[1][0], 0.0f) &&
		FLT_EQ(m[1][2], 0.0f) &&
		FLT_EQ(m[1][3], 0.0f) &&
		FLT_EQ(m[2][0], 0.0f) &&
		FLT_EQ(m[2][1], 0.0f) &&
		FLT_EQ(m[2][3], 0.0f) &&
		FLT_EQ(m[3][0], 0.0f) &&
		FLT_EQ(m[3][1], 0.0f) &&
		FLT_EQ(m[3][2], 0.0f);
}

//-------------------------------------------------------------------------------
void TMatrix::Set(float _m00, float _m01, float _m02, float _m03,
			  float _m10, float _m11, float _m12, float _m13, 
			  float _m20, float _m21, float _m22, float _m23, 
			  float _m30, float _m31, float _m32, float _m33)
{
	m[0][0] = _m00;
	m[0][1] = _m01;
	m[0][2] = _m02;
	m[0][3] = _m03;

	m[1][0] = _m10;
	m[1][1] = _m11;
	m[1][2] = _m12;
	m[1][3] = _m13;

	m[2][0] = _m20;
	m[2][1] = _m21;
	m[2][2] = _m22;
	m[2][3] = _m23;

	m[3][0] = _m30;
	m[3][1] = _m31;
	m[3][2] = _m32;
	m[3][3] = _m33;
}

//-------------------------------------------------------------------------------
void TMatrix::SetIdentity()
{
	Set(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

//-------------------------------------------------------------------------------
const TVector3& TMatrix::GetRight() const
{
	return (const TVector3&) m[0];
}

//-------------------------------------------------------------------------------
const TVector3& TMatrix::GetUp() const
{
	return (const TVector3&) m[1];
}

//-------------------------------------------------------------------------------
const TVector3& TMatrix::GetAt() const
{
	return (const TVector3&) m[2];
}

//-------------------------------------------------------------------------------
const TVector3& TMatrix::GetPos() const
{
	return (const TVector3&) m[3];
}

//-------------------------------------------------------------------------------
void TMatrix::SetRight(const TVector3 &v)
{
	(TVector3&) m[0] = v;
	m[0][3] = 0.0f;
}

//-------------------------------------------------------------------------------
void TMatrix::SetUp(const TVector3 &v)
{
	(TVector3&) m[1] = v;
	m[1][3] = 0.0f;
}

//-------------------------------------------------------------------------------
void TMatrix::SetAt(const TVector3 &v)
{
	(TVector3&) m[2] = v;
	m[2][3] = 0.0f;
}

//-------------------------------------------------------------------------------
void TMatrix::SetPos(const TVector3 &v)
{
	(TVector3&) m[3] = v;
	m[3][3] = 1.0f;
}

//-------------------------------------------------------------------------------
TVector2 TMatrix::operator*(const TVector2& v) const
{
	return TVector2((v.x * m[0][0]) + (v.y * m[1][0]) + m[2][0],
		(v.x * m[0][1]) + (v.y * m[1][1]) + m[2][1]);
}

//-------------------------------------------------------------------------------
TVector3 TMatrix::operator*(const TVector3 &v) const
{
	return TVector3(
		(v.x * m[0][0]) + (v.y * m[1][0]) + (v.z * m[2][0]) + m[3][0],
		(v.x * m[0][1]) + (v.y * m[1][1]) + (v.z * m[2][1]) + m[3][1],
		(v.x * m[0][2]) + (v.y * m[1][2]) + (v.z * m[2][2]) + m[3][2]);
}

//-------------------------------------------------------------------------------
bool TMatrix::operator==(const TMatrix& other) const
{
	return 
		FLT_EQ(m[0][0], other[0][0]) &&
		FLT_EQ(m[0][1], other[0][1]) &&
		FLT_EQ(m[0][2], other[0][2]) &&
		FLT_EQ(m[0][3], other[0][3]) &&
		FLT_EQ(m[1][0], other[1][0]) &&
		FLT_EQ(m[1][1], other[1][1]) &&
		FLT_EQ(m[1][2], other[1][2]) &&
		FLT_EQ(m[1][3], other[1][3]) &&
		FLT_EQ(m[2][0], other[2][0]) &&
		FLT_EQ(m[2][1], other[2][1]) &&
		FLT_EQ(m[2][2], other[2][2]) &&
		FLT_EQ(m[2][3], other[2][3]) &&
		FLT_EQ(m[3][0], other[3][0]) &&
		FLT_EQ(m[3][1], other[3][1]) &&
		FLT_EQ(m[3][2], other[3][2]) &&
		FLT_EQ(m[3][3], other[3][3]);
}

//-------------------------------------------------------------------------------
bool TMatrix::operator!=(const TMatrix& other) const
{
	return !operator==(other);
}

//-------------------------------------------------------------------------------
void TMatrix::FastInvert()
{
	TMatrix tmp = *this;
	Transpose3x3(tmp);
	m[3][0] = -DotProduct(tmp[0], tmp[3]);
	m[3][1] = -DotProduct(tmp[1], tmp[3]);
	m[3][2] = -DotProduct(tmp[2], tmp[3]);
	m[3][3] = 1.0f;
}

//-------------------------------------------------------------------------------
void TMatrix::FastInvert(const TMatrix& in)
{
	Transpose3x3(in);
	m[3][0] = -DotProduct(in[0], in[3]);
	m[3][1] = -DotProduct(in[1], in[3]);
	m[3][2] = -DotProduct(in[2], in[3]);
	m[3][3] = 1.0f;
}

//-------------------------------------------------------------------------------
TVector4& TMatrix::operator[](unsigned int i)
{
	return (TVector4&) m[i];
}                                                    

//-------------------------------------------------------------------------------
const TVector4& TMatrix::operator[](unsigned int i) const
{
	return (const TVector4&) m[i];
}

//-------------------------------------------------------------------------------
TVector4& TMatrix::operator[](int i)
{
	return (TVector4&) m[i];
}                                                    

//-------------------------------------------------------------------------------
const TVector4& TMatrix::operator[](int i) const
{
	return (const TVector4&) m[i];
}

//-------------------------------------------------------------------------------
void TMatrix::Invert()
{
	D3DXMatrixInverse((D3DXMATRIX*) this, NULL, (D3DXMATRIX*) this);
}

//-------------------------------------------------------------------------------
void TMatrix::Invert(const TMatrix& other)
{
	D3DXMatrixInverse((D3DXMATRIX*) this, NULL, (D3DXMATRIX*) &other);
}

//-------------------------------------------------------------------------------
TVector3 TMatrix::GetRotation() const
{
    TVector3 v[3];
    D3DXMATRIX temp;
    TVector3 a;
	D3DXVECTOR4 output;

    // create a matrix that will be used to rotate back the vertices
    D3DXMatrixIdentity(&temp);

	v[0] = GetRight();
	v[1] = GetUp();
	v[2] = GetAt();

    // calc angle on the "at" vector on the X/Z plane
	TVector3 rotation;
    rotation.y = atan2f(v[2].x,v[2].z);

    // rotate back along the Y axis
	a.x = 0.f;
	a.y = 1.f;
	a.z = 0.f;

    D3DXMatrixRotationY(&temp, -rotation.y);
    
	D3DXVec3Transform(&output, (D3DXVECTOR3*)(&v[0]), &temp);
	v[0].Set(output.x, output.y, output.z);
	D3DXVec3Transform(&output, (D3DXVECTOR3*)(&v[1]), &temp);
	v[1].Set(output.x, output.y, output.z);
	D3DXVec3Transform(&output, (D3DXVECTOR3*)(&v[2]), &temp);
	v[2].Set(output.x, output.y, output.z);

    // calc tilt on the "at" vector on the Z/Y plane
    rotation.x = atan2f(-v[2].y,v[2].z);

    // rotate back along the Z axis
	a.x = 1.f;
	a.y = 0.f;
	a.z = 0.f;

    D3DXMatrixRotationX(&temp, -rotation.x);

	D3DXVec3Transform(&output, (D3DXVECTOR3*)(&v[0]), &temp);
	v[0].Set(output.x, output.y, output.z);
	D3DXVec3Transform(&output, (D3DXVECTOR3*)(&v[1]), &temp);
	v[1].Set(output.x, output.y, output.z);
	D3DXVec3Transform(&output, (D3DXVECTOR3*)(&v[2]), &temp);
	v[2].Set(output.x, output.y, output.z);

    // calc roll on the "right" vector on the X/Y plane
    rotation.z = atan2f(v[0].y,v[0].x);

	return rotation;
/*
	// Non-d3d
	TVector3 v[3];
	TMatrix temp;

	temp.SetIdentity();

	v[0] = GetRight();
	v[1] = GetUp();
	v[2] = GetAt();

	// calc angle on the "at" vector on the X/Z plane
	TVector3 rotation;
	rotation.y = atan2f(v[2].x,v[2].z);

	temp.RotateY(-rotation.y);

	temp.TransformVector(&v[0], &v[0]);
	temp.TransformVector(&v[1], &v[1]);
	temp.TransformVector(&v[2], &v[2]);

	// calc tilt on the "at" vector on the Z/Y plane
	rotation.x = atan2f(-v[2].y,v[2].z);

	temp.RotateX(-rotation.x);

	temp.TransformVector(&v[0], &v[0]);
	temp.TransformVector(&v[1], &v[1]);
	temp.TransformVector(&v[2], &v[2]);

	// calc roll on the "right" vector on the X/Y plane
	rotation.z = atan2f(v[0].y,v[0].x);
	return rotation;
*/
}

//-------------------------------------------------------------------------------
void TMatrix::Transpose()
{
	TMatrix tmp = *this;
	Transpose(tmp);
}

//-------------------------------------------------------------------------------
void TMatrix::Transpose(const TMatrix& other)
{
	m[0][0] = other[0][0];
	m[0][1] = other[1][0];
	m[0][2] = other[2][0];
	m[0][3] = other[3][0];

	m[1][0] = other[0][1];
	m[1][1] = other[1][1];
	m[1][2] = other[2][1];
	m[1][3] = other[3][1];

	m[2][0] = other[0][2];
	m[2][1] = other[1][2];
	m[2][2] = other[2][2];
	m[2][3] = other[3][2];

	m[3][0] = other[0][3];
	m[3][1] = other[1][3];
	m[3][2] = other[2][3];
	m[3][3] = other[3][3];
}

//-------------------------------------------------------------------------------
bool TMatrix::IsOrthoNormal() const
{
	float a = DotProduct(GetAt(), GetRight());
	float b = DotProduct(GetAt(), GetUp());
	float c = DotProduct(GetUp(), GetRight());

	const float accept = 0.00001f;

	if(fabsf(a) > accept)
		return false;
	if(fabsf(b) > accept)
		return false;
	if(fabsf(c) > accept)
		return false;
	return true;
}

//-------------------------------------------------------------------------------
void TMatrix::OrthoNormalize()
{
	SetUp(Normalize(GetUp()));
	SetAt(Normalize(GetAt()));	
	SetRight(CrossProduct(GetUp(), GetAt()));	
	SetAt(CrossProduct(GetRight(), GetUp()));
}

//-------------------------------------------------------------------------------
void TMatrix::Transpose3x3()
{
	TVector3 xAxis = GetRight();
	TVector3 yAxis = GetUp();
	TVector3 zAxis = GetAt();

	m[0][0] = xAxis.x;
	m[0][1] = yAxis.x;
	m[0][2] = zAxis.x;
	m[1][0] = xAxis.y;
	m[1][1] = yAxis.y;
	m[1][2] = zAxis.y;
	m[2][0] = xAxis.z;
	m[2][1] = yAxis.z;
	m[2][2] = zAxis.z;
}

//-------------------------------------------------------------------------------
void TMatrix::Transpose3x3(const TMatrix& other)
{
	m[0][0] = other[0][0];
	m[0][1] = other[1][0];
	m[0][2] = other[2][0];
	m[0][3] = 0.0f;

	m[1][0] = other[0][1];
	m[1][1] = other[1][1];
	m[1][2] = other[2][1];
	m[1][3] = 0.0f;

	m[2][0] = other[0][2];
	m[2][1] = other[1][2];
	m[2][2] = other[2][2];
	m[2][3] = 0.0f;
}

//-------------------------------------------------------------------------------
const char* TMatrix::GetStr() const
{
	static char buf[1024];
	sprintf_s(buf, 1024, "[%f, %f, %f, %f]\n[%f, %f, %f, %f]\n[%f, %f, %f, %f]\n[%f, %f, %f, %f]",
		m[0][0], m[0][1], m[0][2], m[0][3], 
		m[1][0], m[1][1], m[1][2], m[1][3], 
		m[2][0], m[2][1], m[2][2], m[2][3], 
		m[3][0], m[3][1], m[3][2], m[3][3]);
	return buf;
}

//-------------------------------------------------------------------------------
void TMatrix::RotateZXY(const TVector3& angles)
{
	TMatrix x, y, z;

	if (angles.x != 0.f) { x.RotateX(angles.x); }
	else				 { x.SetIdentity(); }

	if (angles.y != 0.f) { y.RotateY(angles.y); }
	else				 { y.SetIdentity(); }

	if (angles.z != 0.f) { z.RotateZ(angles.z); }
	else				 { z.SetIdentity(); }

	*this = z * (x * y);
}

//-------------------------------------------------------------------------------
void TMatrix::RotateYXZ(const TVector3& angles)
{
	TMatrix x, y, z;

	if (angles.x != 0.f) { x.RotateX(angles.x); }
	else				 { x.SetIdentity(); }

	if (angles.y != 0.f) { y.RotateY(angles.y); }
	else				 { y.SetIdentity(); }

	if (angles.z != 0.f) { z.RotateZ(angles.z); }
	else				 { z.SetIdentity(); }

	*this = y * (x * z);
}

//-------------------------------------------------------------------------------
void TMatrix::RotateXYZ(const TVector3& angles)
{
	TMatrix x, y, z;

	if (angles.x != 0.f) { x.RotateX(angles.x); }
	else				 { x.SetIdentity(); }

	if (angles.y != 0.f) { y.RotateY(angles.y); }
	else				 { y.SetIdentity(); }

	if (angles.z != 0.f) { z.RotateZ(angles.z); }
	else				 { z.SetIdentity(); }

	*this = x * (y * z);
}

//-------------------------------------------------------------------------------
float TMatrix::GetDeterminant(const TMatrix& in)
{
	return 0
		+ in.m[0][0] *
		( 0 + in.m[1][1] * ( in.m[2][2] * in.m[3][3] - in.m[3][2] * in.m[2][3] )
		- in.m[1][2] * ( in.m[2][1] * in.m[3][3] - in.m[3][1] * in.m[2][3] )
		+ in.m[1][3] * ( in.m[2][1] * in.m[3][2] - in.m[3][1] * in.m[2][2] )
		)
		- in.m[0][1] *
		( 0 + in.m[1][0] * ( in.m[2][2] * in.m[3][3] - in.m[3][2] * in.m[2][3] )
		- in.m[1][2] * ( in.m[2][0] * in.m[3][3] - in.m[3][0] * in.m[2][3] )
		+ in.m[1][3] * ( in.m[2][0] * in.m[3][2] - in.m[3][0] * in.m[2][2] )
		)
		+ in.m[0][2] *
		( 0 + in.m[1][0] * ( in.m[2][1] * in.m[3][3] - in.m[3][1] * in.m[2][3] )
		- in.m[1][1] * ( in.m[2][0] * in.m[3][3] - in.m[3][0] * in.m[2][3] )
		+ in.m[1][3] * ( in.m[2][0] * in.m[3][1] - in.m[3][0] * in.m[2][1] )
		)
		- in.m[0][3] *
		( 0 + in.m[1][0] * ( in.m[2][1] * in.m[3][2] - in.m[3][1] * in.m[2][2] )
		- in.m[1][1] * ( in.m[2][0] * in.m[3][2] - in.m[3][0] * in.m[2][2] )
		+ in.m[1][2] * ( in.m[2][0] * in.m[3][1] - in.m[3][0] * in.m[2][1] )
		);
}

//-------------------------------------------------------------------------------
TVector3 TMatrix::GetScale() const
{
	TQuaternion quat;

	quat.FromRotationMatrix(*this);

	TMatrix rotation;
	quat.ToRotationMatrix(rotation);
	rotation.Invert();
	rotation = rotation * *this;

	return TVector3(rotation.m[0][0], rotation.m[1][1], rotation.m[2][2]);
}

//-------------------------------------------------------------------------------
void TMatrix::Lerp(const TMatrix& in, float weight)
{
	if (FLT_EQ(weight, 0.0f))
	{
		return;
	}

	TQuaternion rot1;
	TQuaternion rot2;

	TVector3 scale = GetScale();
	TVector3 otherScale = in.GetScale();

	TVector3 resultScale = ((otherScale - scale) * weight) + scale;

	TVector3 position = ((in.GetPos() - GetPos()) * weight) + GetPos();

	rot1.FromRotationMatrix(*this);
	rot2.FromRotationMatrix(in);

	TQuaternion result = TQuaternion::Slerp(weight, rot1, rot2);
	result.ToRotationMatrix(*this);

	TMatrix scaleMatrix;
	scaleMatrix.Scale(resultScale);

	*this = scaleMatrix * (*this);

	SetPos(position);
}
