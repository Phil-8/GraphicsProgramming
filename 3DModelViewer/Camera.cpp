#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::_width = width;
	Camera::_height = height;
	_position = position;
}


void Camera::UpdateMatrix(float FOVdegree, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(_position, _position + _orientation, _up);
	projection = glm::perspective(glm::radians(FOVdegree), (float)(_width / _height), nearPlane, farPlane);


	cameraMatrix = projection * view;
}


void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID(), uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}


void Camera::Move(EMoveDirection direction)
{
	switch (direction)
	{

	case Forward:
		_position += _speed * glm::normalize(_orientation);
		break;

	case Backward:
		_position -= _speed * glm::normalize(_orientation);
		break;

	case Left:
		_position -= _speed * glm::normalize(glm::cross(_orientation, _up));
		break;

	case Right:
		_position += _speed * glm::normalize(glm::cross(_orientation, _up));
		break;

	case Up:
		_position += _speed * glm::normalize(_up);
		break;

	case Down:
		_position -= _speed * glm::normalize(_up);
		break;

	default:
		break;

	}
}