#pragma once
#include "BaseObject.h"
/*#include "glm/glm.hpp"
#include "glfw/glfw3.h"
#include "glad/glad.h"
*/

class Texture :
    public BaseObject
{
private:
    unsigned char* textureData;
    bool isLoadedFromFile = false;
    unsigned int textureId;
    unsigned int type = GL_TEXTURE_2D;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int internalFormat = GL_RGBA8;
    unsigned int sourceFormat = GL_RGBA;
    unsigned int wrapS = GL_REPEAT;
    unsigned int wrapT = GL_REPEAT;
    unsigned int magFilter = GL_NEAREST;
    unsigned int minFilter = GL_NEAREST;
public:
    Texture();
    ~Texture();  //calls cleanup
    unsigned char* GetTextureData();
    void SetTextureData(unsigned int count, unsigned char* data);
    bool IsLoadedFromFile();
    unsigned int GetTextureId();
    void SetWidth(unsigned int width);
    void SetHeight(unsigned int height);
    void SelectToChange();
    void Deselect();
    void SelectToRender(int textureUnit = 0);
    void Allocate();
private:
    void CleanUp();
};


/*
class Texture :
    public BaseObject
{
private:
    unsigned char* textureData = nullptr;
    // need a cleanup for textureData if not equal to nullptr using Delete[]?

public:
    void SetTextureData(unsigned int count, unsigned char* data);

};
*/
