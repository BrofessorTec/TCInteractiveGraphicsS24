#include "ObjectManager.h"
#include "IAnimation.h"
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

std::unordered_map<std::string, std::shared_ptr<GraphicsObject>> ObjectManager::GetObjectMap()
{
	return objectsMap;
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

void ObjectManager::SetBehaviorDefaults()
{
	// It loops through all the objects setting their behavior defaults.
	for (auto& [name, object] : objectsMap) {
		object->SetBehaviorDefaults();
	}
}
