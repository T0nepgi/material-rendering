#version 330 core

// Material properties
struct Material {
	vec3 color;
	float specularStrength;
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

// Inputs
// ---------------------------------------
in vec3 Normal;
in vec3 FragPos;

// Uniforms
// ---------------------------------------
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLight;

uniform vec3 viewPos;

// Outputs
// ---------------------------------------
out vec4 FragColor;

// Functions declaration
// ---------------------------------------
vec3 calculDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calculPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

// Main
// ---------------------------------------
void main() {
	
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	vec3 result = calculDirLight(dirLight, normal, viewDir); // directional light
	result += calculPointLight(pointLight, normal, FragPos, viewDir); // point light
	
	FragColor = vec4(result, 1.0f);
}

// Functions definition
// ---------------------------------------
vec3 calculDirLight(DirLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);
	
	// ambient shading
	vec3 ambient = light.ambient * material.color;
	
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * material.color;
	
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * material.specularStrength;
	
	
	// combine results
	return ambient + diffuse + specular;
}

vec3 calculPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);
	
	// ambient shading
	vec3 ambient = light.ambient * material.color;
	
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * material.color;
	
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * material.color;
	
	// attenuation (because point light)
	float dist = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	
	// combine results
	return attenuation * (ambient + diffuse + specular);

}



