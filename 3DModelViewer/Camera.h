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

	Camera(int width, int height, glm::vec3 position);

	glm::vec3 GetPosition() const { return _position; }
	glm::vec3 GetOrientation() const { return _orientation; }
	glm::vec3 GetUp() const { return _up; }

	void UpdateMatrix(float FOVdegree, float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);
	void Move(EMoveDirection direction);


private:

	glm::vec3 _position;
	glm::vec3 _orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	int _width;
	int _height;

	float _speed = 0.1f;
	float _sensitivity = 100.0f;
};

























//// Camera.h
//#pragma once
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//
//class Camera {
//public:
//    glm::vec3 Position;
//    glm::vec3 Front;
//    glm::vec3 Up;
//    glm::vec3 Right;
//    glm::vec3 WorldUp;
//
//    float Yaw;
//    float Pitch;
//
//    float MovementSpeed;
//    float MouseSensitivity;
//
//    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
//        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
//        float yaw = -90.0f,
//        float pitch = 0.0f)
//        : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
//        MovementSpeed(2.5f),
//        MouseSensitivity(0.1f)
//    {
//        Position = position;
//        WorldUp = up;
//        Yaw = yaw;
//        Pitch = pitch;
//        updateCameraVectors();
//    }
//
//    glm::mat4 GetViewMatrix() const {
//        return glm::lookAt(Position, Position + Front, Up);
//    }
//
//    void ProcessKeyboard(const char* direction, float deltaTime) {
//        float velocity = MovementSpeed * deltaTime;
//        if (direction == "FORWARD")
//            Position += Front * velocity;
//        if (direction == "BACKWARD")
//            Position -= Front * velocity;
//        if (direction == "LEFT")
//            Position -= Right * velocity;
//        if (direction == "RIGHT")
//            Position += Right * velocity;
//    }
//
//    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
//        xoffset *= MouseSensitivity;
//        yoffset *= MouseSensitivity;
//
//        Yaw += xoffset;
//        Pitch += yoffset;
//
//        if (constrainPitch) {
//            if (Pitch > 89.0f) Pitch = 89.0f;
//            if (Pitch < -89.0f) Pitch = -89.0f;
//        }
//
//        updateCameraVectors();
//    }
//
//private:
//    void updateCameraVectors() {
//        glm::vec3 front;
//        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
//        front.y = sin(glm::radians(Pitch));
//        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
//        Front = glm::normalize(front);
//
//        Right = glm::normalize(glm::cross(Front, WorldUp));
//        Up = glm::normalize(glm::cross(Right, Front));
//    }
//};



//In your main loop :
//
//Camera camera;
//
//// Setup projection matrix once
//glm::mat4 projection = glm::perspective(glm::radians(45.0f),
//	(float)windowWidth / (float)windowHeight,
//	0.1f, 100.0f);
//
//// Each frame
//glm::mat4 view = camera.GetViewMatrix();
//glm::mat4 vp = projection * view;
//
//Pass vp(or view and projection separately) into your shaders.


//Input
//float deltaTime = ...; // calculate time between frames
//
//const Uint8* state = SDL_GetKeyboardState(NULL);
//if (state[SDL_SCANCODE_W]) camera.ProcessKeyboard("FORWARD", deltaTime);
//if (state[SDL_SCANCODE_S]) camera.ProcessKeyboard("BACKWARD", deltaTime);
//if (state[SDL_SCANCODE_A]) camera.ProcessKeyboard("LEFT", deltaTime);
//if (state[SDL_SCANCODE_D]) camera.ProcessKeyboard("RIGHT", deltaTime);
//
//
//float xpos, ypos;
//SDL_GetRelativeMouseState(&xpos, &ypos); // mouse delta since last frame
//camera.ProcessMouseMovement(xpos, -ypos);
//
//
//Make sure to enable relative mouse mode in SDL so it captures mouse movement :
//SDL_SetRelativeMouseMode(SDL_TRUE);



