#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform vec3 aColor;
uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexColor;
out vec2 TexCoord;


void main()
{
	vec4 transformed = transform * vec4(aPos, 1.0);
	gl_Position = projection * view * model * transformed;
	
	vertexColor = aColor;
	TexCoord = aTexCoord;
}