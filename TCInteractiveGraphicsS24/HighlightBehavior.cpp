#include "HighlightBehavior.h"
#include "GraphicsObject.h"

void HighlightBehavior::StoreDefaults()
{
	if (object == nullptr) return;
	ambientIntensity = this->object->GetMaterial().ambientIntensity;
	// how to fix this pointer?
}

void HighlightBehavior::SetParameter(GraphicStructures::IParams& params)
{
	this->params = reinterpret_cast<GraphicStructures::HighlightParams&>(params);
}

void HighlightBehavior::Update(double elapsedSeconds)
{
	if (object == nullptr) return;
	if (object->IsIntersectingWithRay(*params.ray)) {
		object->GetMaterial().ambientIntensity = 1.0f;
	}
	else {
		object->GetMaterial().ambientIntensity = ambientIntensity;
	}
}
