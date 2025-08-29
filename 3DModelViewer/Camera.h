#pragma once

#include"Shader.h"
#include <glm/glm.hpp>

enum EMoveDirection
{
	Forward,
	Backward,
	Left,
	Right,
	Up,
	Down
};


class Camera
{

public:

	//constructor
	Camera(int width, int height, glm::vec3 position);

	//properties
	glm::vec3 GetPosition() const { return _position; }
	glm::vec3 GetOrientation() const { return _orientation; }
	glm::vec3 GetUp() const { return _up; }

	//handle matrix
	void UpdateMatrix(Shader& shader, Shader& lightShader);

	//movement
	void Move(EMoveDirection direction);
	void ProcessMouse(float deltaX, float deltaY);


private:

	glm::vec3 _position;
	glm::vec3 _orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 _cameraMatrix = glm::mat4(1.0f);

	int _width = 100;
	int _height = 100;

	float _fov = 45.0f;
	float _nearPlane = 0.1f;
	float _farPlane = 100.0f;
	float _speed = 0.1f;
	float _sensitivity = 0.2f;
	float _yaw = -90.0f;
	float _pitch = 0.0f;
};