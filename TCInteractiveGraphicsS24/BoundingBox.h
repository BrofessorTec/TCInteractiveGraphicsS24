#pragma once
#include "glm/glm.hpp"
#include "GeometricPlane.h"
#include "Ray.h"
#include "vector"

class BoundingBox
{
public:
	static const int FRONT = 0;
	static const int BACK = 1;
	static const int LEFT = 2;
	static const int RIGHT = 3;
	static const int TOP = 4;
	static const int BOTTOM = 5;
protected:
	float width = 1.0f, height = 1.0f, depth = 1.0f;
	glm::mat4 frame = glm::mat4(1.0f);;
	glm::mat4 invFrame;
	GeometricPlane planes[6];
	std::vector<Intersection> intersections;
	glm::vec3 intersectionPoint{};
public:
	BoundingBox();

	void SetReferenceFrame(glm::mat4 frameIn) {
		frame = frameIn;
		invFrame = glm::inverse(frame);
	}
	const glm::mat4& GetReferenceFrame() const { return frame; }
	const std::vector<Intersection>& GetIntersections() const {
		return intersections;
	}
	const glm::vec3& GetIntersectionPoint() const {
		return intersectionPoint;
	}
	void Create(float width = 1.0f, float height = 1.0f, float depth = 1.0f);
	bool IsIntersectingWithRay(const Ray& ray);
	const Intersection& GetIntersection(int whichPlane) {
		return intersections[whichPlane];
	}

};
