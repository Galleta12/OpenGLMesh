#version 400 core

uniform vec4 gLineColor;

layout ( location = 0 ) out vec4 FragColor;

void main()
{
    FragColor = gLineColor;
}
