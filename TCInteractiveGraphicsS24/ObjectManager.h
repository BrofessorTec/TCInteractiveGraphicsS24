#pragma once
#include "GraphicsObject.h"

class ObjectManager
{
private:
	std::unordered_map<std::string, std::shared_ptr<GraphicsObject>> objectsMap;

public:
	void SetObject(std::string key, std::shared_ptr<GraphicsObject> graphObj);
	std::shared_ptr<GraphicsObject> GetObject(std::string key);
	std::unordered_map<std::string, std::shared_ptr<GraphicsObject>> GetObjectMap();
	void Update(double elapsedSeconds);
	void SetBehaviorDefaults();
};

