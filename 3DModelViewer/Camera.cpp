#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::Width = width;
	Camera::Height = height;
	Position = position;
}


void Camera::Matrix(float FOVdegree, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdegree), (float)(Width / Height), nearPlane, farPlane);
}