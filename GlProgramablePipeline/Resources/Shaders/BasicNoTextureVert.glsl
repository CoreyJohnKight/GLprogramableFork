#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

out vec3 v_MyPos;
out vec3 v_Normal;

uniform mat4 u_MVP;
uniform mat4 u_Model;

void main()
{
	v_MyPos = vec3(u_Model * vec4(vec3(position), 1.0f));
	gl_Position = u_MVP * position;
	v_Normal = normal;
};

