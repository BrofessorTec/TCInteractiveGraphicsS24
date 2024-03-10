#include "Scene.h"

void Scene::AddObject(std::shared_ptr<GraphicsObject> object)
{
	objects.push_back(object);
}

GraphicStructures::Light& Scene::GetGlobalLight()
{
	return globalLight;
}

GraphicStructures::Light& Scene::GetLocalLight()
{
	return locaLight;
}
