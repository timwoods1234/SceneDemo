#include "Collision.h"
#include "TVector3.h"
#include "TPlane.h"
#include "TSphere.h"
#include "TAABB.h"
#include "TRay.h"

//-------------------------------------------------------------------------------
float Distance(const TVector3& point, const TRay& ray)
{
    TVector3 kDiff = point - ray.GetOrigin();
    float fSqrLen = ray.GetDirection().GetSquaredLength();
	float fT = DotProduct( kDiff, ray.GetDirection() ) / fSqrLen;
    kDiff -= ray.GetDirection() * fT;

    return kDiff.GetSquaredLength();
}

//-------------------------------------------------------------------------------
float Distance( const TVector3& point, const TPlane& plane )
{
	return DotProduct(plane.GetNormal(), point) - plane.GetConstant();
}

//-------------------------------------------------------------------------------
bool IntersectTest(const TRay& ray, const TSphere& sphere)
{
	float dist = Distance( sphere.GetCentre(), ray );
	return dist <= (sphere.GetRadius() * sphere.GetRadius());
}

//-------------------------------------------------------------------------------
bool IntersectTest(const TRay& ray, const TPlane& plane)
{
	TVector3 result;
	return GetIntersectPoints(ray, plane, result);
}

//-------------------------------------------------------------------------------
bool IntersectTest(const TAABB& box1, const TAABB& box2)
{
	TVector3 doubleCentreDiff = (box1.GetMin() + box1.GetMax()) - (box2.GetMin() + box2.GetMax());
	TVector3 size0, size1;
	box1.GetSize(size0);
	box2.GetSize(size1);

	return (fabs(doubleCentreDiff.x) <= size0.x + size1.x &&
			fabs(doubleCentreDiff.y) <= size0.y + size1.y &&
			fabs(doubleCentreDiff.z) <= size0.z + size1.z);
}

//-------------------------------------------------------------------------------
bool IntersectTest(const TRay& ray, const TAABB& box)
{
	TVector3 result;
	return GetIntersectPoints(ray, box, result);
}

//-------------------------------------------------------------------------------
bool IntersectTest(const TAABB& box, const TSphere& sphere)
{
	TVector3 result = box.GetClosestPoint(sphere.GetCentre());
	return SquaredDistance(result, sphere.GetCentre()) < sphere.GetRadius() * sphere.GetRadius();
}

//-------------------------------------------------------------------------------
bool IntersectTest(const TSphere& sphere, const TPlane& plane)
{
	float dist = DotProduct(sphere.GetCentre(), plane.GetNormal()) + plane.GetConstant();
	return (fabs(dist) < sphere.GetRadius());
}

//-------------------------------------------------------------------------------
bool IntersectTest(const TAABB& box, const TPlane& plane)
{
	float	minD, maxD;

	if (plane.GetNormal().x > 0.0f)
	{
		minD = plane.GetNormal().x*box.GetMin().x; maxD = plane.GetNormal().x*box.GetMax().x;
	}
	else
	{
		minD = plane.GetNormal().x*box.GetMax().x; maxD = plane.GetNormal().x*box.GetMin().x;
	}

	if (plane.GetNormal().y > 0.0f)
	{
		minD += plane.GetNormal().y*box.GetMin().y; maxD += plane.GetNormal().y*box.GetMax().y;
	}
	else
	{
		minD += plane.GetNormal().y*box.GetMax().y; maxD += plane.GetNormal().y*box.GetMin().y;
	}

	if (plane.GetNormal().z > 0.0f)
	{
		minD += plane.GetNormal().z*box.GetMin().z; maxD += plane.GetNormal().z*box.GetMax().z;
	}
	else
	{
		minD += plane.GetNormal().z*box.GetMax().z; maxD += plane.GetNormal().z*box.GetMin().z;
	}

	if (minD >= plane.GetConstant())
	{	// Check if completely on the front side of the plane
		return false;
	}

	if (maxD <= plane.GetConstant())
	{	// Check if completely on the back side of the plane
		return false;
	}

	return true;	// We straddle the plane
}

//-------------------------------------------------------------------------------
bool IntersectTest(const TSphere& s1, const TSphere& s2)
{
	return CollisionAt(s1.GetCentre(), s2.GetCentre(), s1.GetRadius(), s2.GetRadius());
}
