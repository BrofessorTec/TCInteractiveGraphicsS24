#include "Texture.h"
#include "glad/glad.h"

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

unsigned int Texture::GetTextureId()
{
	return textureId;
}

Texture::~Texture()
{
	CleanUp();
	glDeleteTextures(1, &textureId);
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

void Texture::SetWidth(unsigned int width)
{
	this->width = width;
}

void Texture::SetHeight(unsigned int height)
{
	this->height = height;
}

void Texture::SelectToChange()
{
	glBindTexture(type, textureId);
}

void Texture::Deselect()
{
	glBindTexture(type, 0);
}

void Texture::SelectToRender(int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(type, textureId);
}

void Texture::Allocate()
{
	SelectToChange();
	// Apply texture parameters 
	glTexParameteri(type, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, minFilter);
	// Send the texture to the GPU 
	glTexImage2D(type, 0, internalFormat, width, height, 0, sourceFormat, GL_UNSIGNED_BYTE, textureData);
	CleanUp();
	// Generate mipmaps
	glGenerateMipmap(type);
	Deselect();

}
