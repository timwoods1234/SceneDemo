#include "Collision.h"
#include "TSphere.h"
#include "TPlane.h"
#include "TAABB.h"

//-------------------------------------------------------------------------------
TCullingFlag CullingTest(const TVector3& point, const TPlane& plane, float epsilon)
{
	float dp = DotProduct(point, plane.GetNormal()) + plane.GetConstant();

    if (dp < -epsilon)
    {
        return CULLING_OUTSIDE;
    }

    return CULLING_INSIDE;
}

//-------------------------------------------------------------------------------
TCullingFlag CullingTest(const TAABB& box, const TPlane& plane)
{
	float minD;
	float maxD;

	if (plane.GetNormal().x > 0.0f)
	{
		minD = plane.GetNormal().x * box.GetMin().x;
		maxD = plane.GetNormal().x * box.GetMax().x;
	}
	else
	{
		minD = plane.GetNormal().x * box.GetMax().x;
		maxD = plane.GetNormal().x * box.GetMin().x;
	}

	if (plane.GetNormal().y > 0.0f)
	{
		minD += plane.GetNormal().y * box.GetMin().y;
		maxD += plane.GetNormal().y * box.GetMax().y;
	}
	else
	{
		minD += plane.GetNormal().y * box.GetMax().y;
		maxD += plane.GetNormal().y * box.GetMin().y;
	}

	if (plane.GetNormal().z > 0.0f)
	{
		minD += plane.GetNormal().z * box.GetMin().z; 
		maxD += plane.GetNormal().z * box.GetMax().z;
	}
	else
	{
		minD += plane.GetNormal().z * box.GetMax().z;
		maxD += plane.GetNormal().z * box.GetMin().z;
	}

	minD += plane.GetConstant();
	maxD += plane.GetConstant();

	if (maxD < 0.f)
	{
		return CULLING_OUTSIDE;
	}

	if (minD < 0.f)
	{
		return CULLING_INTERSECT;
	}

	return CULLING_INSIDE;
}

//-------------------------------------------------------------------------------
TCullingFlag CullingTest(const TSphere& sphere, const TPlane& plane)
{
    // Find the distance to this plane
	float dist = DotProduct(sphere.GetCentre(), plane.GetNormal()) + plane.GetConstant();

    // If this distance is < -sphere.radius, we are outside
	if (dist < -sphere.GetRadius())
	{
		return CULLING_OUTSIDE;
	}

    // Else if the distance is between +- radius, then we intersect
	if (fabs(dist) < sphere.GetRadius())
	{
        return CULLING_INTERSECT;
	}

	return CULLING_INSIDE;
}

//-------------------------------------------------------------------------------
bool CheckCollision(TVector3 &a_position, TVector3 &b_position, float a_mass, float b_mass, TVector3 &a_move)
{
	// early escape test: check if A is too far away
	float dist = Distance(a_position, b_position);
	float sumRadii = a_mass + b_mass;
	dist -= sumRadii;

	if (a_move.GetLength() < dist)
	{
		return false;
	}

	// Normalize movement vector
	TVector3 n(a_move);
	n.Normalize();

	// Find vector from center of A to center of B
	TVector3 c = b_position - a_position;

	// dot product (overloaded '*')
	double d = DotProduct(n, c);

	// early escape: check A is moving towards B
	if(d <= 0)
	{
	  return false;
	}

	// Find the length of the vector C (above)
	double lenC = c.GetLength();
	double f = (lenC * lenC) - (d * d);

	// escape test: can't collide if the closest that A will get to B
	// is larger than total radius
	double sumRadiiSquared = sumRadii * sumRadii;

	if(f >= sumRadiiSquared)
	{
		return false;
	}

	// triangle math finds how far A can go
	double t = sumRadiiSquared - f;

	// if this is negative, exit
	if(t < 0)
	{
		return false;
	}

	// So A needs to travel along its axis by d - sqrt(T)
	double distance = d - sqrt(t);

	// magnitude of move vector
	double mag = a_move.GetLength();

	// make sure the distance A moves is less than mag
	if(mag < distance)
	{
		return false;
	}

	// Set length of the movevec so A and B will just touch
	a_move.Normalize();
	a_move *= (float)distance;

	return true;
}

//-------------------------------------------------------------------------------
bool CheckMovingCollision(TVector3 &a_position, TVector3 &b_position,
						  float a_mass, float b_mass,
						  TVector3 &a_move, TVector3 &b_move)
{
	TVector3 oldAMoveVec(a_move);
	TVector3 oldBMoveVec(b_move);

	// Movement of A relative to B (assume B is stationary)
	a_move -= b_move;

	if (CheckCollision(a_position, b_position,
						  a_mass, b_mass, a_move))
	{
		// Find time of collision
		float dT = a_move.GetLength() / oldAMoveVec.GetLength();

		if (dT > 1.0f)
		{
			dT = 1.0f;
		}

		// Multiply move vectors by dT
		a_move = (oldAMoveVec * dT);
		a_position += a_move;

		b_move = b_move * dT;
		b_position += b_move;

		// Reset for bounce calcs.
		a_move = oldAMoveVec;
		b_move = oldBMoveVec;

		return true;
	}

	// No collision, revert axis back to original
	a_move = oldAMoveVec;

	return false;
}

//-------------------------------------------------------------------------------
void CreateBounce(TVector3 &a_position, TVector3 &b_position,
				  float a_mass, float b_mass,
				  TVector3 &a_move, TVector3 &b_move,
				  TVector3 &a_direction, TVector3 &b_direction)
{
	// normalized vector from center of A to center of B
	TVector3 n = a_position - b_position;
	n.Normalize();

	// calculate new movement vector of A, v1
	TVector3 v1 = a_direction + (n * b_mass);

	// calculate new movement vector of B, v2
	TVector3 v2 = b_direction - (n * a_mass) ;

	a_direction = v1;
	a_move.Set(0,0,0);
	b_direction = v2;
	b_move.Set(0,0,0);
}

//-------------------------------------------------------------------------------
void MoveApart(TVector3& a_position, TVector3& b_position,
			   const float a_radius, const float b_radius)
{
	TVector3 displacement = a_position - b_position;
	float distance = displacement.GetLength();

	displacement.Normalize();

	displacement *= (a_radius + b_radius) - distance;

	a_position = (a_position + displacement);
	b_position = (b_position - displacement);
}
