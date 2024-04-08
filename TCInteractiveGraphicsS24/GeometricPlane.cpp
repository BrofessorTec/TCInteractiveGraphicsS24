#include "GeometricPlane.h"
#include "GeometricLine.h"

GeometricPlane::GeometricPlane() : normal(0, 1, 0), distanceFromOrigin(0)
{
}

Intersection GeometricPlane::GetIntersectionWithLine(
	const GeometricLine& line) const
{
	Intersection intersection;
	// Vince (2014) pp. 200
	float ndotv = glm::dot(normal, line.GetDirection());
	if (ndotv == 0) return intersection; // parallel
	float ndott = glm::dot(normal, line.GetStartPoint());
	float lambda = -(ndott + distanceFromOrigin) / ndotv;
	intersection.offset = lambda;
	if (lambda < 0) return intersection; // miss, behind view point
	intersection.isIntersecting = true;
	return intersection;
}

float GeometricPlane::GetIntersectionOffset(Ray ray)
{
	float offset = -1.0f;
	float nRayProjection = glm::dot(normal, ray.direction);
	if (nRayProjection == 0) return offset;
	float nStartProjection = glm::dot(normal, ray.startPoint);
	offset = -(nStartProjection + distanceFromOrigin) / nRayProjection;
	return offset;
}
