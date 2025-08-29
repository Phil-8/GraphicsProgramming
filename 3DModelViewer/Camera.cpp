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


	_cameraMatrix = projection * view;
}


void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID(), uniform), 1, GL_FALSE, glm::value_ptr(_cameraMatrix));
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


	//float rotationX = _sensitivity * (float)(deltaY - (_height * 0.5)) / _height;
	//float rotationY = _sensitivity * (float)(deltaX - (_height * 0.5)) / _height;


	//glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(-rotationX), glm::normalize(glm::cross(_orientation, _up)));
	//glm::vec3 newOrientation = glm::normalize(glm::vec3(rotation * glm::vec4(_orientation, 0.0f)));

	//glm::vec3 newn = newOrientation;
	//glm::vec3 upn = glm::normalize(_up);

	//float cosLimit = std::cos(glm::radians(5.0f));

	//// if newn is NOT within 5° of up or down, accept it
	//if (glm::dot(newn, upn) < cosLimit && glm::dot(newn, -upn) < cosLimit) {
	//	_orientation = newn;
	//}

	//_orientation = glm::normalize(glm::rotate(_orientation, glm::radians(-rotationY), glm::normalize(_up)));



}



