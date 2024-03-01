#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
private:
	glm::mat4 lookFrame = glm::mat4(1.0f);  // initialize these to the identity matrix?
	glm::mat4 refFrame = glm::mat4(1.0f);
	int moveSpeed = 10;
	//glm::vec3 position; // or is this supposed to update the postion of the refernce frame? probably

public:
	void SetLookFrame(glm::mat4 lookFrame);
	void SetMoveSpeed(int speed);
	void SetPosition(glm::vec3 position);  
	glm::mat4 LookForward();
	glm::mat4 LookAtTarget(glm::vec3 target);
	void MoveForward(double elapsedSeconds);
	void MoveBackward(double elapsedSeconds);
	void MoveLeft(double elapsedSeconds);
	void MoveRight(double elapsedSeconds);
	void MoveUp(double elapsedSeconds);
	void MoveDown(double elapsedSeconds);
};

