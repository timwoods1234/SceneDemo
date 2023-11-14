#include "Collision.h"
#include "TVector3.h"
#include "TLine.h"
#include "TTriangle.h"
#include "TRay.h"
#include "TAABB.h"
#include "TSphere.h"
#include "TPlane.h"

//-------------------------------------------------------------------------------
void GetIntersectPoints(const TRay& ray, const TSphere& sphere, unsigned int& numPoints, TVector3 results[2])
{
	TVector3 kDiff = ray.GetOrigin() - sphere.GetCentre();
    float fA = ray.GetDirection().GetSquaredLength();
	float fB = DotProduct( kDiff, ray.GetDirection() );
    float fC = kDiff.GetSquaredLength() - sphere.GetRadius()*sphere.GetRadius();

    float afT[2];
    float fDiscr = fB*fB - fA*fC;
    if ( fDiscr < 0.0 )
    {
        numPoints = 0;
    }
    else if ( fDiscr > 0.0 )
    {
        float fRoot = sqrtf(fDiscr);
        float fInvA = 1.0f/fA;
        afT[0] = (-fB - fRoot)*fInvA;
        afT[1] = (-fB + fRoot)*fInvA;

        if ( afT[0] >= 0.0f )
            numPoints = 2;
        else if ( afT[1] >= 0.0f )
            numPoints = 1;
        else
            numPoints = 0;
    }
    else
    {
        afT[0] = -fB/fA;
        numPoints = ( afT[0] >= 0.0 ? 1 : 0 );
    }

    for(unsigned int i = 0; i<numPoints; ++i )
	{
        results[i] = ray.GetOrigin() + ray.GetDirection()*afT[i];
	}
}

//-------------------------------------------------------------------------------
bool GetIntersectPoints(const TRay& ray, const TPlane& plane, TVector3& result)
{
	float term1 = ray.GetOrigin().x * plane.GetNormal().x + 
				   ray.GetOrigin().y * plane.GetNormal().y + 
				   ray.GetOrigin().z * plane.GetNormal().z -
				   plane.GetConstant();

	float term2 = (-ray.GetDirection().x) * plane.GetNormal().x +
				   (-ray.GetDirection().y) * plane.GetNormal().y + 
				   (-ray.GetDirection().z) * plane.GetNormal().z;

	float u = (term2 == 0.0f) ? 0.0f : term1 / term2;

	if ( u > 0.0f )
	{
		result = (ray.GetDirection() * u) + ray.GetOrigin();
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------
bool GetIntersectPoints(const TTriangle& tri, const TPlane& plane, TLine& edge)
{
	// Vertex clipping.
	float dist1 = DotProduct( plane.GetNormal(), tri.v1 ) - plane.GetConstant();
	float dist2 = DotProduct( plane.GetNormal(), tri.v2 ) - plane.GetConstant();
	float dist3 = DotProduct( plane.GetNormal(), tri.v3 ) - plane.GetConstant();

	if( dist1 > 0.f && dist2 > 0.f && dist3 > 0.f )
	{
		return false; // not clipped.
	}

	if( dist1 < 0.f && dist2 < 0.f && dist3 < 0.f )
	{
		return false; // totally clipped.
	}

	edge.m_p0 = TVector3( 0.f, 0.f, 0.f );
	edge.m_p1 = TVector3( 0.f, 0.f, 0.f );

    // The edge is split by the plane.  Compute the point of
    // intersection.  If the old edge is <V0,V1> and I is the
    // intersection point, the new edge is <V0,I> when d0 > 0 or
    // <I,V1> when d1 > 0.

	bool edge1Clipped = false;
	bool edge2Clipped = false;
	bool edge3Clipped = false;

	// Edge Clipping.
	// Edge 1
	if(( dist1 >= FLT_MIN && dist2 <= FLT_MIN ) || ( dist1 <= FLT_MIN && dist2 >= FLT_MIN )) 	
	{
		// Build the intersection 
	    TVector3 newVec = tri.v1 + (( tri.v2 - tri.v1 ) * ( dist1 / ( dist1 - dist2 )));

		if ( dist1 > 0.0f )
		{
			edge.m_p0 = newVec;
		}
		else
		{
			edge.m_p1 = newVec;
		}

		edge1Clipped = true;

	}
	
	// Edge 2
	if((dist2 >= FLT_MIN && dist3 <= FLT_MIN) || (dist2 <= FLT_MIN && dist3 >= FLT_MIN)) // Edge 2
	{
	    TVector3 newVec = tri.v2 + (( tri.v3 - tri.v2 ) * ( dist2 / ( dist2 - dist3 )));

		if ( dist2 > 0.0f )
		{
			edge.m_p0 = newVec;
		}
		else
		{
			edge.m_p1 = newVec;
		}

		edge2Clipped = true;
	}

	// Edge 3
	if((dist3 >= FLT_MIN && dist1 <= FLT_MIN) || (dist3 <= FLT_MIN && dist1 >= FLT_MIN)) // Edge 3
	{
	    TVector3 newVec = tri.v3 + (( tri.v1 - tri.v3) * ( dist3 / ( dist3 - dist1 )));

		if ( dist3 > 0.0f )
			edge.m_p0 = newVec;
		else
			edge.m_p1 = newVec;

		edge3Clipped = true;
	}

	// Edge Clipping.
	if(!((edge1Clipped && edge2Clipped) ||(edge1Clipped && edge3Clipped) || (edge2Clipped && edge3Clipped)))
	{
		// Edge 1
		if(( dist1 > 0.f && dist2 < 0.f ) || ( dist1 < 0.f && dist2 > 0.f ))
		{
			// Build the intersection 
			TVector3 newVec = tri.v1 + (( tri.v2 - tri.v1 ) * ( dist1 / ( dist1 - dist2 )));

			if ( dist1 > 0.0f )
			{
				edge.m_p0 = newVec;
			}
			else
			{
				edge.m_p1 = newVec;
			}

			edge1Clipped = true;

		}
		
		// Edge 2
		if((dist2 > 0.f && dist3 < 0.f) || (dist2 < 0.f && dist3 > 0.f)) // Edge 2
		{
			TVector3 newVec = tri.v2 + (( tri.v3 - tri.v2 ) * ( dist2 / ( dist2 - dist3 )));

			if ( dist2 > 0.0f )
			{
				edge.m_p0 = newVec;
			}
			else
			{
				edge.m_p1 = newVec;
			}

			edge2Clipped = true;
		}

		// Edge 3
		if((dist3 >= 0.f && dist1 <= 0.f) || (dist3 <= 0.f && dist1 >= 0.f)) // Edge 3
		{
			TVector3 newVec = tri.v3 + (( tri.v1 - tri.v3) * ( dist3 / ( dist3 - dist1 )));

			if ( dist3 > 0.0f )
			{
				edge.m_p0 = newVec;
			}
			else
			{
				edge.m_p1 = newVec;
			}

			edge3Clipped = true;
		}
	}
	return true;
}

//-------------------------------------------------------------------------------
bool GetIntersectPoints(const TRay& ray, const TAABB& box, TVector3& result)
{
	// Check for point inside box, trivial reject, and determine parametric distance to each front face
	bool inside = true;

	float xt, xn;
	if (ray.GetOrigin().x < box.GetMin().x)
	{
		xt = box.GetMin().x - ray.GetOrigin().x;
		if (xt > ray.GetDirection().x) return false;
		xt /= ray.GetDirection().x;
		inside = false;
		xn = -1.0f;
	}
	else if (ray.GetOrigin().x > box.GetMax().x)
	{
		xt = box.GetMax().x - ray.GetOrigin().x;
		if (xt < ray.GetDirection().x) return false;
		xt /= ray.GetDirection().x;
		inside = false;
		xn = 1.0f;
	} 
	else 
	{
		xt = -1.0f;
	}

	float yt, yn;
	if (ray.GetOrigin().y < box.GetMin().y)
	{
		yt = box.GetMin().y - ray.GetOrigin().y;
		if (yt > ray.GetDirection().y) return false;
		yt /= ray.GetDirection().y;
		inside = false;
		yn = -1.0f;
	}
	else if (ray.GetOrigin().y > box.GetMax().y)
	{
		yt = box.GetMax().y - ray.GetOrigin().y;
		if (yt < ray.GetDirection().y) return false;
		yt /= ray.GetDirection().y;
		inside = false;
		yn = 1.0f;
	}
	else
	{
		yt = -1.0f;
	}

	float zt, zn;
	if (ray.GetOrigin().z < box.GetMin().z)
	{
		zt = box.GetMin().z - ray.GetOrigin().z;
		if (zt > ray.GetDirection().z) return false;
		zt /= ray.GetDirection().z;
		inside = false;
		zn = -1.0f;
	}
	else if (ray.GetOrigin().z > box.GetMax().z)
	{
		zt = box.GetMax().z - ray.GetOrigin().z;
		if (zt < ray.GetDirection().z) return false;
		zt /= ray.GetDirection().z;
		inside = false;
		zn = 1.0f;
	}
	else
	{
		zt = -1.0f;
	}

	// Inside box?

	if (inside)
	{
		return false;
	}

	// Select farthest plane - this is
	// the plane of intersection.

	int which = 0;
	float t = xt;

	if (yt > t)
	{
		which = 1;
		t = yt;
	}
	if (zt > t)
	{
		which = 2;
		t = zt;
	}

	switch (which)
	{
		case 0: // intersect with yz plane
		{
			float y = ray.GetOrigin().y + ray.GetDirection().y*t;
			if (y < box.GetMin().y || y > box.GetMax().y) return false;
			float z = ray.GetOrigin().z + ray.GetDirection().z*t;
			if (z < box.GetMin().z || z > box.GetMax().z) return false;
		}
		break;

		case 1: // intersect with xz plane
		{
			float x = ray.GetOrigin().x + ray.GetDirection().x*t;
			if (x < box.GetMin().x || x > box.GetMax().x) return false;
			float z = ray.GetOrigin().z + ray.GetDirection().z*t;
			if (z < box.GetMin().z || z > box.GetMax().z) return false;
		} 
		break;

		case 2: // intersect with xy plane
		{
			float x = ray.GetOrigin().x + ray.GetDirection().x*t;
			if (x < box.GetMin().x || x > box.GetMax().x) return false;
			float y = ray.GetOrigin().y + ray.GetDirection().y*t;
			if (y < box.GetMin().y || y > box.GetMax().y) return false;
		}
		break;
	}

	// Return parametric point of intersection
	result = ray.GetOrigin() + (ray.GetDirection() * t);
	return true;
}

//-------------------------------------------------------------------------------
bool GetIntersectPoints(const TAABB& box, const TSphere& sphere, TVector3& result)
{
	result = box.GetClosestPoint(sphere.GetCentre());
	return SquaredDistance(result, sphere.GetCentre()) < sphere.GetRadius() * sphere.GetRadius();
}