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
	
	// ambient light
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	// diffuse lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	//vec3 lightDir = normalize(-light.direction); 
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	
	// specular lighting
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	
	// result
	vec3 result = attenuation * (ambient + diffuse + specular);
	FragColor = vec4(result, 1.0f);
}