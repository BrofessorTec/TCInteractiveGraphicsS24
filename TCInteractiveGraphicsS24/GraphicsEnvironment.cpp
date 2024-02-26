#include "GraphicsEnvironment.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iterator> 

struct VertexData {
	glm::vec3 position, color;
	glm::vec2 tex;
};


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

    // Cull back faces and use counter-clockwise winding of front faces
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);


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

void GraphicsEnvironment::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

glm::mat4 GraphicsEnvironment::CreateViewMatrix(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up)
{
	glm::vec3 right = glm::cross(direction, up);
	right = glm::normalize(right);

	glm::vec3 vUp = glm::cross(right, direction);
	vUp = glm::normalize(vUp);

	glm::mat4 view(1.0f);
	view[0] = glm::vec4(right, 0.0f);
	view[1] = glm::vec4(up, 0.0f);
	view[2] = glm::vec4(direction, 0.0f);
	view[3] = glm::vec4(position, 1.0f);
	return glm::inverse(view);
}

void GraphicsEnvironment::Run2D()
{

	glm::vec3 clearColor = { 0.2f, 0.3f, 0.3f };

	//glUseProgram(shader->GetShaderProgram());  // use new shaderProgram is this needed anymore?


	// added the io back here
	ImGuiIO& io = ImGui::GetIO();

	float angle = 0, childAngle = 0;
	float cameraX = -10, cameraY = 0;
	glm::mat4 view;


	while (!glfwWindowShouldClose(window)) {
		ProcessInput(window);

		// moved projection matrix calc to here
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		float aspectRatio = width / (height * 1.0f);

		float left = -50.0f;
		float right = 50.0f;
		float bottom = -50.0f;
		float top = 50.0f;
		left *= aspectRatio;
		right *= aspectRatio;
		glm::mat4 projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		view = CreateViewMatrix(
			glm::vec3(cameraX, cameraY, 1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		// Update the objects in the scene
		// should the update objects be in the render class?
		for (auto& object : GetRenderer("renderer1")->GetScene()->GetObjects()) {
			object->ResetOrientation();
			object->RotateLocalZ(angle);
			for (auto& child : object->GetChildren()) {
				child->ResetOrientation();
				child->RotateLocalZ(childAngle);
			}
		}

		//GetRenderer("renderer1")->SetScene(scene);
		GetRenderer("renderer1")->SetView(view);
		GetRenderer("renderer1")->SetProjection(projection);
		//GetRenderer("renderer2")->SetScene(textureScene);
		GetRenderer("renderer2")->SetView(view);
		GetRenderer("renderer2")->SetProjection(projection);


		//StaticAllocate();

		Render();


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Computing Interactive Graphics");
		//ImGui::Text(shader->GetLog().c_str());
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / io.Framerate, io.Framerate);
		ImGui::ColorEdit3("Background color", (float*)&clearColor.r);
		ImGui::SliderFloat("Angle", &angle, 0, 360);
		ImGui::SliderFloat("Child Angle", &childAngle, 0, 360);
		ImGui::SliderFloat("Camera X", &cameraX, left, right);
		ImGui::SliderFloat("Camera Y", &cameraY, bottom, top);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}


void GraphicsEnvironment::Run3D()
{
	/*
	std::shared_ptr<Texture> texture3d = std::make_shared<Texture>();
	texture3d->SetHeight(4);
	texture3d->SetWidth(4);


	// Create the texture data
	unsigned char* textureData = new unsigned char[] {
		0, 0, 0, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 0, 255,
			0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
			0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
			0, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 255
		};


	texture3d->SetTextureData(64, textureData);

	// Generate the texture id
	GLuint textureId;
	glGenTextures(1, &textureId);
	// Select the texture 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	// Apply texture parameters 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Send the texture to the GPU 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	// Generate mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);


	// trying to create graphics object here??
	//std::shared_ptr<GraphicsObject> graphicsObject3d = std::make_shared<GraphicsObject>();


	// Front face
	VertexData A = { {-5.0f, 5.0f, 5.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} };
	VertexData B = { {-5.0f,-5.0f, 5.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} };
	VertexData C = { { 5.0f,-5.0f, 5.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} };
	VertexData D = { { 5.0f, 5.0f, 5.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} };
	// Right face
	VertexData E = { { 5.0f, 5.0f, 5.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} };
	VertexData F = { { 5.0f,-5.0f, 5.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} };
	VertexData G = { { 5.0f,-5.0f,-5.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} };
	VertexData H = { { 5.0f, 5.0f,-5.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} };
	// Back face
	VertexData I = { { 5.0f, 5.0f,-5.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} };
	VertexData J = { { 5.0f,-5.0f,-5.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} };
	VertexData K = { {-5.0f,-5.0f,-5.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} };
	VertexData L = { {-5.0f, 5.0f,-5.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} };
	// Left face
	VertexData M = { {-5.0f, 5.0f,-5.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} };
	VertexData N = { {-5.0f,-5.0f,-5.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} };
	VertexData O = { {-5.0f,-5.0f, 5.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} };
	VertexData P = { {-5.0f, 5.0f, 5.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} };
	// Top face
	VertexData Q = { {-5.0f, 5.0f,-5.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} };
	VertexData R = { {-5.0f, 5.0f, 5.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} };
	VertexData S = { { 5.0f, 5.0f, 5.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} };
	VertexData T = { { 5.0f, 5.0f,-5.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} };
	// Bottom face
	VertexData U = { { 5.0f,-5.0f,-5.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} };
	VertexData V = { { 5.0f,-5.0f, 5.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} };
	VertexData W = { {-5.0f,-5.0f, 5.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} };
	VertexData X = { {-5.0f,-5.0f,-5.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} };

	// 3 vertex per triangle, 2 triangles per face, 6 faces
	// 3 * 2 * 6 = 36 vertices
	VertexData vertexData[36]{
		// Front face
		A, B, C, A, C, D,
		// Right face
		E, F, G, E, G, H,
		// Back face
		I, J, K, I, K, L,
		// Left face
		M, N, O, M, O, P,
		// Top face
		Q, R, S, Q, S, T,
		// Bottom face
		U, V, W, U, W, X
	};

	
	*/

	unsigned int vaoId, vboId;
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	

	ImGuiIO& io = ImGui::GetIO();

	float cubeYAngle = 0;
    float cubeXAngle = 0;
	float cubeZAngle = 0;
	float left = -20.0f;
	float right = 20.0f;
	float bottom = -20.0f;
	float top = 20.0f;
	int width, height;

	//std::string message = result.message;

	float aspectRatio;
	float nearPlane = 1.0f;
	float farPlane = 50.0f;
	float fieldOfView = 60;

	glm::vec3 cameraPosition(15.0f, 15.0f, 20.0f);
	glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 referenceFrame(1.0f);
	glm::vec3 clearColor = { 0.2f, 0.3f, 0.3f };

	while (!glfwWindowShouldClose(window)) {
		ProcessInput(window);
		glfwGetWindowSize(window, &width, &height);

		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		referenceFrame = glm::rotate(glm::mat4(1.0f), glm::radians(cubeYAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		referenceFrame = glm::rotate(referenceFrame, glm::radians(cubeXAngle), glm::vec3(1.0f, 0.0f, 0.0f));
		referenceFrame = glm::rotate(referenceFrame, glm::radians(cubeZAngle), glm::vec3(0.0f, 0.0f, 1.0f));

		view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

		if (width >= height) {
			aspectRatio = width / (height * 1.0f);
		}
		else {
			aspectRatio = height / (width * 1.0f);
		}
		projection = glm::perspective(
			glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);

		// Render the object
		//if (result.isSuccess) comment out since no result object anymore?
		//{
			unsigned int shaderProgram = GetRenderer("renderer3d")->GetShader()->GetShaderProgram();
			glUseProgram(shaderProgram);
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "worldLoc"), 1, GL_FALSE, glm::value_ptr(referenceFrame));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewLoc"), 1, GL_FALSE, glm::value_ptr(view));
			glBindVertexArray(vaoId);
			glBindBuffer(GL_ARRAY_BUFFER, vboId);
			// Positions
			EnableAttribute(0, 3, sizeof(VertexData), (void*)0);
			// Colors
			EnableAttribute(1, 3, sizeof(VertexData), (void*)sizeof(glm::vec3));
			// Texture Coords
			EnableAttribute(2, 2, sizeof(VertexData), (void*)(sizeof(glm::vec3) * 2));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureId);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glUseProgram(0);
			glBindVertexArray(0);
		//}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Computing Interactive Graphics");
		//ImGui::Text(message.c_str());  no result object anymore?
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / io.Framerate, io.Framerate);
		ImGui::ColorEdit3("Background color", (float*)&clearColor.r);
		ImGui::SliderFloat("X Angle", &cubeXAngle, 0, 360);
		ImGui::SliderFloat("Y Angle", &cubeYAngle, 0, 360);
		ImGui::SliderFloat("Z Angle", &cubeZAngle, 0, 360);
		ImGui::SliderFloat("Camera X", &cameraPosition.x, left, right);
		ImGui::SliderFloat("Camera Y", &cameraPosition.y, bottom, top);
		ImGui::SliderFloat("Camera Z", &cameraPosition.z, 20, 50);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();

}

void GraphicsEnvironment::EnableAttribute(int attribIndex, int elementCount, int sizeInBytes, void* offset)
{
	glEnableVertexAttribArray(attribIndex);
	glVertexAttribPointer(
		attribIndex,
		elementCount,
		GL_FLOAT,
		GL_FALSE,
		sizeInBytes, // The number of bytes to the next element
		offset       // Byte offset of the first position in the array
	);
}

