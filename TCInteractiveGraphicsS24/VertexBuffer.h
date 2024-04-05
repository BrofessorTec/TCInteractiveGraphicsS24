#pragma once
#include <glad/glad.h> 
#include <vector>
#include <unordered_map>
#include <string>
#include "Texture.h"


struct VertexAttribute {
	unsigned int index;
	unsigned int numberOfComponents;
	int type;
	int isNormalized;
	unsigned int bytesToNext;
	void* byteOffset;
};


class VertexBuffer
{
protected:
	unsigned int numberOfElementsPerVertex;
	unsigned int numberOfVertices;
	unsigned int vboId;
	int primitiveType;
	std::vector<float> vertexData;
	std::unordered_map<std::string, VertexAttribute> attributeMap;
	int textureUnit = 0;
	std::shared_ptr<Texture> texture = nullptr;

public:
	VertexBuffer(unsigned int numElementsPerVertex = 6);
	~VertexBuffer();

	inline void Select() { glBindBuffer(GL_ARRAY_BUFFER, vboId); }
	inline void Deselect() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
	inline unsigned int GetNumberOfVertices() const { return numberOfVertices; }
	inline int GetPrimitiveType() const { return primitiveType; }
	inline void SetPrimitiveType(int primitiveType) { this->primitiveType = primitiveType; }

	// Variadic function
	void AddVertexData(unsigned int count, ...);
	void StaticAllocate();
	void AddVertexAttribute(
		const std::string& name, unsigned int index, 
		unsigned int numberOfElements, unsigned int offsetCount=0);
	void SetUpAttributeInterpretration();
	int GetTextureUnit();
	void SetTextureUnit(int textureUnit);
	std::shared_ptr<Texture> GetTexture();
	void SetTexture(std::shared_ptr<Texture> texture);
	bool HasTexture() const;
	void SelectTexture();
};

