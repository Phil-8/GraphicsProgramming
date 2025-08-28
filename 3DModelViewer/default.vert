#version 330 core

//positions coordinates
layout (location = 0) in vec3 position;

//colors
layout (location = 1) in vec3 colorIn;

//texture coordinates
layout (location = 2) in vec2 textureIn;

out vec3 color;
out vec2 textrueCoordinates;

uniform mat4 camMatrix;


void main()
{
	gl_Position = camMatrix * vec4(position, 1.0);

	color = colorIn;
	textrueCoordinates = textureIn;
}