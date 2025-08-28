#version 330 core

in vec3 color;
in vec2 textrueCoordinates;
in vec3 normals;
in vec3 currentPosition;

out vec4 finalColor;

uniform sampler2D tex;
uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

void main()
{
	float ambientLight = 0.2f;

	vec3 normal = normalize(normals);
	vec3 lightDirection = normalize(lightPosition - currentPosition);

	float diffuse = max(dot(normal, lightDirection), 0.0f);
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(cameraPosition - currentPosition);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specLightAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specLightAmount * specularLight;

	finalColor = texture(tex, textrueCoordinates) * lightColor * (diffuse + ambientLight + specular);
}