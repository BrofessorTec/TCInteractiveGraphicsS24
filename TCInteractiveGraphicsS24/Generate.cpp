#include "Generate.h"

std::shared_ptr<VertexBuffer> Generate::Cuboid(float width, float height, float depth, glm::vec3 color, glm::vec2 tex)
{
    // 2.1.Parameter tex specifies the repeat value for s and t.
    // 2.2.It creates a vertex buffer, fills it with vertex data based on the arguments, and then
    //    returns it.
    
    std::shared_ptr<VertexBuffer> vertexBuffer3d = std::make_shared<VertexBuffer>(8);

	// front face  with 6 vertices and no indexed buffer?
	vertexBuffer3d->AddVertexData(8, -width / 2, height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
	vertexBuffer3d->AddVertexData(8, -width / 2, -height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, -height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, -width / 2, height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, -height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);

    // right face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, width / 2, height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, -height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, -height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, -height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);

    // back face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, width / 2, height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, -height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, -width / 2, -height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, -width / 2, -height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, -width / 2, height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);

    // left face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, -width / 2, height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, -width / 2, -height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, -width / 2, -height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, -width / 2, height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, -width / 2, -height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, -width / 2, height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);

    // top face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, -width / 2, height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, -width / 2, height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, -width / 2, height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);

    // bottom face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, width / 2, -height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, -height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, -width / 2, -height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, width / 2, -height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, -width / 2, -height / 2, depth / 2, color[0], color[1], color[2], tex[0], tex[1]);
    vertexBuffer3d->AddVertexData(8, -width / 2, -height / 2, -depth / 2, color[0], color[1], color[2], tex[0], tex[1]);


    return vertexBuffer3d;
}
