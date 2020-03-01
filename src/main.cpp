//GLAD
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ImageReader/stb_image.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Other libraries
#include <iostream>
#include <climits>
#include <cmath>
#include <vector>
#include <fstream>

//Other classes
#include "Shader.h"
#include "Camera.h"


using namespace std;
using namespace glm;

// --- Camera
Camera camera(vec3(0.0f, 0.0f, 10.0f));
float lastX = 400.0f;
float lastY = 300.0f;
bool firstMouse = true;

// Type of Light
enum Lighting {
	DIRECTION, POINT, SPOT, MULTIPLE
};

// Geometries
enum Geometry {
	CUBE, POLYHEDRE
};

const char* THIS_PROJECTS_NAME = "diverse materials visualization";

// Settings constants
// ------------------------------------------------------------

// Screen size
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// Background Color
const vec4 BACKGROUND_COLOR = vec4(0.1f, 0.1f, 0.1f, 1.0f);
// unit of time
const double TIME_RENDERING_UNIT = 7;

// Input
const float MOUSE_SENSITIVITY = 0.05f;

// --- Buffers
const unsigned int NB_VAOS = 3;
const unsigned int NB_VBOS = 2;
const unsigned int VAO_LIGHT = 0;
const unsigned int VAO_OBJ_CUBE = 1;
const unsigned int VAO_OBJ_POLYHEDRE = 2;
const unsigned int VBO_CUBE = 0;
const unsigned int VBO_POLYHEDRE = 1;

// --- Vertices files
const unsigned int NB_VERTICES_CUBE = 36;
const unsigned int NB_VERTICES_POLYHEDRE = 60;
const unsigned int NB_FLOATS_ONE_VERTICE = 8;
const unsigned int NB_FLOATS_POSITION = 3;
const unsigned int NB_FLOATS_NORMAL = 3;
const unsigned int NB_FLOATS_TEXCOORDS = 2;
const unsigned int LAYOUT_POSITION = 0;
const unsigned int LAYOUT_NORMAL = 1;
const unsigned int LAYOUT_TEXCOORDS = 2;
const unsigned int OFFSET_POSITION = 0;
const unsigned int OFFSET_NORMAL = NB_FLOATS_POSITION;
const unsigned int OFFSET_TEXCOORDS = OFFSET_NORMAL + NB_FLOATS_NORMAL;

// --- Object
const vec3 OBJECT_DEFAULT_DIFFUSE = vec3(1.0f, 0.5f, 0.31f);
const vec3 OBJECT_DEFAULT_SPECULAR = vec3(0.5f, 0.5f, 0.5f);
const float OBJECT_DEFAULT_SHININESS = 128.0f;

// --- Object files inscription protocol
const unsigned int OBJECT_INFO_SIZE = 13;
const unsigned int OBJECT_INFO_TEXTURE_INDEX = 2;
const unsigned int OBJECT_INFO_MAT_DIFFUSE = 3;
const unsigned int OBJECT_INFO_MAT_SPECULAR = 3;
const unsigned int OBJECT_INFO_SHININESS = 1;
const unsigned int OBJECT_INFO_TEXTURE_USE = 3;

// --- World's elements settings
const unsigned int NB_OBJECTS = 6;
const unsigned int NB_POINTLIGHTS = 5;
const float OBJECTS_ANGLES_OFFSET = 20.0f;
const vec3 OBJECTS_ROTATE_AXE = vec3(1.0f, 0.3f, 0.5f);
const vec3 LIGHTS_SCALE = vec3(0.2f);
const char* OBJECTS_POS_FILE = "objects_positions.txt";
const char* POINTLIGHTS_POS_FILE = "pointLights_positions.txt";
const char* TEXTURES_FILES = "res/textures/textures.txt";

// --- Lightning
const vec3 LIGHT_PROPER_COLOR = vec3(1.0f, 1.0f, 1.0f);
const float LIGHT_AMBIENT_FACTOR = 0.1f;
const float LIGHT_DIFFUSE_FACTOR = 0.5f;
const float LIGHT_SPECULAR_FACTOR = 1.0f;
const vec3 LIGHT_INITIAL_POSITION = vec3(1.2f, 1.0f, 2.0f);
const vec3 LIGHT_DIRECTION = vec3(-0.2f, -0.5f, -0.3f);
const float LIGHT_CONSTANT = 1.0f;
const float LIGHT_LINEAR = 0.5f;
const float LIGHT_QUADRATIC = 0.052f;
const float LIGHT_CUTOFF = 12.5f;
const float LIGHT_OUTERCUTOFF = 17.5f;

bool dynamicLight = false;
bool inTransition_dynamicToStaticLight = false;
bool L_KeyforDynamicLightIsPressed = false;

// --- Time and position during time
// time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// --- Others (non constants)
float texturesMixity = 0;


// ========================================================================

// -------------------------------------------------------------
// Functions
// -------------------------------------------------------------

// --- Window management
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
// mouse
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

// --- Initialisations and firsts settings
GLFWwindow* initialisation();
void geometryIntoBuffer(unsigned int* VBOs, unsigned int index, string fileName);
void setLightAttributes(unsigned int lightVAO, unsigned int VBO);
void setObjectAttributes(unsigned int objectVAO, unsigned int VBO);
void setShadersInitialPositionsAndColors(Shader* objectShader, Shader* lightShader, Lighting lightType,
										 string lightName = "light", const vector<vec3>& positions = vector<vec3>(0));
void setDirectionalLighting(Shader* objectShader, string lightName);
void setPointLighting(Shader* objectShader, string lightName, vec3 position = LIGHT_INITIAL_POSITION);
void setSpotLighting(Shader* objectShader, string lightName, bool useCamera = true, vec3 position =
					 LIGHT_INITIAL_POSITION, vec3 direction = LIGHT_DIRECTION);
void setMultipleLighting(Shader* objectShader, const vector<vec3>& positions, string lightName,
						 unsigned int nbLights = NB_POINTLIGHTS);
void setLightingBasicProperties(Shader* objectShader, string lightName, bool useBasic = true, vec3 color = vec3(1.0f));

// --- Light and Object updates
mat4 lightModelUpdate(vec3 lightPos);
void updateObjectShaderPosition(Shader* objectShader, mat4 model, mat4 view, mat4 projection);
void updateLightShaderPosition(Shader* lightShader, mat4 model, mat4 view, mat4 projection);
void updateLightsColor(vector<vec3>& colors, unsigned int size, double currentFrame);

// --- Drawing
void drawElement(Shader* elemShader, unsigned int elemVAO, Geometry Type);
void drawMultipleLights(Shader* lightShader, unsigned int VAO, const vector<vec3>& positions,
					    unsigned int nbElements, const vector<vec3>& colors = vector<vec3>());
void drawTheObjects(Shader* objectShader, unsigned int* VAOs, unsigned int* textures, const vector<float>& objectsMaterialInfos,
					const vector<vec3>& positions, unsigned int nbElements,
					const vector<vec3>& lightsNewColors = vector<vec3>(), string lightsName = "");

// --- Utils
void reloadBackgroundBuffers();
void deallocateBuffers(unsigned int nbVAO, unsigned int* firstVAO, unsigned int nbVBO, unsigned int* firstVBO,
					   unsigned int nbEBO, unsigned int* firstEBO);
vector<float> loadFloatsFromFile(char const *namePath);
vector<string> loadStringsFromFile(char const *namePath);
vector<vec3> retrievePositionsFromFile(string fileName, unsigned int nbPositions);
void createTextures(const vector<string>& fileNames, unsigned int* textures, unsigned int nbTextures);
unsigned int initialiseTexture(string fileName, unsigned int texture);

// =======================================================================================
// -------------------------------------- Main ----------------------------------------
// =======================================================================================

int main() {

	// Initialisation
	// ----------------------------------------------
	GLFWwindow* window = initialisation();
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}

	// Shaders
	// ----------------------------------------------

	Shader lightShader("vLight.glsl", "fLight.glsl");

	Shader objectShader("vObject.glsl", "fObject.glsl");

	// Buffers
	// ------------------------------------------------
	unsigned int VBOs[NB_VBOS];
	glGenBuffers(NB_VBOS, VBOs);

	unsigned int VAOs[NB_VAOS];
	glGenVertexArrays(NB_VAOS, VAOs);

	// fill the buffers with vertices loaded from file
	geometryIntoBuffer(VBOs, VBO_CUBE, "cubeNormalsAndTexture.txt");
	geometryIntoBuffer(VBOs, VBO_POLYHEDRE, "polyhedreNormalsAndTexture.txt");

	// Light attributes into array object
	setLightAttributes(VAOs[VAO_LIGHT], VBOs[VBO_CUBE]);

	// Object Attributes into array object
	setObjectAttributes(VAOs[VAO_OBJ_CUBE], VBOs[VBO_CUBE]);
	setObjectAttributes(VAOs[VAO_OBJ_POLYHEDRE], VBOs[VBO_POLYHEDRE]);

	// --- Unbind Buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// Texture
	// ------------------------------------------------
	vector<string> filesNames = loadStringsFromFile(TEXTURES_FILES);
	unsigned int textures[filesNames.size()];
	createTextures(filesNames, textures, filesNames.size());

	// Transformation matrix
	// ------------------------------------------------

	mat4 objectModel = mat4(1.0f);

	mat4 lightModel = mat4(1.0f);
	lightModel = translate(lightModel, LIGHT_INITIAL_POSITION);
	lightModel = scale(lightModel, LIGHTS_SCALE);

	// will get later from the camera
	mat4 view = mat4(1.0f);

	mat4 projection;
	projection = perspective(radians(camera.getFov()), (float) SCR_WIDTH / SCR_HEIGHT, NEAR_PLANE, FAR_PLANE);

	// ==============================================================

	// ------------------------------------------------
	// Rendering
	// ------------------------------------------------

	// Elements original position, orientation and scale
	vector<vec3> lightsPositions = retrievePositionsFromFile("pointLights_positions.txt", NB_POINTLIGHTS);
	vector<vec3> objectsPositions = retrievePositionsFromFile("objects_positions.txt", NB_OBJECTS);
	vector<float> objectsMaterialInfo = loadFloatsFromFile("res/objects/objects.txt");

	// --- Rendering Settings
	// Modes
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	// Lighting and Colors
	vector<vec3> lightsColors = vector<vec3>(NB_POINTLIGHTS);
	setShadersInitialPositionsAndColors(&objectShader, &lightShader, DIRECTION, "dirLight");
	setShadersInitialPositionsAndColors(&objectShader, NULL, MULTIPLE, "pointLights", lightsPositions);

	// Rendering loop
	// -----------------------------------------------
	while (!glfwWindowShouldClose(window)) {
		// useful constants
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// --------------------------------------------
		processInput(window);

		// transformations
		// --------------------------------------------

		// transformations update
		//lightModel = lightModelUpdate(lightPos);
		projection = perspective(radians(camera.getFov()), (float) SCR_WIDTH / SCR_HEIGHT, NEAR_PLANE,
					FAR_PLANE);
		view = camera.getViewMat();

		// object
		updateObjectShaderPosition(&objectShader, objectModel, view, projection);

		// light
		updateLightShaderPosition(&lightShader, lightModel, view, projection);

		// Lightning and Colors
		//----------------------------------------------
		objectShader.use();
		objectShader.setVec3("viewPos", camera.getPos());
		updateLightsColor(lightsColors, NB_POINTLIGHTS, currentFrame);

		// Rendering
		//----------------------------------------------

		// --- Reload buffers
		reloadBackgroundBuffers();

		// --- Drawing

		if (dynamicLight or inTransition_dynamicToStaticLight) {
			// lights
			drawMultipleLights(&lightShader, VAOs[0], lightsPositions, NB_POINTLIGHTS, lightsColors);
			// objects
			drawTheObjects(&objectShader, VAOs, textures, objectsMaterialInfo, objectsPositions, NB_OBJECTS,
						   lightsColors, "pointLights");
		} else {
			// lights
			drawMultipleLights(&lightShader, VAOs[0], lightsPositions, NB_POINTLIGHTS);
			// objects
			drawTheObjects(&objectShader, VAOs, textures, objectsMaterialInfo, objectsPositions, NB_OBJECTS);
		}


		// glfw : check and call events and swap the buffers
		// -------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Unbindings and de-allocate all resources
	// -----------------------------------------------------
	deallocateBuffers(NB_VAOS, VAOs, NB_VBOS, VBOs, 0, NULL);

	// glfw : terminate, clearing all previously allocated GLFW resources
	// -------------------------------------------------------
	glfwTerminate();
	return 0;
}

// ===========================================================================================
// ---------------------------------- Functions ----------------------------------------
// ===========================================================================================

//	Window management
// ------------------------------------------------------------

/* glfw : whenever the window size changed (by OS or user resize) this
 * callback function executes
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

/* process all input : query GLFW whether relevant keys are pressed/released
 * this frame and react accordingly
 */
void processInput(GLFWwindow* window) {
	// Quit
	// -----------------------------------------------------------
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// increase/decrease mixing
	// -----------------------------------------------------------
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		texturesMixity += 0.01;
		if (texturesMixity > 1.0f)
			texturesMixity = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		texturesMixity -= 0.01;
		if (texturesMixity < 0.0f)
			texturesMixity = 0.0f;
	}

	// linear moving
	// -----------------------------------------------------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.forward(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.backward(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.toTheLeft(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.toTheRight(deltaTime);

	// light mode (static or dynamic)
	// -----------------------------------------------------------
	if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		if(!L_KeyforDynamicLightIsPressed)
			L_KeyforDynamicLightIsPressed = true;

	} else if (L_KeyforDynamicLightIsPressed) {
		L_KeyforDynamicLightIsPressed = false;
		dynamicLight = !dynamicLight;
		if (!dynamicLight)
			inTransition_dynamicToStaticLight = true;
	}
}

/* process the movements of the mouse
 */
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;

		firstMouse = false;
	}

	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos; 	// reversed since y-coordinates range
									// bottom to top
	lastX = xpos;
	lastY = ypos;

	xOffset *= MOUSE_SENSITIVITY;
	yOffset *= MOUSE_SENSITIVITY;

	camera.updateYawAndPitch(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
	camera.updateFov(-yOffset);
}

// Initialisation and firsts Settings
// ------------------------------------------------------------
/*
 * First initilisation
 */
GLFWwindow* initialisation() {

	// glfw : initialise GLFW and configuring
	// --------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	// glfw : window creation
	// --------------------------

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, THIS_PROJECTS_NAME,
	NULL, NULL);
	if (window == NULL) {
		cout << "ERROR: Failed to create GLFW window" << endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Set input functions
	// capture the mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// glad : load all OpenGL function pointers
	// -------------------------------------------------------------
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return NULL;
	}

	return window;
}


void geometryIntoBuffer(unsigned int* VBOs, unsigned int index, string fileName) {
	string nameTmp = "res/vertices/" + fileName;

	// vertices
	vector<float> verticesTmp;
	verticesTmp = loadFloatsFromFile(nameTmp.c_str());
	float vertices[verticesTmp.size()];
	copy(verticesTmp.begin(), verticesTmp.end(), vertices);

	// into buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[index]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

void setLightAttributes(unsigned int lightVAO, unsigned int VBO) {
	glBindVertexArray(lightVAO);
	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// position
	glVertexAttribPointer(LAYOUT_POSITION, NB_FLOATS_POSITION, GL_FLOAT,
	GL_FALSE, NB_FLOATS_ONE_VERTICE * sizeof(float), (void*) (OFFSET_POSITION * sizeof(float)));
	glEnableVertexAttribArray(LAYOUT_POSITION);

	//unbins
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void setObjectAttributes(unsigned int objectVAO, unsigned int VBO) {
	glBindVertexArray(objectVAO);
	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Position
	glVertexAttribPointer(LAYOUT_POSITION, NB_FLOATS_POSITION, GL_FLOAT,
	GL_FALSE, NB_FLOATS_ONE_VERTICE * sizeof(float), (void*) (OFFSET_POSITION * sizeof(float)));
	glEnableVertexAttribArray(LAYOUT_POSITION);

	// Normals
	glVertexAttribPointer(LAYOUT_NORMAL, NB_FLOATS_NORMAL, GL_FLOAT, GL_FALSE,
				NB_FLOATS_ONE_VERTICE * sizeof(float), (void*) (OFFSET_NORMAL * sizeof(float)));
	glEnableVertexAttribArray(LAYOUT_NORMAL);

	// Texture Coords
	glVertexAttribPointer(LAYOUT_TEXCOORDS, NB_FLOATS_TEXCOORDS, GL_FLOAT,
	GL_FALSE, NB_FLOATS_ONE_VERTICE * sizeof(float), (void*) (OFFSET_TEXCOORDS * sizeof(float)));
	glEnableVertexAttribArray(LAYOUT_TEXCOORDS);

	// --- Unbinds
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void setShadersInitialPositionsAndColors(Shader* objectShader, Shader* lightShader, Lighting lightType,
			string lightName, const vector<vec3>& lightsPos) {

	// Object
	// ------------------------------------------------

	objectShader->use();
	// --- material default properties (before rendering)
	objectShader->setVec3("material.matDiffuse", OBJECT_DEFAULT_DIFFUSE);
	objectShader->setVec3("material.matSpecular", OBJECT_DEFAULT_SPECULAR);
	objectShader->setFloat("material.shininess", OBJECT_DEFAULT_SHININESS);
	objectShader->setInt("useTexture", -1);
	objectShader->setInt("useTextureSpecular", -1);

	// --- light properties
	switch (lightType) {
	case DIRECTION:
		setDirectionalLighting(objectShader, lightName);
		break;
	case POINT:
		setPointLighting(objectShader, lightName);
		break;
	case SPOT:
		setSpotLighting(objectShader, lightName);
		break;
	case MULTIPLE:
		setMultipleLighting(objectShader, lightsPos, lightName, NB_POINTLIGHTS);
	}

	// Light
	// -------------------------------------------------
	if (lightShader != NULL) {
		lightShader->use();
		lightShader->setVec3("lightColor", LIGHT_PROPER_COLOR);
	}
}

void setDirectionalLighting(Shader* objectShader, string lightName) {
	setLightingBasicProperties(objectShader, lightName);

	objectShader->setVec3(lightName + ".direction", LIGHT_DIRECTION);
}

void setPointLighting(Shader* objectShader, string lightName, vec3 position) {
	setLightingBasicProperties(objectShader, lightName);

	objectShader->setVec3(lightName + ".position", position);

	objectShader->setFloat(lightName + ".constant", LIGHT_CONSTANT);
	objectShader->setFloat(lightName + ".linear", LIGHT_LINEAR);
	objectShader->setFloat(lightName + "quadratic", LIGHT_QUADRATIC);
}

void setSpotLighting(Shader* objectShader, string lightName, bool useCamera, vec3 position, vec3 direction) {
	setLightingBasicProperties(objectShader, lightName);

	if (useCamera) {
		objectShader->setVec3(lightName + ".position", camera.getPos());
		objectShader->setVec3(lightName + ".direction", camera.getDirection());
	} else {
		objectShader->setVec3(lightName + ".position", position);
		objectShader->setVec3(lightName + ".direction", direction);
	}

	objectShader->setFloat(lightName + ".constant", LIGHT_CONSTANT);
	objectShader->setFloat(lightName + ".linear", LIGHT_LINEAR);
	objectShader->setFloat(lightName + "quadratic", LIGHT_QUADRATIC);
}

void setMultipleLighting(Shader* objectShader, const vector<vec3>& positions, string lightName,
			unsigned int nbLights) {
	for (unsigned int i = 0; i < nbLights; i++) {
		string name = lightName + "[";
		name += to_string(i) + "]";
		setPointLighting(objectShader, name, positions[i]);
	}
}

void setLightingBasicProperties(Shader* objectShader, string lightName, bool useBasic, vec3 color_) {

	vec3 color = useBasic ? LIGHT_PROPER_COLOR : color_;

	objectShader->setVec3(lightName + ".ambient", LIGHT_AMBIENT_FACTOR * color);
	objectShader->setVec3(lightName + ".diffuse", LIGHT_DIFFUSE_FACTOR * color);
	objectShader->setVec3(lightName + ".specular", LIGHT_SPECULAR_FACTOR * color);

	objectShader->setVec3("viewPos", camera.getPos());
}

// Light and objects update
// ------------------------------------------------------------
mat4 lightModelUpdate(vec3 lightPos) {
	mat4 lightModel = mat4(1.0f);
	lightModel = translate(lightModel, lightPos);
	lightModel = scale(lightModel, LIGHTS_SCALE);

	return lightModel;
}

void updateObjectShaderPosition(Shader* objectShader, mat4 model, mat4 view, mat4 projection) {
	objectShader->use();
	objectShader->setMat4("model", model);
	objectShader->setMat4("view", view);
	objectShader->setMat4("projection", projection);
}

void updateLightShaderPosition(Shader* lightShader, mat4 model, mat4 view, mat4 projection) {
	lightShader->use();
	lightShader->setMat4("model", model);
	lightShader->setMat4("view", view);
	lightShader->setMat4("projection", projection);
}

void updateLightsColor(vector<vec3>& colors, unsigned int size, double curFrame) {
	for (unsigned int i = 0; i < size; i++) {

		if (dynamicLight)
			colors[i] = vec3(sin(curFrame + i*M_PI_4), cos(0.5 * curFrame + i * M_PI_4), sin(2 * curFrame + i * M_PI_4));
		else
			colors[i] = LIGHT_PROPER_COLOR;
	}
}

// Drawing
// ------------------------------------------------------------

void drawElement(Shader* elemShader, unsigned int elemVAO, Geometry type) {
	elemShader->use();
	glBindVertexArray(elemVAO);
	glDrawArrays(GL_TRIANGLES, 0, type == CUBE ? NB_VERTICES_CUBE : NB_VERTICES_POLYHEDRE);
}

void drawMultipleLights(Shader* lightShader, unsigned int VAO, const vector<vec3>& positions,
						unsigned int nbElements, const vector<vec3>& colors) {

	int nb = nbElements;
	for (int i = 0; i < nb; i++) {
		mat4 model = mat4(1.0f);
		model = translate(model, positions[i]);
		model = scale(model, LIGHTS_SCALE);

		lightShader->use();
		lightShader->setMat4("model", model);

		// update colors
		if (colors.size() != 0) {
			lightShader->setVec3("lightColor", colors[i]);
		}

		drawElement(lightShader, VAO, CUBE);
	}
}

void drawTheObjects(Shader* objectShader, unsigned int* VAOs, unsigned int* textures, const vector<float>& infos,
			const vector<vec3>& positions, unsigned int nbObjects, const vector<vec3>& colors, string lName) {

	objectShader->use();

	// Update point lights colors if needed
	// -------------------------------------------------
	unsigned int lSize = colors.size();
	if (lSize != 0) {
		for (unsigned int i = 0; i < lSize; i++) {
			string name = lName + "[";
			name += to_string(i) + "]";

			setLightingBasicProperties(objectShader, name, false, colors[i]);
		}
	}

	// Each object properties
	// --------------------------------------------------
	for (unsigned int i = 0; i < nbObjects; i++) {

		// Infos from infos vector
		// -------------------------------------------
		unsigned int j = i * OBJECT_INFO_SIZE;

		// textures indexes
		int text = infos[j];
		int specText = infos[j + 1];

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[text]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[specText]);

		objectShader->setInt("material.texDiffuse", 0);
		objectShader->setInt("material.texSpecular", 1);
		j += OBJECT_INFO_TEXTURE_INDEX;

		// object's global diffuse color
		vec3 matDiffuse = vec3(infos[j], infos[j + 1], infos[j + 2]);
		objectShader->setVec3("material.matDiffuse", matDiffuse);
		j += OBJECT_INFO_MAT_DIFFUSE;

		// object's global specular color
		vec3 matSpecular = vec3(infos[j], infos[j + 1], infos[j + 2]);
		objectShader->setVec3("material.matSpecular", matSpecular);
		j += OBJECT_INFO_MAT_SPECULAR;

		// object's shininess
		float shininess = infos[j]*OBJECT_DEFAULT_SHININESS;
		objectShader->setFloat("material.shininess", shininess);
		j += OBJECT_INFO_SHININESS;

		// whether or not use the given textures
		int useTex = infos[j];
		int useTexSpecular = infos[j + 1];
		int invertTexSpec = infos[j+2];
		objectShader->setInt("useTexture", useTex);
		objectShader->setInt("useTextureSpecular", useTexSpecular);
		objectShader->setInt("textureMoreInfo", invertTexSpec);
		j += OBJECT_INFO_TEXTURE_USE;

		// geometry of the object
		Geometry type;
		switch ((int) infos[j]) {
		case 0:
			type = CUBE;
			break;
		case 1:
			type = POLYHEDRE;
			break;
		default:
			type = CUBE;
			break;
		}

		// Position
		// ---------------------------------------------
		mat4 model = mat4(1.0f);
		model = translate(model, positions[i]);
		float angle = OBJECTS_ANGLES_OFFSET * i;
		model = rotate(model, radians(angle), OBJECTS_ROTATE_AXE);
		objectShader->setMat4("model", model);

		drawElement(objectShader, VAOs[type == CUBE ? VAO_OBJ_CUBE : VAO_OBJ_POLYHEDRE], type);

	}
}
// Utils
// ------------------------------------------------------------

void reloadBackgroundBuffers() {
	glClearColor(BACKGROUND_COLOR.x, BACKGROUND_COLOR.y, BACKGROUND_COLOR.z, BACKGROUND_COLOR.w);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/* load an array of vertices from a text file
 */
vector<float> loadFloatsFromFile(char const *namePath) {

	vector<float> values;
	string word;
	ifstream input;
	input.exceptions(ifstream::failbit | ifstream::badbit);
	try {
		// open file
		input.open(namePath);
		if (!input.is_open()) {
			throw ifstream::failure("open file");
		}

		// read from file
		char x;
		//string word;
		float nextValue(0.0);
		while (!input.eof()) {
			// fill the word
			try {
				x = input.get();
			} catch (ifstream::failure &e) {
				// temporary solution (not good)
				word += ',';
				x = ' ';
			}
			if (x != ' ' and x != '\n' and x != '\t')
				word += x;
			else {
				// --- End of the word
				if (word.size() != 0) {
					// invalid entry
					if (word.back() != ',') {
						throw ifstream::failure("file invalid entries 2");
					}
					// convert to value
					word.replace(word.size() - 1, 1, "");
					try {
						nextValue = std::stof(word);
					} catch (invalid_argument &e) {
						throw ifstream::failure("file invalid entries 3");
					}

					// add to the tab
					values.push_back(nextValue);
					word = "";
				}
			}
		}
		input.close();

	} catch (ifstream::failure & e) {
		cout << "ERROR::FILE_NOT_SUCCESSFULLY_READ" << endl;
		input.close();
	}
	return values;
}

vector<string> loadStringsFromFile(char const *namePath) {
	cout << "  TEXTURES" << endl;
	vector<string> values;
	string s;
	ifstream input;
	input.exceptions(ifstream::failbit | ifstream::badbit);
	try {
		// open file
		input.open(namePath);
		if (!input.is_open()) {
			throw ifstream::failure("open file");
		}

		char x;
		bool inString = false;
		while (!input.eof()) {
			try {
				x = input.get();
			} catch (ifstream::failure &e) {

			}

			switch (x) {
			case '"':
				if (inString) {
					inString = false;
					values.push_back(s);
					cout << s << endl;
					s.clear();
				} else {
					inString = true;
					s.clear();
				}
				break;
			case '\n':
				break;
			default:
				s += x;
				break;
			}
		}

		input.close();
	} catch (ifstream::failure &e) {
		cout << "ERROR::VERTICES::FILE_NOT_SUCCESSFULLY_READ" << endl;
		input.close();
	}
	return values;
}

void deallocateBuffers(unsigned int nbVAO, unsigned int* firstVAO, unsigned int nbVBO, unsigned int* firstVBO,
			unsigned int nbEBO, unsigned int* firstEBO) {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	if (nbVAO != 0) {
		glDeleteVertexArrays(nbVAO, firstVAO);
	}

	if (nbVBO != 0) {
		glDeleteBuffers(nbVBO, firstVBO);
	}

	if (nbEBO != 0) {
		glDeleteBuffers(nbEBO, firstEBO);
	}
}

vector<vec3> retrievePositionsFromFile(string fileName, unsigned int nbPositions) {
	string nametmp = "res/positions/" + fileName;
	vector<float> tmp = loadFloatsFromFile(nametmp.c_str());

	vector<vec3> positions;
	for (unsigned int i = 0; i < nbPositions; i++) {
		float x = tmp[3 * i];
		float y = tmp[3 * i + 1];
		float z = tmp[3 * i + 2];

		vec3 position = vec3(x, y, z);
		positions.push_back(position);
	}
	return positions;
}

void createTextures(const vector<string>& fileNames, unsigned int* textures, unsigned int nbTextures) {
	glGenTextures(nbTextures, textures);

	for (unsigned int i = 0; i < nbTextures; i++) {
		initialiseTexture(fileNames[i], textures[i]);
	}
}

unsigned int initialiseTexture(string fileName, unsigned int texture) {
	string namePath = "res/textures/" + fileName;

	glBindTexture(GL_TEXTURE_2D, texture);

	// wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nbChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(namePath.c_str(), &width, &height, &nbChannels, 0);
	if (data) {
		GLenum format;
		if (nbChannels == 1)
			format = GL_RED;
		if (nbChannels == 3)
			format = GL_RGB;
		if (nbChannels == 4)
			format = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
		GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);
	return texture;
}

