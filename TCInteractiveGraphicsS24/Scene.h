#pragma once
#include <memory>
#include <vector>
#include "GraphicsObject.h"
#include "GraphicStructures.h"
#include "glm/glm.hpp"

class Scene
{
private:
	std::vector<std::shared_ptr<GraphicsObject>> objects;
	GraphicStructures::Light globalLight = { glm::vec3(0.0f), glm::vec3(1.0f), 1.0f, 1.0f };
	GraphicStructures::Light locaLight = { glm::vec3(0.0f), glm::vec3(1.0f), 1.0f, 1.0f };

public:
	Scene() = default;
	~Scene() = default;
	inline const std::vector<std::shared_ptr<GraphicsObject>>& GetObjects() const {
		return objects;
	}
	void AddObject(std::shared_ptr<GraphicsObject> object);
	GraphicStructures::Light& GetGlobalLight();
	GraphicStructures::Light& GetLocalLight();
};

