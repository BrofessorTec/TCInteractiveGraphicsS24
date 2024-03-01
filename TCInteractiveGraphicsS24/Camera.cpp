#include "Camera.h"

void Camera::SetLookFrame(glm::mat4 lookFrame)
{
	this->lookFrame = lookFrame;
}

void Camera::SetMoveSpeed(int speed)
{
	moveSpeed = speed;
}

void Camera::SetPosition(glm::vec3 position)
{
	//glm::vec4 posUpdate = { position[0], position[1], position[2], 1.0f };  // is last spot a 0 or 1? cant remember
	refFrame[3] = glm::vec4(position, 1.0f);
}

glm::mat4 Camera::LookForward()
{
	// how to do this?
	//returns a view matrix that looks forward. Use the look frame?
	// tried to copy notes to what it would look like here but not sure if this is right at all

	//glm::vec3 cameraPosition;
	glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
	//refFrame[3] = glm::vec4(0.0f, 3.0f, 30.0f, 1.0f);  // initial camera position? could be altered
	glm::vec3 cameraForward;


	//cameraPosition = refFrame[3];
	cameraForward = -refFrame[2];
	cameraTarget = glm::vec3(refFrame[3]) + cameraForward;
	cameraUp = refFrame[1];
	lookFrame = glm::lookAt(glm::vec3(refFrame[3]), cameraTarget, cameraUp);

	return lookFrame;
}

glm::mat4 Camera::LookAtTarget(glm::vec3 target)
{
	// how to do this?
	// (it returns a view matrix that looks at the target position).
	//Use the look frame.

	//glm::vec3 cameraPosition;
	glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
	refFrame[3] = glm::vec4(0.0f, 3.0f, 30.0f, 1.0f);  // initial camera position? could be altered
	glm::vec3 cameraForward;


	//cameraPosition = refFrame[3];
	cameraForward = -refFrame[2];
	cameraUp = refFrame[1];
	lookFrame = glm::lookAt(glm::vec3(refFrame[3]), target, cameraUp);

	return lookFrame;
}

void Camera::MoveForward(double elapsedSeconds)
{
	glm::vec3 forward = -refFrame[2];
	glm::vec3 position = refFrame[3];
	forward = forward * static_cast<float>(moveSpeed * elapsedSeconds);
	position = position + forward;
	refFrame[3] = glm::vec4(position, 1.0f);
	//lookFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveBackward(double elapsedSeconds)
{
	glm::vec3 backward = refFrame[2];
	glm::vec3 position = refFrame[3];
	backward = backward * static_cast<float>(moveSpeed * elapsedSeconds);
	position = position + backward;
	refFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveLeft(double elapsedSeconds)
{
	glm::vec3 toLeft = -refFrame[0];
	glm::vec3 position = refFrame[3];
	toLeft = toLeft * static_cast<float>(10.0f * elapsedSeconds);
	position = position + toLeft;
	refFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveRight(double elapsedSeconds)
{
	glm::vec3 toRight = refFrame[0];
	glm::vec3 position = refFrame[3];
	toRight = toRight * static_cast<float>(10.0f * elapsedSeconds);
	position = position + toRight;
	refFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveUp(double elapsedSeconds)
{
	glm::vec3 up = refFrame[1];
	glm::vec3 position = refFrame[3];
	up = up * static_cast<float>(moveSpeed * elapsedSeconds);
	position = position + up;
	refFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveDown(double elapsedSeconds)
{
	glm::vec3 up = -refFrame[1];
	glm::vec3 position = refFrame[3];
	up = up * static_cast<float>(moveSpeed * elapsedSeconds);
	position = position + up;
	refFrame[3] = glm::vec4(position, 1.0f);
}
