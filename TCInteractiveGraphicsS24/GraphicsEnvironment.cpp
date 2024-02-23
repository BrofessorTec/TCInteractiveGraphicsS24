#include "GraphicsEnvironment.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iterator> 


GraphicsEnvironment::~GraphicsEnvironment()
{
    glfwTerminate();
}

GLFWwindow* GraphicsEnvironment::GetWindow()
{
    return window;
}

void GraphicsEnvironment::Init(unsigned int majorVersion, unsigned int minorVersion)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool GraphicsEnvironment::SetWindow(unsigned int width, unsigned int height, const std::string& title)
{
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (window == NULL) {
//		std::cout << "Failed to create GLFW window" << std::endl;
		Log("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	return true;
}

bool GraphicsEnvironment::InitGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		//std::cout << "Failed to initialize GLAD" << std::endl;
		Log("Failed to initialize GLAD");
		return false;
	}
	return true;
}

void GraphicsEnvironment::SetUpGraphics()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetFramebufferSizeCallback(window, OnWindowSizeChanged);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430");
}

void GraphicsEnvironment::OnWindowSizeChanged(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void GraphicsEnvironment::CreateRenderer(const std::string& name, std::shared_ptr<Shader> shader)
{
	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(shader);
	rendererMap.emplace(name, renderer);
}

std::shared_ptr<Renderer> GraphicsEnvironment::GetRenderer(const std::string& name)
{
	return rendererMap[name];
}

void GraphicsEnvironment::StaticAllocate()
{
	// unordered_map iterator created 
	// iterator pointing to start of unordered_map 
	std::unordered_map<std::string, std::shared_ptr<Renderer>>::iterator it
		= rendererMap.begin();

	for (const auto& pair : rendererMap) {
		std::string key = pair.first;
		std::shared_ptr<Renderer> renderer = pair.second;

		// Process key and renderer

		std::cout << "Key: " << key << ", Renderer: ";
		//renderer->AllocateVertexBuffers(renderer->GetScene()->GetObjects());
		renderer->AllocateVertexBuffers();
		std::cout << std::endl;
	}

}

void GraphicsEnvironment::Render()
{
	for (const auto& pair : rendererMap) {
		std::string key = pair.first;
		std::shared_ptr<Renderer> renderer = pair.second;

		// Process key and renderer
		std::cout << "Key: " << key << ", Renderer: ";
		renderer->RenderScene();
		std::cout << std::endl;
	}
}
