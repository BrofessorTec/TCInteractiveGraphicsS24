#pragma once
#include "BaseObject.h"
#include "Renderer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h> 
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>


class GraphicsEnvironment :
    public BaseObject
{
private: 
    GLFWwindow* window;
    std::unordered_map<std::string, std::shared_ptr<Renderer>> rendererMap;
public:
    ~GraphicsEnvironment();
    GLFWwindow* GetWindow();
    void Init(unsigned int majorVersion, unsigned int minorVersion);
    bool SetWindow(unsigned int width, unsigned int height, const std::string&
        title);
    bool InitGlad();
    void SetUpGraphics();
    static void OnWindowSizeChanged(GLFWwindow* window, int width, int height);
    void CreateRenderer(const std::string& name, std::shared_ptr<Shader>
        shader);
    std::shared_ptr<Renderer> GetRenderer(const std::string& name);
    void StaticAllocate();
    void Render();
    void ProcessInput(GLFWwindow* window);
    glm::mat4 CreateViewMatrix(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up);
    void Run2D();
    void Run3D();
    void EnableAttribute(int attribIndex, int elementCount, int sizeInBytes, void* offset);
};
