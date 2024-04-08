#pragma once
#include <glm/glm.hpp>

class Ray
{
public:
	glm::vec3 startPoint;
	glm::vec3 direction;
	Ray() {};
	Ray(glm::vec3 start, glm::vec3 end);
	glm::vec3 GetIntersectionPoint(float offset) const;
};

