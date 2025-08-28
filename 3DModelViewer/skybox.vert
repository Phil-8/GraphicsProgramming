#version 330 core

layout (location = 0) in vec3 positionIn;

out vec3 textureCoordinates;

uniform mat4 projection;
uniform mat4 view;

void main ()
{
	textureCoordinates = positionIn;
	vec4 position = projection * view * vec4(positionIn, 1.0f);
	gl_Position = position.xyww;
}