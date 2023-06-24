#version 330 core

layout(location = 0) out vec4 colour;

uniform vec4 u_Colour;
uniform vec4 u_LightCol;

void main()
{
	colour = u_Colour * u_LightCol;
};  