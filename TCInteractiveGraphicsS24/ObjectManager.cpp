#include "ObjectManager.h"
#include <iostream>

void ObjectManager::SetObject(std::string key, std::shared_ptr<GraphicsObject> graphObj)
{
	//objectsMap[key] = object;
	objectsMap.emplace(key, graphObj);
}

std::shared_ptr<GraphicsObject> ObjectManager::GetObject(std::string key)
{
	return objectsMap[key];
}

void ObjectManager::Update(double elapsedSeconds)
{
	for (auto& pair : objectsMap) {
		std::string key = pair.first;
		std::shared_ptr<GraphicsObject> graphObject = pair.second;

		// Process key and graphics object
		std::cout << "Key: " << key << ", GraphObject: ";
		graphObject->Update(elapsedSeconds);
		std::cout << std::endl;
	}
}
