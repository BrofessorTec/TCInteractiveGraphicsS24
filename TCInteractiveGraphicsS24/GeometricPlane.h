#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class GeometricLine;

// Vince, J. (2014). Mathematics for Computer Graphics, Springer

struct Intersection {
	bool isIntersecting = false;
	float offset = -1.0f;
};

class GeometricPlane
{
protected:
	glm::vec3 normal;
	float distanceFromOrigin;

public:
	GeometricPlane();
	~GeometricPlane() = default;

	void SetNormal(glm::vec3 normal) { this->normal = normal; }
	void SetDistanceFromOrigin(float distance) {
		distanceFromOrigin = fabs(distance);
	}
	void Set(glm::vec3 normal, float distance) {
		SetNormal(normal);
		SetDistanceFromOrigin(distance);
	}

	Intersection GetIntersectionWithLine(const GeometricLine& line) const;
	float GetIntersectionOffset(Ray ray);
};

