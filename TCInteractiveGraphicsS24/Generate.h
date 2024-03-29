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

    static std::shared_ptr<VertexBuffer> XZPlane(
        float width, float depth,
        glm::vec3 color = { 1.0f, 1.0f, 1.0f },
        glm::vec2 tex = { 1.0f, 1.0 });

    static std::shared_ptr<VertexBuffer> XYPlane(
        float width, float height,
        glm::vec3 color = { 1.0f, 1.0f, 1.0f },
        glm::vec2 tex = { 1.0f, 1.0 });

    static std::shared_ptr<VertexBuffer> CuboidNorm(
        float width, float height, float depth,
        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f },
        glm::vec3 normal = { 1.0f, 1.0f, 1.0f },
        glm::vec2 tex = { 1.0f, 1.0f });

    static std::shared_ptr<VertexBuffer> XZPlaneNorm(
        float width, float depth,
        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f},
        glm::vec3 normal = { 1.0f, 1.0f, 1.0f },
        glm::vec2 tex = { 1.0f, 1.0 });

    static std::shared_ptr<VertexBuffer> XYPlaneNorm(
        float width, float height,
        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f },
        glm::vec3 normal = { 1.0f, 1.0f, 1.0f },
        glm::vec2 tex = { 1.0f, 1.0 });
};

