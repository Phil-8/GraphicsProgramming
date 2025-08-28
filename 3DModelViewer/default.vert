#version 330 core

//positions coordinates
layout (location = 0) in vec3 position;

//colors
layout (location = 1) in vec3 colorIn;

//texture coordinates
layout (location = 2) in vec2 textureIn;

//normals
layout (location = 3) in vec3 normalsIn;

out vec3 color;
out vec2 textrueCoordinates;
out vec3 normals;
out vec3 currentPosition;

uniform mat4 cameraMatrix;
uniform mat4 model;


void main()
{
	currentPosition = vec3(model * vec4(position, 1.0));

	gl_Position = cameraMatrix * vec4(currentPosition, 1.0);

	color = colorIn;
	textrueCoordinates = textureIn;
	normals = normalsIn;
}