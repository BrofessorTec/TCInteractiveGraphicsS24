#include "Renderer.h"
#include "Shader.h"
#include <glad/glad.h> 
#include "GraphicsObject.h"
#include "Scene.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VertexBuffer.h"

/*
Renderer::Renderer(std::shared_ptr<Shader> shader)
{
	this->shader = shader;
	glGenVertexArrays(1, &vaoId);
}

void Renderer::AllocateVertexBuffers(const auto& objects)
{
    glBindVertexArray(vaoId);
    for (auto& object : objects) {
        object->StaticAllocateVertexBuffer();
    }
    glBindVertexArray(0);
}


void Renderer::RenderObject(const GraphicsObject& object)
{
    shader->SendMat4Uniform("world", object.GetReferenceFrame());

    auto& buffer = object.GetVertexBuffer();
    buffer->Select();
    buffer->SetUpAttributeInterpretration();
    glDrawArrays(buffer->GetPrimitiveType(), 0, buffer->GetNumberOfVertices());

    // Recursively render the children
    auto& children = object.GetChildren();
    for (auto& child : children) {
        RenderObject(*child);
    }
}

void Renderer::RenderScene(std::shared_ptr<Scene> scene, glm::mat4 view)
{
    if (shader->IsCreated()) {
        glUseProgram(shader->GetShaderProgram());
        glBindVertexArray(vaoId);
        //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        shader->SendMat4Uniform("view", view);
        // Render the objects in the scene
        for (auto& object : scene->GetObjects()) {
            RenderObject(*object);
        }
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glUseProgram(0);
        glBindVertexArray(0);
    }
}
*/