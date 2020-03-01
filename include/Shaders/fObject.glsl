#version 330 core

// Structs
// ---------------------------------------------
// --- Material properties
struct Material {
	sampler2D texDiffuse;
	sampler2D texSpecular;
	
	vec3 matDiffuse;
	vec3 matSpecular;
	
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
#define NR_POINT_LIGHTS 5

// --- Uniforms
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

// settings : how to interprete texture, and how to combine with basic
// material
uniform int useTexture;
uniform int useTextureSpecular;
uniform int textureMoreInfo;

uniform vec3 viewPos;

// --- Inputs
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

// --- Outputs
out vec4 FragColor;

// ==========================================================

vec3 calculDirLight(DirLight light, vec3 normal, vec3 viewDir,
					vec3 resDiffuse, vec3 resSpecular);
vec3 calculPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir,
					  vec3 resDiffuse, vec3 resSpecular);

// ==========================================================

// Main
// -----------------------------------------------------
void main() {
	// Normalising
	// ---------------------------------------------------------
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	// calculating the use of texture and basic material to have the final
	// resulting material properties
	// ---------------------------------------------------------
	
	vec3 resDiffuse = vec3(1.0f);
	vec3 texDiff = vec3(texture(material.texDiffuse,TexCoords));
	vec3 texSpec = vec3(texture(material.texSpecular,TexCoords));
	
	if (useTexture < 0) { resDiffuse = material.matDiffuse; }
	if (useTexture > 0) { resDiffuse = texDiff; }
	if (useTexture == 0) {
		if (texDiff.x < 0.9f, texDiff.y < 0.9f, texDiff.z < 0.9f) {
			resDiffuse = material.matDiffuse;
		} else {
			resDiffuse = vec3(0.0f);
			if (textureMoreInfo == 1) { resDiffuse = texSpec; }
		}
		
	}
	
	vec3 resSpecular = vec3(1.0f);
	if (useTextureSpecular < 0) { resSpecular = material.matSpecular; }
	if (useTextureSpecular > 0) { 
		
		resSpecular = texSpec;
		
		if (textureMoreInfo == 2) { resSpecular = vec3(1.0f) - texSpec; }
	}
	if (useTextureSpecular == 0) {
		if (texDiff.x < 0.9f, texDiff.y < 0.9f, texDiff.z < 0.9f) 
			resSpecular = material.matSpecular;
		else {
			resSpecular = texSpec;
			if (resSpecular.x < 0.05f && resSpecular.y < 0.05f && resSpecular.z < 0.05f) {
				resSpecular = vec3(0.0f);
			}
			resSpecular *= 2.0f;
		}
		
	}
	
	
	// Lighting calculation
	// ---------------------------------------------------------
	
	// directional lighting
	vec3 result = calculDirLight(dirLight, norm, viewDir, resDiffuse, resSpecular);
	
	// point lights
	for (int i = 0; i < NR_POINT_LIGHTS; i++) {
		result += calculPointLight(pointLights[i], norm, FragPos, viewDir, resDiffuse, resSpecular);
	}
	
	FragColor = vec4(result, 1.0f);
}

vec3 calculDirLight(DirLight light, vec3 normal, vec3 viewDir, 
					vec3 resDiffuse, vec3 resSpecular) {
	
	vec3 lightDir = normalize(-light.direction);
	
	// ambient shading
	vec3 ambient = light.ambient * resDiffuse;
	
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * resDiffuse;
	
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * resSpecular;
	
	// combine results
	return ambient + diffuse + specular;
}

vec3 calculPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir,
					  vec3 resDiffuse, vec3 resSpecular) {
	
	vec3 lightDir = normalize(light.position - fragPos);
	
	// ambient shading
	vec3 ambient = light.ambient * resDiffuse;
	
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * resDiffuse;
	
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3  specular = light.specular * spec * resSpecular;
	
	// attenuation (because point light)
	float dist = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * dist * dist);
	
	
	// combine results
	return attenuation * (ambient + diffuse + specular);

}







