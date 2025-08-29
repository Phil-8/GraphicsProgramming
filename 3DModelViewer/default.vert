#version 330 core

//positions coordinates
layout (location = 0) in vec3 positionIn;

//colors
layout (location = 1) in vec3 colorIn;

//texture coordinates
layout (location = 2) in vec2 textureIn;

//normals
layout (location = 3) in vec3 normalsIn;

out vec3 color;
out vec2 textureCoordinates;
out vec3 normals;
out vec3 position;

uniform mat4 cameraMatrix;
uniform mat4 model;


void main()
{
	gl_Position = cameraMatrix * model * vec4(positionIn, 1.0f);

	color = colorIn;
	textureCoordinates = textureIn;
	position = vec3(model * vec4(positionIn, 1.0));
	normals = mat3(transpose(inverse(model))) * normalsIn;
}