#include "ObjectManager.h"

void ObjectManager::SetObject(std::string key, GraphicsObject object)
{
	objectsMap[key] = object;
}

GraphicsObject ObjectManager::GetObject(std::string key)
{
	return objectsMap[key];
}
