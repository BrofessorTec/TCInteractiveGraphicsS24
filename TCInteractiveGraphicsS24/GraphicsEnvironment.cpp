#include "GraphicsEnvironment.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iterator> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


GraphicsEnvironment* GraphicsEnvironment::self;

struct VertexData {
	glm::vec3 position, color;
	glm::vec2 tex;
};


GraphicsEnvironment::~GraphicsEnvironment()
{
    glfwTerminate();
}

GraphicsEnvironment::GraphicsEnvironment()
{
	window = nullptr;
	objManager = std::make_shared<ObjectManager>();
	camera = std::make_shared<Camera>();
	self = this;
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
	glfwWindowHint(GLFW_SAMPLES, 4);
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
	// on mouse move callback
	glfwSetCursorPosCallback(window, OnMouseMove);
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

	glEnable(GL_MULTISAMPLE);
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
	/*
	for (const auto& pair : rendererMap) {
		std::string key = pair.first;
		std::shared_ptr<Renderer> renderer = pair.second;

		// Process key and renderer

		std::cout << "Key: " << key << ", Renderer: ";
		renderer->AllocateVertexBuffers();
		std::cout << std::endl;
	}
	*/


	for (const auto& [name, renderer] : rendererMap) {
		renderer->AllocateVertexBuffers();
	}

}

void GraphicsEnvironment::Render()
{
	/*
	for (const auto& pair : rendererMap) {
		std::string key = pair.first;
		std::shared_ptr<Renderer> renderer = pair.second;

		// Process key and renderer
		std::cout << "Key: " << key << ", Renderer: ";
		renderer->RenderScene();
		std::cout << std::endl;
	}*/

	for (const auto& [name, renderer] : rendererMap) {
		renderer->RenderScene(*camera);  //is this the right syntax?
	}

}

void GraphicsEnvironment::ProcessInput(GLFWwindow* window, double elapsedSeconds)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->MoveForward(elapsedSeconds);
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera->MoveLeft(elapsedSeconds);
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera->MoveBackward(elapsedSeconds);
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera->MoveRight(elapsedSeconds);
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		camera->MoveUp(elapsedSeconds);
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		camera->MoveDown(elapsedSeconds);
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS) {
		lookWithMouse = !lookWithMouse;
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		camera->SetLookFrame(glm::mat4(1.0f));
		camera->SetPosition(glm::vec3(0.0f, 5.0f, 30.0f));
		lookWithMouse = false;
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		glm::mat4 look(1.0f);
		look = glm::rotate(look, glm::radians(90.0f), { 0, 1, 0 });
		camera->SetLookFrame(look);
		camera->SetPosition(glm::vec3(30.0f, 5.0f, 0.0f));
		lookWithMouse = false;
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		glm::mat4 look(1.0f);
		look = glm::rotate(look, glm::radians(180.0f), { 0, 1, 0 });
		camera->SetLookFrame(look);
		camera->SetPosition(glm::vec3(0.0f, 5.0f, -30.0f));
		lookWithMouse = false;
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		glm::mat4 look(1.0f);
		look = glm::rotate(look, glm::radians(-90.0f), { 0, 1, 0 });
		camera->SetLookFrame(look);
		camera->SetPosition(glm::vec3(-30.0f, 5.0f, 0.0f));
		lookWithMouse = false;
		return;
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

	Timer timer;
	double elapsedSeconds;


	while (!glfwWindowShouldClose(window)) {
		elapsedSeconds = timer.GetElapsedTimeInSeconds();
		ProcessInput(window, elapsedSeconds);

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
	float farPlane = 100.0f;
	float fieldOfView = 60;

	//glm::vec3 cameraPosition(15.0f, 15.0f, 20.0f);
	glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
	//glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 referenceFrame(1.0f);
	glm::vec3 clearColor = { 0.2f, 0.3f, 0.3f };
	camera->SetPosition(glm::vec3(0.0f, 3.0f, 30.0f));


	//bool lookWithMouse = false;
	bool resetCameraPosition = false;
	double elapsedSeconds;
	Timer timer;
	bool correctGamma = false;

	// add animation
	std::shared_ptr<RotateAnimation> rotateAnimation =
		std::make_shared<RotateAnimation>();
	rotateAnimation->SetObject(objManager->GetObject("Crate"));
	objManager->GetObject("Crate")->SetAnimation(rotateAnimation);


	while (!glfwWindowShouldClose(window)) {
		elapsedSeconds = timer.GetElapsedTimeInSeconds();
		ProcessInput(window, elapsedSeconds);
		glfwGetWindowSize(window, &width, &height);
		// set mouse parameters
		mouse.windowWidth = width;
		mouse.windowHeight = height;

		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		referenceFrame = glm::rotate(glm::mat4(1.0f), glm::radians(cubeYAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		referenceFrame = glm::rotate(referenceFrame, glm::radians(cubeXAngle), glm::vec3(1.0f, 0.0f, 0.0f));
		referenceFrame = glm::rotate(referenceFrame, glm::radians(cubeZAngle), glm::vec3(0.0f, 0.0f, 1.0f));

		//view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

		// mouse settings
		if (resetCameraPosition) {
			camera->SetLookFrame(glm::mat4(1.0f));
			camera->SetPosition(glm::vec4(0.0f, 3.0f, 20.0f, 1.0f));
			resetCameraPosition = false;
			lookWithMouse = false;
		}
		if (lookWithMouse) {
			camera->SetLookFrame(mouse.spherical.ToMat4());
		}

		// gamma correction
		if (correctGamma) {
			glEnable(GL_FRAMEBUFFER_SRGB);
		}
		else {
			glDisable(GL_FRAMEBUFFER_SRGB);
		}


		// set camera look frame to be mouse speherical
		//camera->SetLookFrame(self->mouse.spherical.ToMat4());

		view = camera->LookForward();
		//view = camera->LookAtTarget(glm::vec3(self->mouse.spherical.ToMat4()[3]));

		if (width >= height) {
			aspectRatio = width / (height * 1.0f);
		}
		else {
			aspectRatio = height / (width * 1.0f);
		}
		projection = glm::perspective(
			glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);

		// Update the objects in the scene
		// commenting this out so the animation works correctly
		/*
		for (auto& object : GetRenderer("renderer3d")->GetScene()->GetObjects()) {
			object->ResetOrientation();
			object->RotateLocalX(cubeXAngle);
			object->RotateLocalY(cubeYAngle);
			object->RotateLocalZ(cubeZAngle);
		}*/


		GetRenderer("renderer3d")->SetView(view);
		GetRenderer("renderer3d")->SetProjection(projection);

		// call update
		objManager->Update(elapsedSeconds);

		Render();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Computing Interactive Graphics");
		//ImGui::Text(message.c_str());  no result object anymore?
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / io.Framerate, io.Framerate);
		ImGui::ColorEdit3("Background color", (float*)&clearColor.r);
		//ImGui::SliderFloat("X Angle", &cubeXAngle, 0, 360);  // commenting these out so the animation works correctly
		//ImGui::SliderFloat("Y Angle", &cubeYAngle, 0, 360);
		//ImGui::SliderFloat("Z Angle", &cubeZAngle, 0, 360);

		//ImGui::SliderFloat("Camera X", &cameraPosition.x, left, right);
		//ImGui::SliderFloat("Camera Y", &cameraPosition.y, bottom, top);
		//ImGui::SliderFloat("Camera Z", &cameraPosition.z, 20, 50);

		ImGui::SliderFloat("Global Intensity", &GetRenderer("renderer3d")->GetScene()->GetGlobalLight().intensity, 0, 1);
		ImGui::SliderFloat("Local Intensity", &GetRenderer("renderer3d")->GetScene()->GetLocalLight().intensity, 0, 1);
		//ImGui::SliderFloat("Local Attenuation ", &GetRenderer("renderer3d")->GetScene()->GetLocalLight().attenuationCoef, 0, 1);
		//ImGui::SliderFloat("Specular Cube", &objManager->GetObject("cube")->GetMaterial().specularIntensity, 0, 1);
		//ImGui::SliderFloat("Shininess Cube", &objManager->GetObject("cube")->GetMaterial().shininess, 0, 100);
		//ImGui::SliderFloat("Ambient Intensity Cube", &objManager->GetObject("cube")->GetMaterial().ambientIntensity, 0, 1);
		//ImGui::SliderFloat("Specular Crate", &objManager->GetObject("Crate")->GetMaterial().specularIntensity, 0, 1);
		//ImGui::SliderFloat("Shininess Crate", &objManager->GetObject("Crate")->GetMaterial().shininess, 0, 100);
		//ImGui::SliderFloat("Ambient Intensity Crate", &objManager->GetObject("Crate")->GetMaterial().ambientIntensity, 0, 1);
		//ImGui::SliderFloat("Specular Floor", &objManager->GetObject("floor")->GetMaterial().specularIntensity, 0, 1);
		//ImGui::SliderFloat("Shininess Floor", &objManager->GetObject("floor")->GetMaterial().shininess, 0, 100);
		//ImGui::SliderFloat("Ambient Intensity Floor", &objManager->GetObject("floor")->GetMaterial().ambientIntensity, 0, 1);

		// add a slider for box animation speed 
		ImGui::SliderFloat("Animation Speed", &rotateAnimation->GetSpeed(), -360, 360);
		ImGui::Checkbox("Correct gamma", &correctGamma);
		ImGui::Checkbox("Use mouse to look", &this->lookWithMouse);
		ImGui::Checkbox("Reset camera position", &resetCameraPosition);
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

void GraphicsEnvironment::AddObject(const std::string name, std::shared_ptr<GraphicsObject> object)
{
	// does the objManager need to be declared as a shared pointer somewhere..?
	objManager->SetObject(name, object);
}

std::shared_ptr<Camera> GraphicsEnvironment::GetCamera()
{
	return camera;
}

void GraphicsEnvironment::OnMouseMove(GLFWwindow* window, double mouseX, double mouseY)
{
	self->mouse.x = mouseX;
	self->mouse.y = mouseY;

	float xPercent = static_cast<float>(self->mouse.x / self->mouse.windowWidth);
	float yPercent = static_cast<float>(self->mouse.y / self->mouse.windowHeight);

	self->mouse.spherical.theta = 90.0f - (xPercent * 180); // left/right
	self->mouse.spherical.phi = 180.0f - (yPercent * 180); // up/down
}


