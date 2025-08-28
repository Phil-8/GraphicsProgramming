#version 330 core

layout (location = 0) in vec3 position;

out vec3 textureCoordinates;

uniform mat4 projection;
uniform mat4 view;

void main ()
{
	vec4 position = projection * view * vec4(position, 1.0f);
	gl_Position = position.xyww;

	textureCoordinates = vec3(position.x, position.y, -position.z);
}