#include "IndexBuffer.h"
#include <cstdarg>

IndexBuffer::IndexBuffer()//:indexData() //unsigned int numElementsPerVertex removed from input parameter
{
	//numberOfIndexes = 0;
	//primitiveType = GL_LINES;
	glGenBuffers(1, &vioId);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &vioId);
}


std::vector<unsigned short>& IndexBuffer::GetIndexData()
{
    return indexData;
}

int IndexBuffer::GetIndexCount()
{
    return indexData.size();  //is this correct?
}

void IndexBuffer::AddIndexData(unsigned int count, ...)
{
	//indexData.clear();
	/*if (count != numberOfElementsPerVertex) {
		throw "Invalid index data count!";
	}
	*/
	va_list args;
	va_start(args, count);
	while (count > 0) {
		// The default is double, so accept as double and then cast to
		// unsigned short.
		indexData.push_back(static_cast<unsigned short>(va_arg(args, int)));
		count--;
	}
	//numberOfIndexes++;
	va_end(args);
}

void IndexBuffer::AddIndexData(unsigned short index)
{
	//is this code completed?
	indexData.push_back(index);
	//numberOfIndexes++;
}

void IndexBuffer::StaticAllocate()
{
	unsigned long long bytesToAllocate = indexData.size() * sizeof(unsigned short);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, bytesToAllocate, indexData.data(), GL_STATIC_DRAW);
}
