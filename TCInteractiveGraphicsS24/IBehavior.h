#pragma once
#include <memory>
#include <sstream>
#include "Ray.h"
#include "GraphicStructures.h"

class GraphicsObject; // Forward declaration

class IBehavior
{
protected:
	std::shared_ptr<GraphicsObject> object;
public:
	IBehavior() : object(nullptr) {}
	virtual ~IBehavior() = default;
	virtual void SetObject(std::shared_ptr<GraphicsObject> object);
	virtual void SetParameter(GraphicStructures::IParams& params) {};
	virtual void StoreDefaults() {};
	virtual void Update(double elapsedSeconds) = 0; 
};

