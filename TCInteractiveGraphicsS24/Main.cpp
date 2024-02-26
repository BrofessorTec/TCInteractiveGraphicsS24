#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VertexBuffer.h"
#include "GraphicsObject.h"
#include "Scene.h"
#include "Shader.h"
#include "Renderer.h"
#include "TextFile.h"
#include "Texture.h"
#include "GraphicsEnvironment.h"


static void SetUp3DScene1(std::shared_ptr<Shader>& shader3d,
	std::shared_ptr<Scene>& scene3d)
{

	struct VertexData {
		glm::vec3 position, color;
		glm::vec2 tex;
	};


	std::string vertexSource =
		"#version 430\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec3 color;\n"
		"layout(location = 2) in vec2 texCoord;\n"
		"out vec4 fragColor;\n"
		"out vec2 fragTexCoord;\n"
		"uniform mat4 world;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = projection * view * world * vec4(position, 1.0);\n"
		"   fragColor = vec4(color, 1.0);\n"
		"   fragTexCoord = texCoord;\n"
		"}\n";

	std::string fragmentSource =
		"#version 430\n"
		"in vec4 fragColor;\n"
		"in vec2 fragTexCoord;\n"
		"out vec4 color;\n"
		"uniform sampler2D tex;\n"
		"void main()\n"
		"{\n"
		"   vec4 texFragColor = texture(tex, fragTexCoord) * fragColor;\n"
		"   color = texFragColor;\n"
		"}\n";

	shader3d = std::make_shared<Shader>(vertexSource, fragmentSource);

	shader3d->AddUniform("projection");
	shader3d->AddUniform("world");
	shader3d->AddUniform("view");
	shader3d->AddUniform("texUnit");

	unsigned int shaderProgram = shader3d->GetShaderProgram();


	// Get the uniform locations
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	unsigned int worldLoc = glGetUniformLocation(shaderProgram, "world");


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






	scene3d = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> graphicsObject3d = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> vertexBuffer3d = std::make_shared<VertexBuffer>(8);

	// front face? or is this totally wrong now
	/*
	vertexBuffer3d->AddVertexData(8, -5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	vertexBuffer3d->AddVertexData(8, -5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	vertexBuffer3d->AddVertexData(8, 5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	vertexBuffer3d->AddVertexData(8, 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);


	vertexBuffer3d->AddVertexAttribute("position", 0, 3, 0);
	vertexBuffer3d->AddVertexAttribute("vertexColor", 1, 3, 3);
	vertexBuffer3d->AddVertexAttribute("texCoord", 2, 2, 6);
	*/



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

}



static void SetUpTexturedScene(std::shared_ptr<Shader>&
	textureShader, std::shared_ptr<Scene>& textureScene)
{
	//unsigned int shaderProgram;
	std::shared_ptr<TextFile> vertFile = std::make_shared<TextFile>();
	// relative path 
	vertFile->ReadFile("texture.vert.glsl");

	// relative path
	std::shared_ptr<TextFile> fragFile = std::make_shared<TextFile>();
	fragFile->ReadFile("texture.frag.glsl");

	// am i supposed to use the shader that was passed into the method?
	textureShader = std::make_shared<Shader>(vertFile->GetString(), fragFile->GetString());

	textureShader->AddUniform("projection");
	textureShader->AddUniform("world");
	textureShader->AddUniform("view");
	textureShader->AddUniform("texUnit");
	//shaderProgram = shader->GetShaderProgram();

	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	texture->SetHeight(4);
	texture->SetWidth(4);
	unsigned char* data = new unsigned char[] { 255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255,
		0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
		0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
		255, 255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255 };

	texture->SetTextureData(64, data);

	// next instruction is to create sharedscene object, arent we already passing one into this object?
	textureScene = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> graphicsObject = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(8);
	//updated the tex vertex data from 1 to 3
	vertexBuffer->AddVertexData(8, -20.0f, 20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 3.0f);
	vertexBuffer->AddVertexData(8, -20.0f, -20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	vertexBuffer->AddVertexData(8, 20.0f, -20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 0.0f);
	vertexBuffer->AddVertexData(8, -20.0f, 20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 3.0f);
	vertexBuffer->AddVertexData(8, 20.0f, -20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 0.0f);
	vertexBuffer->AddVertexData(8, 20.0f, 20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 3.0f);

	vertexBuffer->AddVertexAttribute("position", 0, 3, 0);
	vertexBuffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	vertexBuffer->AddVertexAttribute("texCoord", 2, 2, 6);

	// adjusting the texture settings here
	texture->SetWrapS(GL_CLAMP_TO_EDGE);
	texture->SetWrapT(GL_CLAMP_TO_EDGE);
	texture->SetMagFilter(GL_LINEAR);
	texture->SetMinFilter(GL_LINEAR);

	vertexBuffer->SetTexture(texture);
	graphicsObject->SetVertexBuffer(vertexBuffer);
	graphicsObject->SetPosition(glm::vec3(-40.0f, -20.0f, 0.0f));  //can adjust position if needed
	textureScene->AddObject(graphicsObject);


	// new textured object to scene
	std::shared_ptr<GraphicsObject> graphicsObject2 = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> vertexBuffer2 = std::make_shared<VertexBuffer>(8);
	vertexBuffer2->AddVertexData(8, -10.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	vertexBuffer2->AddVertexData(8, -10.0f, -10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	vertexBuffer2->AddVertexData(8, 10.0f, -10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	vertexBuffer2->AddVertexData(8, -10.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	vertexBuffer2->AddVertexData(8, 10.0f, -10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	vertexBuffer2->AddVertexData(8, 10.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	vertexBuffer2->AddVertexAttribute("position", 0, 3, 0);
	vertexBuffer2->AddVertexAttribute("vertexColor", 1, 3, 3);
	vertexBuffer2->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> texture2 = std::make_shared<Texture>();
	texture2->LoadTextureDataFromFile("..\\3rdparty\\texture\\Default\\Tiles\\tile_0122.png");


	vertexBuffer2->SetTexture(texture2);
	graphicsObject2->SetVertexBuffer(vertexBuffer2);
	graphicsObject2->SetPosition(glm::vec3(40.0f, 10.0f, 0.0f));  //can adjust position if needed
	textureScene->AddObject(graphicsObject2);


}

static void SetUpNonTexturedScene(std::shared_ptr<Shader>&
	shader, std::shared_ptr<Scene>& scene)
{
	unsigned int shaderProgram;
	std::shared_ptr<TextFile> vertFile = std::make_shared<TextFile>();
	// relative path 
	vertFile->ReadFile("basic.vert.glsl");

	// relative path
	std::shared_ptr<TextFile> fragFile = std::make_shared<TextFile>();
	fragFile->ReadFile("basic.frag.glsl");


	shader = std::make_shared<Shader>(vertFile->GetString(), fragFile->GetString());

	shader->AddUniform("projection");
	shader->AddUniform("world");
	shader->AddUniform("view");
	shaderProgram = shader->GetShaderProgram();

	scene = std::make_shared<Scene>();

	std::shared_ptr<GraphicsObject> square = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(6);
	buffer->AddVertexData(6, -5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(6, -5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(6, 5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(6, -5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexData(6, 5.0f, -5.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexData(6, 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexAttribute("position", 0, 3);
	buffer->AddVertexAttribute("color", 1, 3, 3);
	square->SetVertexBuffer(buffer);
	scene->AddObject(square);

	std::shared_ptr<GraphicsObject> triangle = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer2 = std::make_shared<VertexBuffer>(6);
	buffer2->AddVertexData(6, -5.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer2->AddVertexData(6, -5.0f, -5.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer2->AddVertexData(6, 5.0f, -5.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer2->AddVertexAttribute("position", 0, 3);
	buffer2->AddVertexAttribute("color", 1, 3, 3);
	triangle->SetVertexBuffer(buffer2);
	triangle->SetPosition(glm::vec3(30.0f, 0.0f, 0.0f));
	scene->AddObject(triangle);

	std::shared_ptr<GraphicsObject> line = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer3 = std::make_shared<VertexBuffer>(6);
	buffer3->SetPrimitiveType(GL_LINES);
	buffer3->AddVertexData(6, 0.0f, 2.5f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer3->AddVertexData(6, 0.0f, -2.5f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer3->AddVertexAttribute("position", 0, 3);
	buffer3->AddVertexAttribute("color", 1, 3, 3);
	line->SetVertexBuffer(buffer3);
	line->SetPosition(glm::vec3(5.0f, -10.0f, 0.0f));
	triangle->AddChild(line);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	std::shared_ptr<GraphicsEnvironment> graphicsEnviron = std::make_shared<GraphicsEnvironment>();
	graphicsEnviron->Init(4, 3);

	bool created = graphicsEnviron->SetWindow(1200, 800, "ETSU Computing Interactive Graphics");
	if (created == false) return -1;


	bool loaded = graphicsEnviron->InitGlad();
	if (loaded == false) return -1;

	graphicsEnviron->SetUpGraphics();


	std::shared_ptr<Shader> shader;
	std::shared_ptr<Scene> scene;
	SetUpNonTexturedScene(shader, scene);


	graphicsEnviron->CreateRenderer("renderer1", shader);
	graphicsEnviron->GetRenderer("renderer1")->SetScene(scene);


	// setup texture info here
	std::shared_ptr<Shader> textureShader;
	std::shared_ptr<Scene> textureScene;
	SetUpTexturedScene(textureShader, textureScene);


	graphicsEnviron->CreateRenderer("renderer2", textureShader);
	graphicsEnviron->GetRenderer("renderer2")->SetScene(textureScene);



	graphicsEnviron->StaticAllocate();

	// can comment this out for now to not run the 2d graphics program
	graphicsEnviron->Run2D();


	// can i reuse the same graphics environ here?
	/*
	graphicsEnviron->SetUpGraphics();

	// new 3d code created here
	std::shared_ptr<Shader> shader3d;
	std::shared_ptr<Scene> scene3d;
	SetUp3DScene1(shader3d, scene3d);


	graphicsEnviron->CreateRenderer("renderer3", shader3d);
	graphicsEnviron->GetRenderer("renderer3")->SetScene(scene3d);


	graphicsEnviron->StaticAllocate();

	graphicsEnviron->Run3D();
	*/
	return 0;
}

