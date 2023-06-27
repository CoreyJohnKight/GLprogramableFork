#version 330 core

layout(location = 0) out vec4 colour;

in vec3 v_Normal;
in vec3 v_MyPos;

uniform vec4 u_Colour;
uniform vec4 u_LightCol;
uniform vec3 u_LightPos;
uniform vec3 u_CamPos;


void main()
{
	vec3 normal = normalize(v_Normal);
	vec3 lightDirection = normalize(u_LightPos - v_MyPos);

	float ambient = 0.3f;
	
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	
	float specularConstant = 0.5f;
	vec3 viewDirection = normalize(u_CamPos - v_MyPos);
	vec3 reflectionDir = reflect(-lightDirection, normal);
	float specularStrength = pow(max(dot(viewDirection, reflectionDir), 0.0f), 8);
	float specular = specularStrength * specularConstant;

	colour = u_Colour * u_LightCol * (diffuse + ambient + specular);
	colour.a = 1.0f;
};  