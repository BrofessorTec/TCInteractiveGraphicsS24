#include "HighlightBehavior.h"

void HighlightBehavior::StoreDefaults()
{
	if (object == nullptr) return;
	ambientIntensity = this->object->GetMaterial().ambientIntensity;
	// how to fix this pointer?
}

void HighlightBehavior::SetParameter(GraphicStructures::IParams& param)
{
	this->params = reinterpret_cast<GraphicStructures::HighlightParams&>(params);
}
