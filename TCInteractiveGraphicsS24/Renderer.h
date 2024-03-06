#pragma once
#include "BaseObject.h"
#include "Shader.h"
#include <glad/glad.h> 
#include "GraphicsObject.h"
#include "Scene.h"
#include "Camera.h"


class Renderer :
    public BaseObject
{
private:
        std::shared_ptr<Shader> shader;
        unsigned int vaoId;
        std::shared_ptr<Scene> scene;
        glm::mat4 view;
        glm::mat4 projection;

public:
    Renderer(std::shared_ptr<Shader> shader2)
    {
        shader = shader2;
        glGenVertexArrays(1, &vaoId);
    }
    inline const std::shared_ptr<Shader>& GetShader() const { return shader; }
    std::shared_ptr<Scene> GetScene()
    {
        return scene;
    }
    void SetScene(std::shared_ptr<Scene> sceneNew)
    {
        scene = sceneNew;
    }
    void SetView(glm::mat4 viewNew)
    {
        view = viewNew;
    }
    void SetProjection(glm::mat4 projection2)
    {
        projection = projection2;
    }
    /*void AllocateVertexBuffers(const auto& objects)
    {
        glBindVertexArray(vaoId);
        for (auto& object : objects) {
            object->StaticAllocateVertexBuffer();
        }
        glBindVertexArray(0);
    }*/
    
    // testing this to remove the need to pass in the objects parameter but still getting a crash
    void AllocateVertexBuffers() 
    {
        std::vector<std::shared_ptr<GraphicsObject>> objects = scene->GetObjects();
        glBindVertexArray(vaoId);
        for (auto& object : objects) {
            object->StaticAllocateVertexBuffer();
        }
        glBindVertexArray(0);
    }
    
    void RenderScene(Camera& camera)
    {
        if (shader->IsCreated()) {
            glUseProgram(shader->GetShaderProgram());
            glBindVertexArray(vaoId);
            //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            shader->SendMat4Uniform("view", view);
            shader->SendMat4Uniform("projection", projection);
            shader->SendVec3Uniform("cameraPos", glm::value_ptr(camera)->GetPosition());  // need to fix this
            shader->SendFloatUniform("globalLightAttenuation", scene->GetGlobalLight().attenuationCoef);
            shader->SendFloatUniform("localLightAttenuation", scene->GetLocalLight().attenuationCoef);
            shader->SendFloatUniform("globalLightIntensity", scene->GetGlobalLight().intensity);
            shader->SendFloatUniform("localLightIntensity", scene->GetLocalLight().intensity);
            shader->SendVec3Uniform("globalLightColor", scene->GetGlobalLight().color);
            shader->SendVec3Uniform("localLightColor", scene->GetLocalLight().color);
            shader->SendVec3Uniform("globalLightPos", scene->GetGlobalLight().position);
            shader->SendVec3Uniform("localLightPos", scene->GetLocalLight().position);


            /* values needed from the notes
            glUniform3fv(globalLightPosLoc, 1, glm::value_ptr(globalLight.position));
            glUniform3fv(globalLightColorLoc, 1, glm::value_ptr(globalLight.color));
            glUniform1f(globalLightIntensityLoc, globalLight.intensity);
            glUniform3fv(localLightPosLoc, 1, glm::value_ptr(localLight.position));
            glUniform3fv(localLightColorLoc, 1, glm::value_ptr(localLight.color));
            glUniform1f(localLightIntensityLoc, localLight.intensity);
            glUniform1f(localLightAttentuationLoc, localLight.attenuationCoef);
            glUniform3fv(viewPositionLoc, 1, glm::value_ptr(cameraPosition));
            
            
            */


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
private:
    void RenderObject(const GraphicsObject& object)
    {
        shader->SendMat4Uniform("world", object.GetReferenceFrame());

        auto& buffer = object.GetVertexBuffer();
        buffer->Select();
        if (buffer->HasTexture())
        {
            shader->SendIntUniform("texUnit", buffer->GetTextureUnit());
            buffer->GetTexture()->SelectToRender();
        }
        buffer->SetUpAttributeInterpretration();
        glDrawArrays(buffer->GetPrimitiveType(), 0, buffer->GetNumberOfVertices());

        // Recursively render the children
        auto& children = object.GetChildren();
        for (auto& child : children) {
            RenderObject(*child);
        }
    }
}; 


/*
class Renderer :
    public BaseObject
{
private:
    std::shared_ptr<Shader> shader;
    unsigned int vaoId;

public:
    Renderer(std::shared_ptr<Shader> shader);
    inline const std::shared_ptr<Shader>& GetShader() const { return shader; }
    void AllocateVertexBuffers(const auto& objects);
    void RenderScene(std::shared_ptr<Scene> scene, glm::mat4 view);
private:
    void RenderObject(const GraphicsObject& object);
};*/

