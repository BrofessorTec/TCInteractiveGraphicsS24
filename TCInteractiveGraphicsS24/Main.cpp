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
#include "Generate.h"
#include "HighlightBehavior.h"


static void SetUp3DScene1(std::shared_ptr<Shader>& shader3d,
	std::shared_ptr<Scene>& scene3d, std::shared_ptr<GraphicsEnvironment>& graphicsEnviron)
{

	/*struct VertexData {
		glm::vec3 position, color;
		glm::vec2 tex;
	};*/


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








	scene3d = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> graphicsObject3d = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer = Generate::Cuboid(10.0f, 5.0f, 5.0f);

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	buffer->AddVertexAttribute("texCoord", 2, 2, 6);

	// adjusting the texture settings here
	texture3d->SetWrapS(GL_REPEAT);
	texture3d->SetWrapT(GL_REPEAT);
	texture3d->SetMagFilter(GL_NEAREST);
	texture3d->SetMinFilter(GL_NEAREST);

	buffer->SetTexture(texture3d);



	graphicsObject3d->SetVertexBuffer(buffer);

	graphicsObject3d->SetPosition(glm::vec3(0.0f, 2.6f, 0.0f));  //can adjust position if needed
	scene3d->AddObject(graphicsObject3d);


	// new crate code here
	std::shared_ptr<Texture> texture3dNew = std::make_shared<Texture>();

	//texture3dNew->LoadTextureDataFromFile("..\\3rdparty\\CrateTex.png");
	texture3dNew->LoadTextureDataFromFile("..\\3rdparty\\CrateTex2.jpg");

	float crateWidth = 5.0f;
	float crateHeight = 5.0f;
	float crateDepth = 5.0f;
	std::shared_ptr<GraphicsObject> graphicsObject3dCrate = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferNew = Generate::Cuboid(crateWidth, crateHeight, crateDepth);

	bufferNew->AddVertexAttribute("position", 0, 3, 0);
	bufferNew->AddVertexAttribute("vertexColor", 1, 3, 3);
	bufferNew->AddVertexAttribute("texCoord", 2, 2, 6);

	// adjusting the texture settings here
	texture3d->SetWrapS(GL_REPEAT);
	texture3d->SetWrapT(GL_REPEAT);
	texture3d->SetMagFilter(GL_NEAREST);
	texture3d->SetMinFilter(GL_NEAREST);

	bufferNew->SetTexture(texture3dNew);



	graphicsObject3dCrate->SetVertexBuffer(bufferNew);\
	// should be in scene 2
	// add bounding box here?
	//graphicsObject3dCrate->CreateBoundingBox(crateWidth, crateHeight, crateDepth);
	//graphicsObject3dCrate->GetReferenceFrame();  // for testing
	//graphicsObject3dCrate->GetBoundingBox();  // for testing



	graphicsObject3dCrate->SetPosition(glm::vec3(-10.0f, 2.6f, 0.0f));  //can adjust position if needed
	scene3d->AddObject(graphicsObject3dCrate);


	// new Floor code here
	std::shared_ptr<Texture> texture3dFloor = std::make_shared<Texture>();

	texture3dFloor->LoadTextureDataFromFile("..\\3rdparty\\FloorTex.jpg");


	std::shared_ptr<GraphicsObject> graphicsObject3dFloor = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferFloor = Generate::XZPlane(60, 60, glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec2{5.0f, 5.0f});

	bufferFloor->AddVertexAttribute("position", 0, 3, 0);
	bufferFloor->AddVertexAttribute("vertexColor", 1, 3, 3);
	bufferFloor->AddVertexAttribute("texCoord", 2, 2, 6);

	// adjusting the texture settings here
	texture3dFloor->SetWrapS(GL_REPEAT);
	texture3dFloor->SetWrapT(GL_REPEAT);
	texture3dFloor->SetMagFilter(GL_NEAREST);
	texture3dFloor->SetMinFilter(GL_NEAREST);

	bufferFloor->SetTexture(texture3dFloor);



	graphicsObject3dFloor->SetVertexBuffer(bufferFloor);

	graphicsObject3dFloor->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));  //can adjust position if needed
	scene3d->AddObject(graphicsObject3dFloor);

	graphicsEnviron->AddObject("cube", graphicsObject3d);
	graphicsEnviron->AddObject("Crate", graphicsObject3dCrate);
	graphicsEnviron->AddObject("floor", graphicsObject3dFloor);



}


static void SetUp3DScene2(std::shared_ptr<Shader>& shader3d,
	std::shared_ptr<Scene>& scene3d, std::shared_ptr<GraphicsEnvironment>& graphicsEnviron)
{

	std::shared_ptr<TextFile> vertFile = std::make_shared<TextFile>();
	// relative path 
	vertFile->ReadFile("lighting.vert.glsl");

	std::shared_ptr<TextFile> fragFile = std::make_shared<TextFile>();
	// relative path 
	fragFile->ReadFile("lighting.frag.glsl");


	shader3d = std::make_shared<Shader>(vertFile->GetString(), fragFile->GetString());

	shader3d->AddUniform("projection");
	shader3d->AddUniform("world");
	shader3d->AddUniform("view");
	shader3d->AddUniform("materialAmbientIntensity");
	shader3d->AddUniform("materialSpecularIntensity");
	shader3d->AddUniform("materialShininess");
	shader3d->AddUniform("globalLightPosition");
	shader3d->AddUniform("globalLightColor");
	shader3d->AddUniform("globalLightIntensity");
	shader3d->AddUniform("globalLightAttenuationCoef");
	shader3d->AddUniform("localLightPosition");
	shader3d->AddUniform("localLightColor");
	shader3d->AddUniform("localLightIntensity");
	shader3d->AddUniform("localLightAttenuationCoef");
	shader3d->AddUniform("viewPosition");
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

	float cubeWidth = 10.0f;
	float cubeHeight = 5.0f;
	float cubeDepth = 5.0f;


	scene3d = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> graphicsObject3d = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer = Generate::CuboidNorm(cubeWidth, cubeHeight, cubeDepth);

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 4, 3);
	buffer->AddVertexAttribute("normal", 2, 3, 7);
	buffer->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	texture3d->SetWrapS(GL_REPEAT);
	texture3d->SetWrapT(GL_REPEAT);
	texture3d->SetMagFilter(GL_NEAREST);
	texture3d->SetMinFilter(GL_NEAREST);

	buffer->SetTexture(texture3d);



	graphicsObject3d->SetVertexBuffer(buffer);

	graphicsObject3d->CreateBoundingBox(cubeWidth, cubeHeight, cubeDepth);

	// adding highlight behavior here
	std::shared_ptr<HighlightBehavior> cubeHighlight = std::make_shared<HighlightBehavior>();
	cubeHighlight->SetObject(graphicsObject3d);
	graphicsObject3d->AddBehavior("highlight", cubeHighlight);


	graphicsObject3d->SetPosition(glm::vec3(0.0f, 2.6f, 0.0f));  //can adjust position if needed
	scene3d->AddObject(graphicsObject3d);


	// new crate code here
	std::shared_ptr<Texture> texture3dNew = std::make_shared<Texture>();

	//texture3dNew->LoadTextureDataFromFile("..\\3rdparty\\CrateTex.png");
	texture3dNew->LoadTextureDataFromFile("..\\3rdparty\\CrateTex2.jpg");


	float crateWidth = 5.0f;
	float crateHeight = 5.0f;
	float crateDepth = 5.0f;

	std::shared_ptr<GraphicsObject> graphicsObject3dCrate = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferNew = Generate::CuboidNorm(crateWidth, crateHeight, crateDepth);

	bufferNew->AddVertexAttribute("position", 0, 3, 0);
	bufferNew->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferNew->AddVertexAttribute("normal", 2, 3, 7);
	bufferNew->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	texture3d->SetWrapS(GL_REPEAT);
	texture3d->SetWrapT(GL_REPEAT);
	texture3d->SetMagFilter(GL_NEAREST);
	texture3d->SetMinFilter(GL_NEAREST);

	bufferNew->SetTexture(texture3dNew);


	graphicsObject3dCrate->SetVertexBuffer(bufferNew);
	// add bounding box here?
	graphicsObject3dCrate->CreateBoundingBox(crateWidth, crateHeight, crateDepth);

	// adding highlight behavior here
	std::shared_ptr<HighlightBehavior> crateHighlight = std::make_shared<HighlightBehavior>();
	crateHighlight->SetObject(graphicsObject3dCrate);
	graphicsObject3dCrate->AddBehavior("highlight", crateHighlight);


	graphicsObject3dCrate->SetPosition(glm::vec3(-10.0f, 2.6f, 0.0f));  //can adjust position if needed
	scene3d->AddObject(graphicsObject3dCrate);


	// new Floor code here
	std::shared_ptr<Texture> texture3dFloor = std::make_shared<Texture>();

	texture3dFloor->LoadTextureDataFromFile("..\\3rdparty\\FloorTex.jpg");


	std::shared_ptr<GraphicsObject> graphicsObject3dFloor = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferFloor = Generate::XZPlaneNorm(60, 60, glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 5.0f, 5.0f });

	bufferFloor->AddVertexAttribute("position", 0, 3, 0);
	bufferFloor->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferFloor->AddVertexAttribute("normal", 2, 3, 7);
	bufferFloor->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	texture3dFloor->SetWrapS(GL_REPEAT);
	texture3dFloor->SetWrapT(GL_REPEAT);
	texture3dFloor->SetMagFilter(GL_NEAREST);
	texture3dFloor->SetMinFilter(GL_NEAREST);

	bufferFloor->SetTexture(texture3dFloor);



	graphicsObject3dFloor->SetVertexBuffer(bufferFloor);

	graphicsObject3dFloor->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));  //can adjust position if needed
	scene3d->AddObject(graphicsObject3dFloor);

	graphicsEnviron->AddObject("cube", graphicsObject3d);
	graphicsEnviron->AddObject("Crate", graphicsObject3dCrate);
	graphicsEnviron->AddObject("floor", graphicsObject3dFloor);



}

// new ray scene here
static void SetUpPCObjectsScene(
	std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene,
	std::shared_ptr<GraphicsEnvironment>& env)
{
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

	// create object
	scene = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> pcLinesCircle = std::make_shared<GraphicsObject>();
	pcLinesCircle->CreateVertexBuffer(6);  
	pcLinesCircle->CreateIndexBuffer();
	std::shared_ptr<VertexBuffer> bufferNew = pcLinesCircle->GetVertexBuffer();
	std::shared_ptr<IndexBuffer> indexBufferNew = pcLinesCircle->GetIndexBuffer();
	int steps = 10;  // can change this if we want to change the number of steps
	bufferNew->SetPrimitiveType(GL_LINES); 
	Generate::GenerateXZCircle(6, glm::vec3(1.0f), steps, bufferNew);  //10 steps used here
	Generate::LineCircleIndexes(indexBufferNew, (360/steps), true);  // 36 used here because 360 degrees and 10 steps
	bufferNew->AddVertexAttribute("position", 0, 3, 0); 
	bufferNew->AddVertexAttribute("color", 1, 3, 3);
	bufferNew->SetUpAttributeInterpretration();
	pcLinesCircle->SetPosition({ 0.0f, 1.0f, 10.0f }); // set initial position
	scene->AddObject(pcLinesCircle);
	env->AddObject("pcLinesCircle", pcLinesCircle);

	//cylinder 
	std::shared_ptr<GraphicsObject> pcLinesCylinder = std::make_shared<GraphicsObject>();
	pcLinesCylinder->CreateVertexBuffer(6);
	pcLinesCylinder->CreateIndexBuffer();
	std::shared_ptr<VertexBuffer> bufferNewCylinder = pcLinesCylinder->GetVertexBuffer();
	std::shared_ptr<IndexBuffer> indexBufferNewCylinder = pcLinesCylinder->GetIndexBuffer();
	int steps2 = 10;  // can change this if we want to change the number of steps
	bufferNewCylinder->SetPrimitiveType(GL_LINES);
	Generate::GenerateXZCylinder(6, 10, glm::vec3(1.0f), steps2, bufferNewCylinder); 
	Generate::LineCylinderIndexes(indexBufferNewCylinder, (360 / steps2)); 
	bufferNewCylinder->AddVertexAttribute("position", 0, 3, 0);
	bufferNewCylinder->AddVertexAttribute("color", 1, 3, 3);
	bufferNewCylinder->SetUpAttributeInterpretration();
	pcLinesCylinder->SetPosition({ 15.0f, 10.0f, 10.0f }); // set initial position
	scene->AddObject(pcLinesCylinder);
	env->AddObject("pcLinesCylinder", pcLinesCylinder);


}


static void SetUpLightScene(std::shared_ptr<Shader>&
	lightShader, std::shared_ptr<Scene>& lightScene, std::shared_ptr<GraphicsEnvironment>& graphicsEnviron)
{
	//unsigned int shaderProgram;
	std::shared_ptr<TextFile> vertFile = std::make_shared<TextFile>();
	// relative path 
	vertFile->ReadFile("texture.vert.glsl");

	// relative path
	std::shared_ptr<TextFile> fragFile = std::make_shared<TextFile>();
	fragFile->ReadFile("texture.frag.glsl");

	lightShader = std::make_shared<Shader>(vertFile->GetString(), fragFile->GetString());

	lightShader->AddUniform("projection");
	lightShader->AddUniform("world");
	lightShader->AddUniform("view");



	// new textured object to scene
	lightScene = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> lightbulb = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> lightbulbBuffer = Generate::XYPlane(4, 4);

	lightbulbBuffer->AddVertexAttribute("position", 0, 3, 0);
	lightbulbBuffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	lightbulbBuffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> lightbulbTexture = std::make_shared<Texture>();
	lightbulbTexture->LoadTextureDataFromFile("..\\3rdparty\\lightbulb.png");


	lightbulbBuffer->SetTexture(lightbulbTexture);
	lightbulb->SetVertexBuffer(lightbulbBuffer);

	lightScene->AddObject(lightbulb);
	graphicsEnviron->AddObject("lightbulb", lightbulb);


}


static void SetUpArrowScene(std::shared_ptr<Shader>&
	arrowShader, std::shared_ptr<Scene>& arrowScene, std::shared_ptr<GraphicsEnvironment>& graphicsEnviron)
{
	//unsigned int shaderProgram;
	std::shared_ptr<TextFile> vertFile = std::make_shared<TextFile>();
	// relative path 
	vertFile->ReadFile("texture.vert.glsl");

	// relative path
	std::shared_ptr<TextFile> fragFile = std::make_shared<TextFile>();
	fragFile->ReadFile("texture.frag.glsl");

	arrowShader = std::make_shared<Shader>(vertFile->GetString(), fragFile->GetString());

	arrowShader->AddUniform("projection");
	arrowShader->AddUniform("world");
	arrowShader->AddUniform("view");



	// new textured object to scene
	arrowScene = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> arrow = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> arrowBuffer = Generate::Cuboid(4, 4, 10);
	std::shared_ptr<VertexBuffer> arrowBuffer2 = Generate::ArrowNorm(4, 4, 10);


	arrowBuffer->AddVertexAttribute("position", 0, 3, 0);
	arrowBuffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	arrowBuffer->AddVertexAttribute("texCoord", 2, 2, 6);




	std::shared_ptr<Texture> arrowTexture = std::make_shared<Texture>();
	// this texture is breaking now for some reason
	//arrowTexture->LoadTextureDataFromFile("..\\3rdparty\\ArrowTex2.jpg");


	arrowBuffer->SetTexture(arrowTexture);
	arrow->SetVertexBuffer(arrowBuffer);
	arrow->SetPosition(glm::vec3(10.0f, 10.0f, 0.0f));

	arrowScene->AddObject(arrow);
	graphicsEnviron->AddObject("arrow", arrow);


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
	texture->SetWrapS(GL_REPEAT);
	texture->SetWrapT(GL_REPEAT);
	texture->SetMagFilter(GL_NEAREST);
	texture->SetMinFilter(GL_NEAREST);

	vertexBuffer->SetTexture(texture);
	graphicsObject->SetVertexBuffer(vertexBuffer);
	graphicsObject->SetPosition(glm::vec3(-40.0f, -20.0f, 0.0f));  //can adjust position if needed
	textureScene->AddObject(graphicsObject);


	// new textured object to scene
	std::shared_ptr<GraphicsObject> graphicsObject2 = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> vertexBuffer2 = std::make_shared<VertexBuffer>(8);
	vertexBuffer2->AddVertexData(8, -10.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 3.0f);
	vertexBuffer2->AddVertexData(8, -10.0f, -10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	vertexBuffer2->AddVertexData(8, 10.0f, -10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 0.0f);
	vertexBuffer2->AddVertexData(8, -10.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 3.0f);
	vertexBuffer2->AddVertexData(8, 10.0f, -10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 0.0f);
	vertexBuffer2->AddVertexData(8, 10.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 3.0f);

	vertexBuffer2->AddVertexAttribute("position", 0, 3, 0);
	vertexBuffer2->AddVertexAttribute("vertexColor", 1, 3, 3);
	vertexBuffer2->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> texture2 = std::make_shared<Texture>();
	texture2->LoadTextureDataFromFile("..\\3rdparty\\texture\\Default\\Tiles\\tile_0122.png");
	texture2->SetWrapS(GL_REPEAT);
	texture2->SetWrapT(GL_REPEAT);
	texture2->SetMagFilter(GL_NEAREST);
	texture2->SetMinFilter(GL_NEAREST);


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

	
	// Run 2d Code below here
	/*
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
	*/


	// can i reuse the same graphics environ here?
	
	graphicsEnviron->SetUpGraphics();

	// new 3d code created here
	std::shared_ptr<Shader> shader3d;
	std::shared_ptr<Scene> scene3d;
	//SetUp3DScene1(shader3d, scene3d, graphicsEnviron);
	SetUp3DScene2(shader3d, scene3d, graphicsEnviron);


	graphicsEnviron->CreateRenderer("renderer3d", shader3d);
	graphicsEnviron->GetRenderer("renderer3d")->SetScene(scene3d);


	// attempting to set up the second scene
	std::shared_ptr<Shader> shaderLight;
	std::shared_ptr<Scene> sceneLight;
	SetUpLightScene(shaderLight, sceneLight, graphicsEnviron);


	graphicsEnviron->CreateRenderer("rendererLight", shaderLight);
	graphicsEnviron->GetRenderer("rendererLight")->SetScene(sceneLight);

	// attempting to set up the arrow scene
	std::shared_ptr<Shader> shaderArrow;
	std::shared_ptr<Scene> sceneArrow;
	SetUpArrowScene(shaderArrow, sceneArrow, graphicsEnviron);

	/* removing arrow code for now
	graphicsEnviron->CreateRenderer("rendererArrow", shaderArrow);
	graphicsEnviron->GetRenderer("rendererArrow")->SetScene(sceneArrow);
	*/

	// attempting to set up the pc circle scene
	std::shared_ptr<Shader> shaderCircle;
	std::shared_ptr<Scene> sceneCircle;
	SetUpPCObjectsScene(shaderCircle, sceneCircle, graphicsEnviron);


	graphicsEnviron->CreateRenderer("rendererCircle", shaderCircle);
	graphicsEnviron->GetRenderer("rendererCircle")->SetScene(sceneCircle);


	graphicsEnviron->StaticAllocate();

	graphicsEnviron->Run3D();
	
	
	return 0;
}

