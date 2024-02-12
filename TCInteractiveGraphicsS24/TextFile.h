#pragma once
#include "BaseObject.h"
#include <sstream>
#include <string>
#include <iostream>


class TextFile :
    public BaseObject
{

private:
    std::stringstream ss;
    std::string data;

public:
    TextFile();

    void ReadFile(std::string filePath);

    void Trim(std::string& str);

    const std::string& GetString() const;
};


