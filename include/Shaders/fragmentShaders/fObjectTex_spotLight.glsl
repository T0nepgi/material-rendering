#version 330 core

// Material properties
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

// Light position and properties
struct Light {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

// Inputs
// ---------------------------------------
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

// Uniforms
// ---------------------------------------
uniform Material material;
uniform Light light;

uniform vec3 viewPos;

// Outputs
// ---------------------------------------
out vec4 FragColor;

// Main
// ---------------------------------------
void main() {
	
	float dist = length(light.position - FragPos);
	float attenuation = 1.0f/ (light.constant + light.linear * dist +
							   light.quadratic * dist * dist);
	
	// --- Ambient lighting
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	// --- Diffuse lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	
	// --- Specular lighting
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	
	// -- Result
	// the ambient light is not influenced by the angle
	vec3 result = ambient;
	
	// spot lit attenuation calculation
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta-light.outerCutOff) / epsilon, 0.0f, 1.0f);
	
	// the intensity value is applied to the diffuse and specular light
	result += intensity * (diffuse + specular);
	
	// final attenuation
	result *= attenuation;
	FragColor = vec4(result, 1.0f);
}