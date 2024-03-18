#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "VertexBuffer.h"
#include "GraphicStructures.h"

class IAnimation; // Forward declaration


class GraphicsObject
{
protected:
	glm::mat4 referenceFrame;
	std::shared_ptr<VertexBuffer> buffer;
	GraphicsObject* parent;
	std::vector<std::shared_ptr<GraphicsObject>> children;
	std::shared_ptr<IAnimation> animation = nullptr;
	GraphicStructures::Material material{};


public:
	GraphicsObject();
	virtual ~GraphicsObject();
	GraphicStructures::Material& GetMaterial();
	const glm::mat4 GetReferenceFrame() const;
	void CreateVertexBuffer(unsigned int numberOfElementsPerVertex);
	void SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
	inline const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const {
		return buffer;
	}
	void StaticAllocateVertexBuffer();

	void AddChild(std::shared_ptr<GraphicsObject> child);
	inline const std::vector<std::shared_ptr<GraphicsObject>>& GetChildren() const {
		return children;
	}

	void SetPosition(const glm::vec3& position);
	void ResetOrientation();
	void RotateLocalX(float degrees);
	void RotateLocalY(float degrees);
	void RotateLocalZ(float degrees);
	void SetReferenceFrame(glm::mat4 newReferenceFrame);
	void Update(double elapsedSeconds);   //needs definition
	void SetAnimation(std::shared_ptr<IAnimation> animation);
	glm::mat4& GetLocalReferenceFrame() { return referenceFrame; };
	void PointAtTarget(glm::vec3 position);
};

