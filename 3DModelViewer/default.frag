#version 330 core

in vec3 color;
in vec2 textrueCoordinates;

out vec4 finalColor;

uniform sampler2D tex;

void main()
{
	finalColor = texture(tex, textrueCoordinates);
}