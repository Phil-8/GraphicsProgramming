#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::_width = width;
	Camera::_height = height;
	_position = position;
}


void Camera::UpdateMatrix(Shader& shader, Shader& lightShader)
{
	//calculate matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(_position, _position + _orientation, _up);
	projection = glm::perspective(glm::radians(_fov), static_cast<float>(_width) / static_cast<float>(_height), _nearPlane, _farPlane);

	_cameraMatrix = projection * view;

	//set shader uniforms
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.GetProgramID(), "cameraPosition"), _position.x, _position.y, _position.z);
	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(_cameraMatrix));

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(_cameraMatrix));
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


void Camera::ProcessMouse(float deltaX, float deltaY)
{
	_yaw +=  deltaX * _sensitivity;
	_pitch += deltaY * _sensitivity;

	_pitch = glm::clamp(_pitch, -89.0f, 89.0f);

	glm::vec3 direction;

	direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	direction.y = sin(glm::radians(_pitch));
	direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	_orientation = glm::normalize(direction);
}