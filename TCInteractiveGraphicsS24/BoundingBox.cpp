#include "BoundingBox.h"
#include "Ray.h"

BoundingBox::BoundingBox()
{
	frame = glm::mat4(1.0f);
	Create(1.0f, 1.0f, 1.0f);
}

void BoundingBox::Create(float width, float height, float depth)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
	float hw = this->width / 2;
	float hh = this->height / 2;
	float hd = this->depth / 2;
	glm::vec3 xAxis = glm::vec3(frame[0]);
	glm::vec3 yAxis = glm::vec3(frame[1]);
	glm::vec3 zAxis = glm::vec3(frame[2]);
	planes[FRONT].Set(-zAxis, hd);
	planes[BACK].Set(zAxis, hd);
	planes[RIGHT].Set(-xAxis, hw);
	planes[LEFT].Set(xAxis, hw);
	planes[TOP].Set(-yAxis, hh);
	planes[BOTTOM].Set(yAxis, hh);
}

bool BoundingBox::IsIntersectingWithRay(const Ray& ray)
{
	intersections.clear();
	float intersection;
	Ray localRay;
	glm::vec3 localStart = glm::vec3(
		invFrame * glm::vec4(ray.startPoint, 1.0f)
	);
	localRay.startPoint = localStart;
	glm::vec3 localDir = glm::vec3(
		invFrame * glm::vec4(ray.direction, 0.0f)
	);
	localRay.direction = localDir;
	for (int i = FRONT; i <= BOTTOM; i++) {
		intersection = planes[i].GetIntersectionOffset(localRay);
		intersections.push_back(intersection);
	}

	//Test intersection with the 2 planes perpendicular to the OBB's X axis
	float nearestFarI = intersections[BACK];
	float farthestNearI = intersections[FRONT];
	if (nearestFarI < farthestNearI)
		std::swap(nearestFarI, farthestNearI);
	float nearI = intersections[LEFT];
	float farI = intersections[RIGHT];
	if (nearI > farI)
		std::swap(nearI, farI);
	if (nearI != farI) {
		if (farI < nearestFarI) nearestFarI = farI;
		if (nearI > farthestNearI) farthestNearI = nearI;
		if (nearestFarI < farthestNearI) return false;
	}

	//Test intersection with 2 planes perpendicular to the OBB's Y axis
	nearI = intersections[FRONT];
	farI = intersections[BACK];
	if (nearI > farI)
		std::swap(nearI, farI);
	if (nearI != farI) {
		if (farI < nearestFarI) nearestFarI = farI;
		if (nearI > farthestNearI) farthestNearI = nearI;
		if (nearestFarI < farthestNearI) return false;
	}

	//Test intersection with 2 planes perpendicular to the OBB's Z axis
	nearI = intersections[TOP];
	farI = intersections[BOTTOM];
	if (nearI > farI)
		std::swap(nearI, farI);
	if (nearI != farI) {
		if (farI < nearestFarI) nearestFarI = farI;
		if (nearI > farthestNearI) farthestNearI = nearI;
		if (nearestFarI < farthestNearI) return false;
	}

	intersectionPoint = ray.GetIntersectionPoint(nearestFarI);
	return true;
}
