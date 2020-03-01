#version 330 core

// Structs
// ---------------------------------------------
// --- Material properties
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	
	float shininess;	
};

// --- Directional Light
struct DirLight {
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// --- Point Light
struct PointLight {
	vec3 position;
	
	float constant;
	float linear;
	float quadratic;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// ==========================================================

// Variables
// -----------------------------------------------------
#define NR_POINT_LIGHTS 4

// --- Uniforms
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform vec3 viewPos;

// --- Inputs
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

// --- Outputs
out vec4 FragColor;

// ==========================================================

vec3 calculDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calculPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

// ==========================================================

// Main
// -----------------------------------------------------
void main() {
	// properties
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	// directional lighting
	vec3 result = calculDirLight(dirLight, norm, viewDir);
	
	// point lights
	for (int i = 0; i < NR_POINT_LIGHTS; i++) {
		result += calculPointLight(pointLights[i], norm, FragPos, viewDir);
	}
	
	FragColor = vec4(result, 1.0f);
}

vec3 calculDirLight(DirLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);
	
	// ambient shading
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	
	
	// combine results
	return ambient + diffuse + specular;
}

vec3 calculPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);
	
	// ambient shading
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	
	// attenuation (because point light)
	float dist = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * dist * dist);
	
	
	// combine results
	return attenuation * (ambient + diffuse + specular);

}







