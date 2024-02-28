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
	//returns a view matrix that looks forward. Use the look frame
	lookFrame[2] = glm::vec4(1.0f);  // would this accomplish it? or needing to normalize?

	return lookFrame;
}

glm::mat4 Camera::LookAtTarget()
{
	// how to do this?
	// (it returns a view matrix that looks at the target position).
	//Use the look frame.


	return glm::mat4();
}
