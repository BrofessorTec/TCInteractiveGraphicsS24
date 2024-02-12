#pragma once
#include "BaseObject.h"

class Texture :
    public BaseObject
{
private:
    unsigned char* textureData;
    bool isLoadedFromFile = false;
    unsigned int textureId;
public:
    Texture();
    ~Texture();  //calls cleanup
    unsigned char* GetTextureData();
    void SetTextureData(unsigned int count, unsigned char* data);
    bool IsLoadedFromFile();
    unsigned int TextureId();
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
