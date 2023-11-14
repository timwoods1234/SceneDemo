#ifndef __COLLISION_H__
#define __COLLISION_H__

// Collision Detection Functions

#ifndef __TMATH_H__
#include "TMath.h"
#endif

class TVector3;
class TRay;
class TSphere;
class TPlane;
class TTriangle;
class TLine;
class TAABB;

// macro for simple sphere-based collision check. a1, a2 are 'alive' flags
#define CollisionAt(pt1, pt2, r1, r2)	SquaredDistance(pt2, pt1) < ( (r1 + r2) * (r1 + r2) )
#define CollisionAtAlive(pt1, pt2, r1, r2, a1, a2)	( a1 && a2 &&  CollisionAt(pt1, pt2, r1, r2) )

bool IntersectTest(const TRay& ray, const TSphere& sphere);
bool IntersectTest(const TRay& ray, const TAABB& box);
bool IntersectTest(const TRay& ray, const TPlane& plane);
bool IntersectTest(const TAABB& box1, const TAABB& box2);
bool IntersectTest(const TAABB& box, const TSphere& sphere);
bool IntersectTest(const TSphere& sphere, const TPlane& plane);
bool IntersectTest(const TAABB& box, const TPlane& plane);
bool IntersectTest(const TSphere& s1, const TSphere& s2);

TCullingFlag CullingTest(const TAABB& box, const TPlane& plane);
TCullingFlag CullingTest(const TSphere& sphere, const TPlane& plane);
TCullingFlag CullingTest(const TVector3& point, const TPlane& plane, float epsilon = 0.0001f);

void GetIntersectPoints(const TRay& ray, const TSphere& sphere, unsigned int& numPoints, TVector3 results[2]);
bool GetIntersectPoints(const TRay& ray, const TAABB& box, TVector3& result);
bool GetIntersectPoints(const TRay& ray, const TPlane& plane, TVector3& result);
bool GetIntersectPoints(const TTriangle& tri, const TPlane& plane, TLine& edge);
bool GetIntersectPoints(const TAABB& box, const TSphere& sphere, TVector3& result);

//+----------------------------------------------------------------
//| Sphere Physics
//+----------------------------------------------------------------

// Tests if a moving sphere &a will collide with stationary sphere &b
bool CheckCollision(TVector3 &a_position, TVector3 &b_position,
					float a_mass, float b_mass,
					TVector3 &a_move);

// Tests if two moving spheres will collide
bool CheckMovingCollision(TVector3 &a_position, TVector3 &b_position,
						  float a_mass, float b_mass,
						  TVector3 &a_move, TVector3 &b_move);

// Simulates a "bounce" between two spheres
void CreateBounce(TVector3 &a_position, TVector3 &b_position,
				  float a_mass, float b_mass,
				  TVector3 &a_move, TVector3 &b_move,
				  TVector3 &a_direction, TVector3 &b_direction);

// move two objects apart (assumes they are touching)
void MoveApart(TVector3& a_position, TVector3& b_position,
			   const float a_radius, const float b_radius);

#endif