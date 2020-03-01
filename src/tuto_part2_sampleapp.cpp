//
////GLAD
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <ImageReader/stb_image.h>
//
////GLM
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
////Other libraries
//#include <iostream>
//#include <climits>
//#include <cmath>
//#include <vector>
//#include <fstream>
//
////Other classes
//#include "Shader.h"
//#include "Camera.h"
//
//using namespace std;
//using namespace glm;
//
//// --- Camera
//Camera camera(vec3(0.0f, 0.0f, 5.0f));
//float lastX = 400.0f;
//float lastY = 300.0f;
//bool firstMouse = true;
//
//// Type of Light
//enum Lighting { DIRECTION, POINT, SPOT, MULTIPLE };
//
//// Geometries
//enum Geometry { CUBE, POLYHEDRE };
//
//// Settings constants
//// ------------------------------------------------------------
//
//// Screen size
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//// Background Color
//const vec4 BACKGROUND_COLOR = vec4(0.1f, 0.1f, 0.1f, 1.0f);
//// unit of time
//const unsigned int RENDERING_TIME = 300;
//
//// Input
//const float MOUSE_SENSITIVITY = 0.05f;
//
//// --- Buffers
//const unsigned int NB_VAOS = 3;
//const unsigned int NB_VBOS = 2;
//const unsigned int VAO_LIGHT = 0;
//const unsigned int VAO_OBJ_CUBE = 1;
//const unsigned int VAO_OBJ_POLYHEDRE = 2;
//const unsigned int VBO_CUBE = 0;
//const unsigned int VBO_POLYHEDRE = 1;
//
//// --- Vertices files
//const unsigned int NB_VERTICES_CUBE = 36;
//const unsigned int NB_VERTICES_POLYHEDRE = 60;
//const unsigned int NB_FLOATS_ONE_VERTICE = 8;
//const unsigned int NB_FLOATS_POSITION = 3;
//const unsigned int NB_FLOATS_NORMAL = 3;
//const unsigned int NB_FLOATS_TEXCOORDS = 2;
//const unsigned int LAYOUT_POSITION  = 0;
//const unsigned int LAYOUT_NORMAL = 1;
//const unsigned int LAYOUT_TEXCOORDS = 2;
//const unsigned int OFFSET_POSITION = 0;
//const unsigned int OFFSET_NORMAL = NB_FLOATS_POSITION;
//const unsigned int OFFSET_TEXCOORDS = OFFSET_NORMAL + NB_FLOATS_NORMAL;
//
//// --- Object
//const vec3 OBJECT_AMBIENT = 	vec3(1.0f, 0.5f, 0.31f);
//const vec3 OBJECT_DIFFUSE = 	vec3(1.0f, 0.5f, 0.31f);
//const float OBJECT_SHININESS =  32.0f;
//
//// --- World elements settings
//const unsigned int NB_OBJECTS = 		10;
//const unsigned int NB_POINTLIGHTS = 	4;
//const bool ROTATE_OBJECTS = 			true;
//const bool ROTATE_LIGHTS = 				false;
//const vec3 OBJECTS_SCALE = 				vec3(1.0f);
//const vec3 LIGHTS_SCALE =				vec3(0.2f);
//const char* OBJECTS_POS_FILE = 			"objects_positions.txt";
//const char*	POINTLIGHTS_POS_FILE =		"pointLights_positions.txt";
//
//// --- Lightning
//const vec3 LIGHT_PROPER_COLOR = 		vec3(1.0f, 1.0f, 1.0f);
//const vec3 LIGHT_AMBIENT =				vec3(0.2f, 0.2f, 0.2f);
//const vec3 LIGHT_DIFFUSE = 				vec3(0.5f, 0.5f, 0.5f);
//const vec3 LIGHT_SPECULAR = 			vec3(1.0f, 1.0f, 1.0f);
//const vec3 LIGHT_INITIAL_POSITION =		vec3(1.2f, 1.0f, 2.0f);
//const vec3 LIGHT_DIRECTION =			vec3(-0.2f,-1.0f,-0.3f);
//const float LIGHT_CONSTANT = 			1.0f;
//const float LIGHT_LINEAR =				0.5f;
//const float LIGHT_QUADRATIC =			0.052f;
//const float LIGHT_CUTOFF = 				12.5f;
//const float LIGHT_OUTERCUTOFF = 		17.5f;
//
//// --- Time and position during time
//// time
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//// --- Settings not constants
//float texMixCoef = 0;
//
//// --- Other values
//unsigned int nbVertices = 0;
//
//// ========================================================================
//
//// -------------------------------------------------------------
//// Functions
//// -------------------------------------------------------------
//
//// --- Window management
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//// mouse
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
//
//// --- Initialisations and firsts settings
//GLFWwindow* initialisation();
//unsigned int segmentVAO();
//void geometryIntoBuffer(unsigned int* VBOs, unsigned int index, string fileName);
//void setLightAttributes(unsigned int lightVAO, unsigned int VBO);
//void setObjectAttributes(unsigned int objectVAO, unsigned int VBO);
//unsigned int createTexture(const char* namePath);
//void setInitialPositionsAndColors(Shader* objectShader, Shader* lightShader, Lighting lightType,
//								  string lightName = "light", vector<vec3> positions = vector<vec3>(0));
//void setDirectionalLighting(Shader* objectShader, string lightName);
//void setPointLighting(Shader* objectShader, string lightName, vec3 position = LIGHT_INITIAL_POSITION);
//void setSpotLighting(Shader* objectShader, string lightName, bool useCamera = true,
//					 vec3 position = LIGHT_INITIAL_POSITION, vec3 direction = LIGHT_DIRECTION);
//void setMultipleLighting(Shader* objectShader, vector<vec3> positions, string lightName, unsigned int nbLights = NB_POINTLIGHTS);
//void setLightingBasicProperties(Shader* objectShader, string lightName);
//
//// --- Light and Object updates
//mat4 lightModelUpdate(vec3 lightPos);
//void updateObjectShaderPosition(Shader* objectShader, mat4 model, mat4 view, mat4 projection);
//void updateLightShaderPosition(Shader* lightShader, mat4 model, mat4 view, mat4 projection);
//
//// --- Drawing
//void drawElement(Shader* elemShader, unsigned int elemVAO);
//void drawMultipleElements(Shader* elemShader, unsigned int VAO, vector<vec3> positions, unsigned int nbElements,
//						  bool rotate = false, vec3 scale = vec3(1.0f));
//
//// --- Utils
//void reloadBackgroundBuffers();
//void deallocateBuffers(unsigned int nbVAO, unsigned int* firstVAO, unsigned int nbVBO, unsigned int* firstVBO,
//					   unsigned int nbEBO, unsigned int* firstEBO);
//vector<float> loadFloatsFromFile(char const *namePath);
//vector<vec3> retrievePositionsFromFile(string fileName, unsigned int nbPositions);
//
//void drawSegment(glm::vec3 p1, glm::vec3 p2, Shader* shader, unsigned int VAO, glm::mat4 view, glm::mat4 projection) {
//	mat4 model = mat4(1.0f);
//
//	vec3 dirP1toP2 = p2 - p1;
//
//	vec3 mediumPoint = 0.5f * dirP1toP2;
//	mediumPoint += p1;
//	model = translate(model, mediumPoint);
//
//	float angle = acos(dot(normalize(dirP1toP2), vec3(1.0f, 0.0f, 0.0f)));
//	if ((dirP1toP2.x > 0 && dirP1toP2.z > 0) or
//		(dirP1toP2.x < 0 && dirP1toP2.z > 0)) {
//
//		angle = -angle;
//	}
//
//	model = rotate(model, angle, vec3(0.0f, 1.0f, 0.0f));
//
//	float l = length(dirP1toP2);
//	model = scale(model, vec3(l, 1.0f, 1.0f));
//
//	// apply transformations to the segment
//	shader->use();
//	shader->setMat4("model", model);
//	shader->setMat4("view", view);
//	shader->setMat4("projection", projection);
//
//	// Rendering
//	glBindVertexArray(VAO);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//
//	// unbind
//	glBindVertexArray(0);
//}
//
//// =======================================================================================
//// -------------------------------------- Main ----------------------------------------
//// =======================================================================================
//
//int main()
//{
//
//	// Initialisation
//	GLFWwindow* window = initialisation();
//	if (window == NULL) {
//		glfwTerminate();
//		return -1;
//	}
//
//	// Shaders
//	// ----------------------------------------------
//
//	Shader lightShader("vertexShaders/vLight.glsl",
//					   "fragmentShaders/fLight.glsl");
//	Shader objectShader("vertexShaders/vObjectTex.glsl",
//						"fragmentShaders/fObjectTex_multipleLights.glsl");
//	Shader lineSegShader("vertexShaders/vLineSeg.glsl",
//			   	   	   	 "fragmentShaders/fLineSeg.glsl");
//
//	// Buffers
//	// ------------------------------------------------
//	unsigned int VBOs[NB_VBOS];
//	glGenBuffers(NB_VBOS, VBOs);
//
//	// a special VAO for segments
//	unsigned int segVAO = segmentVAO();
//
//	unsigned int VAOs[NB_VAOS]; // VAOS[0] is the light, VAO[1] is the cube
//	glGenVertexArrays(NB_VAOS, VAOs);
//
//	// fill the buffers with vertices loaded from file
//	geometryIntoBuffer(VBOs, VBO_CUBE, "cubeNormalsAndTexture.txt");
//	//TODO
//
//	// Light attributes
//	setLightAttributes(VAOs[VAO_LIGHT], VBOs[VBO_CUBE]);
//
//	// Object Attributes
//	setObjectAttributes(VAOs[VAO_OBJ_CUBE], VBOs[VBO_CUBE]);
//	setObjectAttributes(VAOs[VAO_OBJ_POLYHEDRE], VBOs[VBO_POLYHEDRE]);
//
//	// --- Unbind Buffers
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//
//	// Texture
//	// ------------------------------------------------
//	unsigned int texture = createTexture("res/textures/container.png");
//	unsigned int texture_specular = createTexture("res/textures/container_specular.png");
//
//	// ==============================================================
//
//
//	// ------------------------------------------------
//	// Local to Clip space
//	// ------------------------------------------------
//
//	// --- Model
//	mat4 objectModel = mat4(1.0f);
//
//	mat4 lightModel = mat4(1.0f);
//	lightModel = translate(lightModel, LIGHT_INITIAL_POSITION);
//	lightModel = scale(lightModel, LIGHTS_SCALE);
//
//	// --- View
//	// wiil get from the camera
//	mat4 view = mat4(1.0f);
//
//	// --- Projection
//	mat4 projection;
//	projection = perspective(radians(camera.getFov()),(float)SCR_WIDTH/SCR_HEIGHT, NEAR_PLANE, FAR_PLANE);
//
//	// ==============================================================
//
//
//	// ------------------------------------------------
//	// Rendering
//	// ------------------------------------------------
//
//	//vec3 lightPos = LIGHT_INITIAL_POSITION;
//	vector<vec3> lightsPositions = retrievePositionsFromFile("pointLights_positions.txt", NB_POINTLIGHTS);
//
//	// --- Rendering Settings
//	// Modes
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	glEnable(GL_DEPTH_TEST);
//
//	// Light and Colors
//	setInitialPositionsAndColors(&objectShader, &lightShader, DIRECTION, "dirLight");
//	setInitialPositionsAndColors(&objectShader, NULL, MULTIPLE, "pointLights", lightsPositions);
//
//	// Rendering loop
//	// -----------------------------------------------
//	while (!glfwWindowShouldClose(window)) {
//		// useful constants
//		double currentFrame =  glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		// --------------------------------------------
//		processInput(window);
//
//
//		// transformations
//		// --------------------------------------------
//
//		// transformations update
//		//lightModel = lightModelUpdate(lightPos);
//		projection = perspective(radians(camera.getFov()),(float)SCR_WIDTH/SCR_HEIGHT, NEAR_PLANE, FAR_PLANE);
//		view = camera.getViewMat();
//
//		// object
//		updateObjectShaderPosition(&objectShader, objectModel, view, projection);
//
//		// light
//		updateLightShaderPosition(&lightShader, lightModel, view, projection);
//
//
//		// Lightning and Colors
//		//----------------------------------------------
//		objectShader.use();
//		objectShader.setVec3("viewPos", camera.getPos());
//
//		// Rendering
//		//----------------------------------------------
//
//		// --- Reload buffers
//		reloadBackgroundBuffers();
//
//		// --- Drawing
//		// lights
//		drawMultipleElements(&lightShader, VAOs[0], lightsPositions, NB_POINTLIGHTS, false, LIGHTS_SCALE);
//		// objects
//		drawMultipleElements(&objectShader, VAOs[1], retrievePositionsFromFile("objects_positions.txt", NB_OBJECTS), NB_OBJECTS, true, OBJECTS_SCALE);
//
//		drawSegment(vec3(0.0f, 5.0f, 0.0f), vec3(10.0f, 5.0f, 20.0f), &lineSegShader,segVAO ,view, projection);
//
//		// --- Textures
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture_specular);
//
//		// glfw : check and call events and swap the buffers
//		// -------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// Unbindings and de-allocate all resources
//	// -----------------------------------------------------
//	deallocateBuffers(NB_VAOS, VAOs, NB_VBOS, VBOs, 0, NULL);
//
//
//	// glfw : terminate, clearing all previously allocated GLFW resources
//	// -------------------------------------------------------
//	glfwTerminate();
//	return 0;
//}
//
//
//// ===========================================================================================
//// ---------------------------------- Functions ----------------------------------------
//// ===========================================================================================
//
////	Window management
//// ------------------------------------------------------------
//
///* glfw : whenever the window size changed (by OS or user resize) this
// * callback function executes
// */
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//
///* process all input : query GLFW whether relevant keys are pressed/released
// * this frame and react accordingly
// */
//void processInput(GLFWwindow* window) {
//	// Quit
//	// -----------------------------------------------------------
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//
//	// increase/decrease mixing
//	// -----------------------------------------------------------
//	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
//		texMixCoef += 0.01;
//		if (texMixCoef > 1.0f) texMixCoef = 1.0f;
//	}
//	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
//		texMixCoef -= 0.01;
//		if (texMixCoef < 0.0f) texMixCoef = 0.0f;
//	}
//
//	// linear moving
//	// -----------------------------------------------------------
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.forward(deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.backward(deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.toTheLeft(deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.toTheRight(deltaTime);
//}
//
///* process the movements of the mouse
// */
//void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//	if (firstMouse) {
//		lastX = xpos;
//		lastY = ypos;
//
//		firstMouse = false;
//	}
//
//	float xOffset = xpos-lastX;
//	float yOffset = lastY - ypos; 	// reversed since y-coordinates range
//									// bottom to top
//	lastX = xpos;
//	lastY = ypos;
//
//	xOffset *= MOUSE_SENSITIVITY;
//	yOffset *= MOUSE_SENSITIVITY;
//
//	camera.updateYawAndPitch(xOffset, yOffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
//	camera.updateFov(-yOffset);
//}
//
//
//// Initialisation and firsts Settings
//// ------------------------------------------------------------
///*
// * First initilisation
// */
//GLFWwindow* initialisation() {
//
//	// glfw : initialise GLFW and configuring
//	// --------------------------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// glfw : window creation
//	// --------------------------
//
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		cout << "Failed to create GLFW window" << endl;
//		glfwTerminate();
//		return NULL;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	// Set input functions
//	// capture the mouse
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// glad : load all OpenGL function pointers
//	// -------------------------------------------------------------
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		cout << "Failed to initialize GLAD" << endl;
//		return NULL;
//	}
//
//	return window;
//}
//
//unsigned int segmentVAO() {
//	vec3 p1 = vec3(-0.5f, 0.0f, -0.1f);
//	vec3 p2 = vec3(-0.5f, 0.0f, 0.1f);
//	vec3 p3 = vec3(-0.5f, 0.2f, -0.1f);
//	vec3 p4 = vec3(-0.5f, 0.2, 0.1f);
//
//	vec3 p5 = vec3(0.5f, 0.0f, -0.1f);
//	vec3 p6 = vec3(0.5f, 0.0f, 0.1f);
//	vec3 p7 = vec3(0.5f, 0.2f, -0.1f);
//	vec3 p8 = vec3(0.5f, 0.2, 0.1f);
//
//	float vertices[] = {
//			p1.x, p1.y, p1.z,
//			p2.x, p2.y, p2.z,
//			p3.x, p3.y, p3.z,
//			p3.x, p3.y, p3.z,
//			p2.x, p2.y, p2.z,
//			p4.x, p4.y, p4.z,  // left
//
//			p5.x, p5.y, p5.z,
//			p6.x, p6.y, p6.z,
//			p7.x, p7.y, p7.z,
//			p7.x, p7.y, p7.z,
//			p6.x, p6.y, p6.z,
//			p8.x, p8.y, p8.z,  // right
//
//			p4.x, p4.y, p4.z,
//			p8.x, p8.y, p8.z,
//			p3.x, p3.y, p3.z,
//			p3.x, p3.y, p3.z,
//			p8.x, p8.y, p8.z,
//			p7.x, p7.y, p7.z,  // top
//
//			p1.x, p1.y, p1.z,
//			p2.x, p2.y, p2.z,
//			p6.x, p6.y, p6.z,
//			p6.x, p6.y, p6.z,
//			p2.x, p2.y, p2.z,
//			p5.x, p5.y, p5.z, // down
//
//			p1.x, p1.y, p1.z,
//			p5.x, p5.y, p5.z,
//			p3.x, p3.y, p3.z,
//			p3.x, p3.y, p3.z,
//			p5.x, p5.y, p5.z,
//			p7.x, p7.y, p7.z, //back
//
//			p2.x, p2.y, p2.z,
//			p6.x, p6.y, p6.z,
//			p4.x, p4.y, p4.z,
//			p4.x, p4.y, p4.z,
//			p6.x, p6.y, p6.z,
//			p8.x, p8.y, p8.z // front
//	};
//
//	unsigned int VAO, VBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	// bind and set the buffers
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindVertexArray(0);
//	glDeleteBuffers(1, &VBO);
//	return VAO;
//}
//
//void geometryIntoBuffer(unsigned int* VBOs, unsigned int index, string fileName) {
//	string nameTmp = "res/vertices/" + fileName;
//
//	// vertices
//	vector<float> verticesTmp;
//	verticesTmp = loadFloatsFromFile(nameTmp.c_str());
//	float vertices[verticesTmp.size()];
//	copy(verticesTmp.begin(), verticesTmp.end(), vertices);
//
//	// into buffer
//	glBindBuffer(GL_ARRAY_BUFFER, VBOs[index]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//}
//
//void setLightAttributes(unsigned int lightVAO, unsigned int VBO) {
//	glBindVertexArray(lightVAO);
//	// VBO
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	// position
//	glVertexAttribPointer(LAYOUT_POSITION, NB_FLOATS_POSITION, GL_FLOAT,
//			GL_FALSE, NB_FLOATS_ONE_VERTICE * sizeof(float),
//			(void*) (OFFSET_POSITION * sizeof(float)));
//	glEnableVertexAttribArray(LAYOUT_POSITION);
//
//	//unbins
//	glBindVertexArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
//
//void setObjectAttributes(unsigned int objectVAO, unsigned int VBO) {
//	glBindVertexArray(objectVAO);
//	// VBO
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//	// Position
//	glVertexAttribPointer(LAYOUT_POSITION, NB_FLOATS_POSITION, GL_FLOAT,
//			GL_FALSE, NB_FLOATS_ONE_VERTICE * sizeof(float),
//			(void*) (OFFSET_POSITION * sizeof(float)));
//	glEnableVertexAttribArray(LAYOUT_POSITION);
//
//	// Normals
//	glVertexAttribPointer(LAYOUT_NORMAL, NB_FLOATS_NORMAL, GL_FLOAT, GL_FALSE,
//			NB_FLOATS_ONE_VERTICE * sizeof(float),
//			(void*) (OFFSET_NORMAL * sizeof(float)));
//	glEnableVertexAttribArray(LAYOUT_NORMAL);
//
//	// Texture Coords
//	glVertexAttribPointer(LAYOUT_TEXCOORDS, NB_FLOATS_TEXCOORDS, GL_FLOAT,
//			GL_FALSE, NB_FLOATS_ONE_VERTICE * sizeof(float),
//			(void*) (OFFSET_TEXCOORDS * sizeof(float)));
//	glEnableVertexAttribArray(LAYOUT_TEXCOORDS);
//
//	// --- Unbinds
//	glBindVertexArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
//
//unsigned int createTexture(const char* namePath) {
//	unsigned int texture;
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//
//	// wrapping parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	// texture filtering parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	// load image, create texture and generate mipmaps
//	int width, height, nbChannels;
//	stbi_set_flip_vertically_on_load(true);
//	unsigned char* data = stbi_load(namePath, &width, &height, &nbChannels, 0);
//	if (data) {
//		GLenum format;
//		if (nbChannels == 1) format = GL_RED;
//		if (nbChannels == 3) format = GL_RGB;
//		if (nbChannels == 4) format = GL_RGBA;
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	} else {
//		cout << "Failed to load texture" << endl;
//	}
//	stbi_image_free(data);
//	return texture;
//}
//
//void setInitialPositionsAndColors(Shader* objectShader, Shader* lightShader, Lighting lightType, string lightName,
//								  vector<vec3> lightsPos) {
//
//	// Object
//	// ------------------------------------------------
//
//	objectShader->use();
//	// --- material properties
//	objectShader->setInt("material.diffuse", 0); // set texture
//	objectShader->setInt("material.specular", 1); // set specular distribution texture
//	objectShader->setFloat("material.shininess", OBJECT_SHININESS);
//
//	// --- light properties
//	switch(lightType) {
//		case DIRECTION : setDirectionalLighting(objectShader, lightName); break;
//		case POINT : setPointLighting(objectShader, lightName); break;
//		case SPOT : setSpotLighting(objectShader, lightName); break;
//		case MULTIPLE : setMultipleLighting(objectShader, lightsPos, lightName, NB_POINTLIGHTS);
//	}
//
//	// Light
//	// -------------------------------------------------
//	if (lightShader != NULL) {
//		lightShader->use();
//		lightShader->setVec3("lightColor", LIGHT_PROPER_COLOR);
//	}
//}
//
//void setDirectionalLighting(Shader* objectShader, string lightName) {
//	setLightingBasicProperties(objectShader, lightName);
//
//	objectShader->setVec3(lightName + ".direction", LIGHT_DIRECTION);
//}
//
//void setPointLighting(Shader* objectShader, string lightName, vec3 position) {
//	setLightingBasicProperties(objectShader, lightName);
//
//	objectShader->setVec3(lightName + ".position", position);
//
//	objectShader->setFloat(lightName + ".constant", LIGHT_CONSTANT);
//	objectShader->setFloat(lightName + ".linear", LIGHT_LINEAR);
//	objectShader->setFloat(lightName + "quadratic", LIGHT_QUADRATIC);
//}
//
//void setSpotLighting(Shader* objectShader, string lightName, bool useCamera, vec3 position, vec3 direction) {
//	setLightingBasicProperties(objectShader, lightName);
//
//	if (useCamera) {
//		objectShader->setVec3(lightName + ".position", camera.getPos());
//		objectShader->setVec3(lightName + ".direction", camera.getDirection());
//	} else {
//		objectShader->setVec3(lightName + ".position", position);
//		objectShader->setVec3(lightName + ".direction", direction);
//	}
//
//	objectShader->setFloat(lightName + ".constant", LIGHT_CONSTANT);
//	objectShader->setFloat(lightName + ".linear", LIGHT_LINEAR);
//	objectShader->setFloat(lightName + "quadratic", LIGHT_QUADRATIC);
//}
//
//void setMultipleLighting(Shader* objectShader, vector<vec3> positions, string lightName, unsigned int nbLights) {
//	for (unsigned int i = 0; i < nbLights; i++) {
//		string name = lightName + "[";
//		name += to_string(i) + "]";
//		setPointLighting(objectShader, name, positions[i]);
//	}
//}
//
//void setLightingBasicProperties(Shader* objectShader, string lightName) {
//	objectShader->setVec3(lightName + ".ambient", LIGHT_AMBIENT);
//	objectShader->setVec3(lightName + ".diffuse", LIGHT_DIFFUSE);
//	objectShader->setVec3(lightName + ".specular", LIGHT_SPECULAR);
//
//	objectShader->setVec3("viewPos", camera.getPos());
//}
//
//
//// Light and objects update
//// ------------------------------------------------------------
//mat4 lightModelUpdate(vec3 lightPos) {
//	mat4 lightModel = mat4(1.0f);
//	lightModel = translate(lightModel, lightPos);
//	lightModel = scale(lightModel, LIGHTS_SCALE);
//
//	return lightModel;
//}
//
//void updateObjectShaderPosition(Shader* objectShader, mat4 model, mat4 view, mat4 projection) {
//	objectShader->use();
//	objectShader->setMat4("model", model);
//	objectShader->setMat4("view", view);
//	objectShader->setMat4("projection", projection);
//}
//
//void updateLightShaderPosition(Shader* lightShader, mat4 model, mat4 view, mat4 projection) {
//	lightShader->use();
//	lightShader->setMat4("model", model);
//	lightShader->setMat4("view", view);
//	lightShader->setMat4("projection", projection);
//}
//
//// Drawing
//// ------------------------------------------------------------
//
//void drawElement(Shader* elemShader, unsigned int elemVAO) {
//	elemShader->use();
//	glBindVertexArray(elemVAO);
//	glDrawArrays(GL_TRIANGLES, 0, NB_VERTICES_CUBE);
//}
//
//void drawMultipleElements(Shader* elemShader, unsigned int VAO, vector<vec3> positions, unsigned int nbElements,
//						  bool rotate, vec3 scale) {
//	int nb = nbElements;
//		for(int i = 0; i < nb; i++) {
//			mat4 model = mat4(1.0f);
//			model = translate(model, positions[i]);
//
//			if (rotate) {
//				float angle = 20.0f * i;
//				model = glm::rotate(model, radians(angle), vec3(1.0f, 0.3f, 0.5f));
//			}
//			model = glm::scale(model, scale);
//
//			elemShader->use();
//			elemShader->setMat4("model", model);
//
//			drawElement(elemShader, VAO);
//		}
//}
//
//// Utils
//// ------------------------------------------------------------
//void reloadBackgroundBuffers() {
//	glClearColor(BACKGROUND_COLOR.x, BACKGROUND_COLOR.y, BACKGROUND_COLOR.z, BACKGROUND_COLOR.w);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
///* load an array of vertices from a text file
// */
//vector<float> loadFloatsFromFile(char const *namePath) {
//
//	vector<float> values;
//	string word;
//	ifstream input;
//	input.exceptions(ifstream::failbit | ifstream::badbit);
//	try {
//		// open file
//		input.open(namePath);
//		if (!input.is_open()) {
//			throw ifstream::failure("open file");
//		}
//
//		// read from file
//		char x;
//		//string word;
//		float nextValue(0.0);
//		while (!input.eof()) {
//			// fill the word
//			try {
//				x = input.get();
//			}
//			catch (ifstream::failure &e) {
//				// temporary solution (not good)
//				word += ',';
//				x = ' ';
//			}
//			if (x != ' ' and x != '\n')
//				word += x;
//			else {
//				// --- End of the word
//				if (word.size() != 0) {
//					// invalid entry
//					if (word.back() != ',') {
//						throw ifstream::failure("file invalid entries 2");
//					}
//					// convert to value
//					word.replace(word.size() - 1, 1, "");
//					try {
//						nextValue = std::stof(word);
//					} catch (invalid_argument &e) {
//						throw ifstream::failure("file invalid entries 3");
//					}
//
//					// add to the tab
//					values.push_back(nextValue);
//					word = "";
//				}
//			}
//		}
//		input.close();
//
//	} catch (ifstream::failure & e) {
//		cout << "ERROR::VERTICES::FILE_NOT_SUCCESSFULLY_READ" << endl;
//		input.close();
//	}
//	return values;
//}
//
//void deallocateBuffers(unsigned int nbVAO, unsigned int* firstVAO, unsigned int nbVBO, unsigned int* firstVBO,
//					   unsigned int nbEBO, unsigned int* firstEBO) {
//	glBindVertexArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	if (nbVAO != 0) {
//		glDeleteVertexArrays(nbVAO, firstVAO);
//	}
//
//	if (nbVBO != 0) {
//		glDeleteBuffers(nbVBO, firstVBO);
//	}
//
//	if (nbEBO != 0) {
//		glDeleteBuffers(nbEBO, firstEBO);
//	}
//}
//
//vector<vec3> retrievePositionsFromFile(string fileName, unsigned int nbPositions) {
//	string nametmp = "res/positions/" + fileName;
//	vector<float> tmp = loadFloatsFromFile(nametmp.c_str());
//
//	vector<vec3> positions;
//	for (unsigned int i = 0; i < nbPositions; i++) {
//		float x = tmp[3 * i];
//		float y = tmp[3 * i + 1];
//		float z = tmp[3 * i + 2];
//
//		vec3 position = vec3(x, y, z);
//		positions.push_back(position);
//	}
//	return positions;
//}
//
//
