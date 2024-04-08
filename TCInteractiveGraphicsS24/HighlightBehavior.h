#pragma once
#include "IBehavior.h"
#include "GraphicStructures.h"

class HighlightBehavior : IBehavior
{
protected:
	GraphicStructures::HighlightParams params;
	float ambientIntensity = 0.0f;

public:
	void StoreDefaults() override;
	void SetParameter(GraphicStructures::IParams& param) override;

};

