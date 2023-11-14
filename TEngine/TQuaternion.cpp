#include "TQuaternion.h"
#include "TMath.h"
#include "TVector4.h"

//-------------------------------------------------------------------------------
const TQuaternion	TQuaternion::IDENTITY( 1.0f, 0.0f, 0.0f, 0.0f );
const TQuaternion	TQuaternion::ZERO( 0.0f, 0.0f, 0.0f, 0.0f );

//-------------------------------------------------------------------------------
void TQuaternion::FromRotationMatrix(const TMatrix& rot)
{
    float trace = rot.m[0][0] + rot.m[1][1] + rot.m[2][2];
    float root;

    if ( trace > 0.0 )
    {
        // |w| > 1/2, may as well choose w > 1/2
        root = sqrtf( trace + 1.0f );  // 2w
        w = 0.5f * root;
        root = 0.5f / root;  // 1/(4w)
        x = ( rot.m[2][1]-rot.m[1][2] )*root;
        y = ( rot.m[0][2]-rot.m[2][0] )*root;
        z = ( rot.m[1][0]-rot.m[0][1] )*root;
    }
    else
    {
        // |w| <= 1/2
        static int s_next[3] = { 1, 2, 0 };
        int i = 0;
        if ( rot.m[1][1] > rot.m[0][0] )
            i = 1;
        if ( rot.m[2][2] > rot.m[i][i] )
            i = 2;
        int j = s_next[i];
        int k = s_next[j];

        root = sqrtf( rot.m[i][i] - rot.m[j][j] - rot.m[k][k] + 1.0f );
        float* quat[3] = { &x, &y, &z };
        *quat[i] = 0.5f * root;
        root = 0.5f / root;
        w = ( rot.m[k][j] - rot.m[j][k] ) * root;
        *quat[j] = ( rot.m[j][i] + rot.m[i][j] ) * root;
        *quat[k] = ( rot.m[k][i] + rot.m[i][k] ) * root;
    }
}

//-------------------------------------------------------------------------------
void TQuaternion::ToRotationMatrix(TMatrix& rot) const
{
    float tx  = 2.0f * x;
    float ty  = 2.0f * y;
    float tz  = 2.0f * z;
    float twx = tx * w;
    float twy = ty * w;
    float twz = tz * w;
    float txx = tx * x;
    float txy = ty * x;
    float txz = tz * x;
    float tyy = ty * y;
    float tyz = tz * y;
    float tzz = tz * z;

	rot.SetIdentity();
    rot.m[0][0] = 1.0f - ( tyy + tzz );
    rot.m[0][1] = txy - twz;
    rot.m[0][2] = txz + twy;
    rot.m[1][0] = txy + twz;
    rot.m[1][1] = 1.0f - ( txx + tzz );
    rot.m[1][2] = tyz - twx;
    rot.m[2][0] = txz - twy;
    rot.m[2][1] = tyz + twx;
    rot.m[2][2] = 1.0f - ( txx + tyy );
}

//-------------------------------------------------------------------------------
void TQuaternion::FromAngleAxis(const float& angle, const TVector3& axis)
{
    float halfAngle = 0.5f * angle;
    float fsin = sinf(halfAngle);
    w = cosf(halfAngle);
    x = -fsin * axis.x;
    y = -fsin * axis.y;
    z = -fsin * axis.z;
}

//-------------------------------------------------------------------------------
void TQuaternion::ToAngleAxis(float& angle, TVector3& axis) const
{
    float sqrLength = x*x + y*y + z*z;
    if (sqrLength > 0.0)
    {
        angle = 2.0f * acosf(w);
        float invLength = 1.0f / sqrtf(sqrLength);
        axis.x = x * invLength;
        axis.y = y * invLength;
        axis.z = z * invLength;
    }
    else
    {
        // angle is 0 (mod 2*pi), so any axis will do
        angle = 0.0f;
        axis.x = 1.0f;
        axis.y = 0.0f;
        axis.z = 0.0f;
    }
}

//-------------------------------------------------------------------------------
void TQuaternion::FromAxes(const TVector3 axis[3])
{
    TMatrix rot;
	rot.SetIdentity();

    for (unsigned int i = 0; i < 3; ++i)
    {
        rot[0][i] = axis[i].x;
        rot[1][i] = axis[i].y;
        rot[2][i] = axis[i].z;
    }

    FromRotationMatrix( rot );
}

//-------------------------------------------------------------------------------
void TQuaternion::FromEulerAnglesXYZ(const TVector3& angles)
{
	float Xw;
	float Xx;
	float Yw;
	float Yy;
	float Zw;
	float Zz;

	SinCos(angles.x/2.f, Xx, Xw);
	SinCos(angles.y/2.f, Yy, Yw);
	SinCos(angles.z/2.f, Zz, Zw);

	w = (Xw * Yw * Zw) - (-Xx * -Yy * -Zz);
	x = (-Xx * Yw * Zw) + (Xw * -Yy * -Zz);
	y = (Xw * -Yy * Zw) - (-Xx * Yw * -Zz);
	z = (Xw * Yw * -Zz) + (-Xx * -Yy * Zw);
}

//-------------------------------------------------------------------------------
void TQuaternion::FromEulerAnglesYXZ(const TVector3& angles)
{
	float Xw;
	float Xx;
	float Yw;
	float Yy;
	float Zw;
	float Zz;

	SinCos(angles.x/2.f, Xx, Xw);
	SinCos(angles.y/2.f, Yy, Yw);
	SinCos(angles.z/2.f, Zz, Zw);

	w = (Yw * Xw * Zw) - (-(-Yy * -Xx)) * -Zz;
	x = (Yw * -Xx * Zw) + (-Yy * Xw * -Zz);
	y = (-Yy * Xw * Zw) - (Yw * -Xx * -Zz);
	z = (Yw * Xw * -Zz) + (-(-Yy * -Xx)) * Zw;
}

//-------------------------------------------------------------------------------
void TQuaternion::FromEulerAnglesZXY(const TVector3& angles)
{
	float Xw;
	float Xx;
	float Yw;
	float Yy;
	float Zw;
	float Zz;

	SinCos(angles.x/2.f, Xx, Xw);
	SinCos(angles.y/2.f, Yy, Yw);
	SinCos(angles.z/2.f, Zz, Zw);

	w = (Zw * Xw) * Yw - (-Zz * -Xx) * -Yy;
	x = (Zw * -Xx) * Yw - (-Zz * Xw) * -Yy;
	y = (Zw * Xw) * -Yy + (-Zz * -Xx) * Yw;
	z = (-Zz * Xw) * Yw + (Zw * -Xx) * -Yy;
}

//-------------------------------------------------------------------------------
void TQuaternion::ToAxes(TVector3 axis[3]) const
{
    TMatrix rot;

    ToRotationMatrix(rot);

    for (unsigned int i = 0; i < 3; ++i)
    {
        axis[i].x = rot[0][i];
        axis[i].y = rot[1][i];
        axis[i].z = rot[2][i];
    }
}

//-------------------------------------------------------------------------------
TVector3 TQuaternion::operator*(const TVector3& v) const
{
    TMatrix rot;
    ToRotationMatrix(rot);
    return rot * v;
}

//-------------------------------------------------------------------------------
TQuaternion TQuaternion::Inverse() const
{
    float norm = w*w + x*x + y*y + z*z;
    if (norm > 0.0)
    {
        float invNorm = 1.0f / norm;
        return TQuaternion(w*invNorm, -x*invNorm, -y*invNorm, -z*invNorm);
    }
    else
    {
        // return an invalid result to flag the error
        return ZERO;
    }
}

//-------------------------------------------------------------------------------
TQuaternion TQuaternion::Exp() const
{
    float angle = sqrtf(x*x + y*y + z*z);
    float fsin = sinf(angle);

    TQuaternion result;
    result.SetW(cosf(angle));

    if (fabs(fsin) >= EPSILON)
    {
        float coeff = fsin / angle;
        result.SetX(coeff * x);
        result.SetY(coeff * y);
        result.SetZ(coeff * z);
    }
    else
    {
        result.SetX(x);
        result.SetY(y);
        result.SetZ(z);
    }

    return result;
}

//-------------------------------------------------------------------------------
TQuaternion TQuaternion::Log() const
{
    TQuaternion result;
    result.w = 0.0;

    if (fabs(w) < 1.0f)
    {
        float angle = acosf(w);
        float fsin = sinf(angle);
        if (fabs(fsin) >= EPSILON)
        {
            float coeff = angle / fsin;
            result.SetX(coeff * x);
            result.SetY(coeff * y);
            result.SetZ(coeff * z);
            return result;
        }
    }

    result.SetX(x);
    result.SetY(y);
    result.SetZ(z);

    return result;
}

//-------------------------------------------------------------------------------
TQuaternion TQuaternion::Slerp(float t, const TQuaternion& p, const TQuaternion& q)
{
	TQuaternion to = q;
    float cos = DotProduct(p, to);
	if (cos < 0.0f)
	{
		cos = -cos;
		to = TQuaternion(-q.GetW(), -q.GetX(), -q.GetY(), -q.GetZ());
	}

    if (cos >  1.0f) 
    {
		cos = 1.0f;
	}
    if (cos < -1.0f) 
    {
		cos = -1.0f;
	}

	float angle = acosf(cos);
    
	if (fabs(angle) < EPSILON)
	{
        return p;
    }

    float fsin = sinf(angle);
    float invSin = 1.0f / fsin;
    float coeff0 = sinf((1.0f - t ) * angle) * invSin;
    float coeff1 = sinf(t * angle) * invSin;
    return (p * coeff0) + (to * coeff1);
}
