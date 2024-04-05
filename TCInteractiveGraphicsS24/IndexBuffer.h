#pragma once
#include <glad/glad.h> 
#include <iostream>
#include <vector>

class IndexBuffer
{
protected:
	unsigned int vioId;
	std::vector<unsigned short> indexData;
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
};

