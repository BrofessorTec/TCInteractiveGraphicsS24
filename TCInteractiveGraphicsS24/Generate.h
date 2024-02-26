#pragma once
#include "BaseObject.h"
#include "VertexBuffer.h"
class Generate :
    public BaseObject
{
public: 
    static std::shared_ptr<VertexBuffer> Cuboid(
        float width, float height, float depth,
        glm::vec3 color = { 1.0f, 1.0f, 1.0f },
        glm::vec2 tex = { 1.0f, 1.0f });
};

