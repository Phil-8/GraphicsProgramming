#version 330 core

layout (location = 0) in vec3 positionIn;

void main()
{
	gl_Position = vec4(positionIn.x, positionIn.y, positionIn.z, 1.0);
}