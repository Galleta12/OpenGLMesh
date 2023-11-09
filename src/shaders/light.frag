#version 400 core

out vec4 FragColor;

uniform vec3 lightPos;

uniform vec4 lightColor;

void main()
{
	FragColor = lightColor;
}