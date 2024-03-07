#include "Generate.h"

std::shared_ptr<VertexBuffer> Generate::Cuboid(float width, float height, float depth, glm::vec3 color, glm::vec2 tex)
{
    // 2.1.Parameter tex specifies the repeat value for s and t.
    // 2.2.It creates a vertex buffer, fills it with vertex data based on the arguments, and then
    //    returns it.
    
    std::shared_ptr<VertexBuffer> vertexBuffer3d = std::make_shared<VertexBuffer>(8);

    float halfWidth = width / 2;
    float halfHeight = height / 2;
    float halfDepth = depth / 2;


	// front face  with 6 vertices and no indexed buffer?
	vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0, tex.t);
	vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0, 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0, tex.t);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, tex.s, tex.t);

    // right face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0, 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], tex[1]);

    // back face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color[2], 0, 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], tex[0], tex[1]);

    // left face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color[2], 0, 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color[0], color[1], color[2], tex[0], tex[1]);

    // top face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color[0], color[1], color[2], 0, 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], tex[0], tex[1]);

    // bottom face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color[0], color[1], color[2], 0, 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color[2], tex[0], tex[1]);


    return vertexBuffer3d;
}

std::shared_ptr<VertexBuffer> Generate::XZPlane(float width, float depth, glm::vec3 color, glm::vec2 tex)
{
    std::shared_ptr<VertexBuffer> vertexBufferFloor = std::make_shared<VertexBuffer>(8);
    float halfWidth = width / 2;
    float halfDepth = depth / 2;

    // top face  with 6 vertices and no indexed buffer?
    vertexBufferFloor->AddVertexData(8, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, 0, tex.t);
    vertexBufferFloor->AddVertexData(8, -halfWidth, 0, halfDepth, color.r, color.g, color.b, 0, 0);
    vertexBufferFloor->AddVertexData(8, halfWidth, 0, halfDepth, color.r, color.g, color.b, tex.s, 0);
    vertexBufferFloor->AddVertexData(8, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, 0, tex.t);
    vertexBufferFloor->AddVertexData(8, halfWidth, 0, halfDepth, color.r, color.g, color.b, tex.s, 0);
    vertexBufferFloor->AddVertexData(8, halfWidth, 0, -halfDepth, color.r, color.g, color.b, tex.s, tex.t);

    // bottom face  with 6 vertices and no indexed buffer?
    vertexBufferFloor->AddVertexData(8, halfWidth, 0, -halfDepth, color.r, color.g, color.b, 0, tex.t);
    vertexBufferFloor->AddVertexData(8, halfWidth, 0, halfDepth, color.r, color.g, color.b, 0, 0);
    vertexBufferFloor->AddVertexData(8, -halfWidth, 0, halfDepth, color.r, color.g, color.b, tex.s, 0);
    vertexBufferFloor->AddVertexData(8, halfWidth, 0, -halfDepth, color.r, color.g, color.b, 0, tex.t);
    vertexBufferFloor->AddVertexData(8, -halfWidth, 0, halfDepth, color.r, color.g, color.b, tex.s, 0);
    vertexBufferFloor->AddVertexData(8, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, tex.s, tex.t);

    return vertexBufferFloor;
}

std::shared_ptr<VertexBuffer> Generate::CuboidNorm(float width, float height, float depth, glm::vec4 color, glm::vec3 normal, glm::vec2 tex)
{

    std::shared_ptr<VertexBuffer> vertexBuffer3d = std::make_shared<VertexBuffer>(12);

    float halfWidth = width / 2;
    float halfHeight = height / 2;
    float halfDepth = depth / 2;


    // front face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], 0, tex.t);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], 0, 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], tex.s, 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], 0, tex.t);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], tex.s, 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], tex.s, tex.t);

    // right face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], 0, 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], tex[0], tex[1]);

    // back face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], 0, 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], tex[0], tex[1]);

    // left face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], 0, 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], tex[0], tex[1]);

    // top face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], 0, 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], tex[0], tex[1]);

    // bottom face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], 0, 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, normal[0], normal[1], normal[2], tex[0], tex[1]);


    return vertexBuffer3d;
}

std::shared_ptr<VertexBuffer> Generate::XZPlaneNorm(float width, float depth, glm::vec4 color, glm::vec3 normal, glm::vec2 tex)
{
    std::shared_ptr<VertexBuffer> vertexBufferFloor = std::make_shared<VertexBuffer>(12);
    float halfWidth = width / 2;
    float halfDepth = depth / 2;

    // top face  with 6 vertices and no indexed buffer?
    vertexBufferFloor->AddVertexData(12, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], 0, tex.t);
    vertexBufferFloor->AddVertexData(12, -halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], 0, 0);
    vertexBufferFloor->AddVertexData(12, halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], tex.s, 0);
    vertexBufferFloor->AddVertexData(12, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], 0, tex.t);
    vertexBufferFloor->AddVertexData(12, halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], tex.s, 0);
    vertexBufferFloor->AddVertexData(12, halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], tex.s, tex.t);

    // bottom face  with 6 vertices and no indexed buffer?
    vertexBufferFloor->AddVertexData(12, halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], 0, tex.t);
    vertexBufferFloor->AddVertexData(12, halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], 0, 0);
    vertexBufferFloor->AddVertexData(12, -halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], tex.s, 0);
    vertexBufferFloor->AddVertexData(12, halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], 0, tex.t);
    vertexBufferFloor->AddVertexData(12, -halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], tex.s, 0);
    vertexBufferFloor->AddVertexData(12, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, normal[0], normal[1], normal[2], tex.s, tex.t);

    return vertexBufferFloor;
}

