#include "Texture.h"
#include "glad/glad.h"

/*
void Texture::SetTextureData(unsigned int count, unsigned char* data)
{
	textureData = new unsigned char[count];
	memcpy(data, textureData, count);
}
*/

Texture::Texture()
{
	textureData = nullptr;
	glGenTextures(1, &textureId);
}


void Texture::SetTextureData(unsigned int count, unsigned char* data)
{
	CleanUp();
	textureData = new unsigned char[count];
	memcpy(data, textureData, count);
	isLoadedFromFile = false;
}

bool Texture::IsLoadedFromFile()
{
	return isLoadedFromFile;
}

unsigned int Texture::TextureId()
{
	return textureId;
}

Texture::~Texture()
{
	CleanUp();
}

unsigned char* Texture::GetTextureData()
{
	return textureData;
}

void Texture::CleanUp()
{
	if (textureData == nullptr)
	{
		return;
	}
	if (!isLoadedFromFile)
	{
		delete[] textureData;
	}

	textureData = nullptr;
}
