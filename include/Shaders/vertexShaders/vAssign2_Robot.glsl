#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 local;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;

void main() {
	gl_Position = projection * view * model * local * vec4(aPos, 1.0f);

	FragPos = vec3(model * vec4(aPos, 1.0f));
	
	vec4 tmp = model * local * vec4(aNormal, 0.0f);
	Normal = mat3(transpose(inverse(model))) * aNormal;
}