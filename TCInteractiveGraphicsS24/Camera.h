#pragma once
#include <glm/glm.hpp>
class Camera
{
private:
	glm::mat4 lookFrame;
	glm::mat4 refFrame;
	int moveSpeed = 10;
	//glm::vec3 position; // or is this supposed to update the postion of the refernce frame? probably

public:
	void SetLookFrame(glm::mat4 lookFrame);
	void SetMoveSpeed(int speed);
	void SetPosition(glm::vec3 position);  
	glm::mat4 LookForward();
	glm::mat4 LookAtTarget();
};

