#pragma once
#include "GraphicsObject.h"

class ObjectManager
{
private:
	std::unordered_map<std::string, GraphicsObject> objectsMap;

public:
	void SetObject(std::string key, GraphicsObject object);
	GraphicsObject GetObject(std::string key);


};

