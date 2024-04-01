#pragma once
#include <glad/glad.h> 
#include <iostream>
#include <vector>

/*struct VertexAttribute {   //might need to change this
	unsigned int index;
	unsigned int numberOfComponents;
	int type;
	int isNormalized;
	unsigned int bytesToNext;
	void* byteOffset;
};*/

class IndexBuffer
{
protected:
	unsigned int vioId;
	std::vector<unsigned short> indexData;
	//unsigned int numberOfElementsPerVertex; //needed?
	unsigned int numberOfIndexes;
	//int primitiveType;
public:
	IndexBuffer(); //removed numberofelementspervertex
	~IndexBuffer();
	inline void Select() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vioId); }
	inline void Deselect() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
	std::vector<unsigned short>& GetIndexData();
	int GetIndexCount();
	void AddIndexData(unsigned int count, ...);
	void AddIndexData(unsigned short index);
	void StaticAllocate();
	static void LineCircleIndexes(
		std::shared_ptr<IndexBuffer>& bufferToFill,
		int numberOfLineSegments, bool isClosed = true);
	//int GetPrimitiveType();
};

