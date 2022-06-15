#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

uniform mat4 transform;

out vec3 vertexColor;

void main()
{
	vec4 transformed = transform * vec4(aPos, 1.0);
	gl_Position = transformed;

	
	vertexColor = aColor;
}