#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

uniform mat3 model;

out vec4 vertexColor;

void main() 
{
	vertexColor = vec4(aColor, 1.0f);
	
	vec3 pos = vec3(aPos, 1.0f);
	
	pos = model * pos;
	gl_Position = vec4(pos.x/pos.z, pos.y/pos.z, 0.0f, 1.0f);
}