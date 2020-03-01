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
//Camera camera(vec3(0.0f, 0.0f, 10.0f));
//float lastX = 400.0f;
//float lastY = 300.0f;
//bool firstMouse = true;
//
//// --- Settings constants
//// Screen size
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//// Background color
//const vec4 BACKGROUND_COLOR = vec4(0.2f, 0.3f, 0.3f, 1.0f);
//// unit of time
//const unsigned int RENDERING_TIME = 300;
//
//// Input
//const float MOUSE_SENSITIVITY = 0.05f;
//// Objects Rendering
//const unsigned int NB_VERTICES_FOR_CUBE = 36;
//
//// --- Time and position during time
//// time
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//// --- Settings not constants
//float texMixCoef = 0;
//bool R_WAS_PRESSED = false;
//
//// --- Other values
//unsigned int nbVertices = 0;
//
//// --- Window management
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window, Camera* camera);
//// mouse
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
//// --- Utils
//vector<float> loadVerticesf(char const *fileName);
//
///* =========================================================
// * =========================================================
// */
//
//
//// =========================================================
//// ------------------ Main ---------------------------------
//// =========================================================
//int main()
//{
//
//	// ----------------------------------------------------
//	// Initialisation
//	// ----------------------------------------------------
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
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		cout << "Failed to create GLFW window" << endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	// Set input functions
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// glad : load all OpenGL function pointers
//	// -------------------------------------------------------------
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		cout << "Failed to initialize GLAD" << endl;
//		return -1;
//	}
//
//
//	// Shaders
//	// -------------------------------------------------------------
//	Shader ourShader("include/Shaders/vShader_tuto1.glsl", "include/Shaders/fShader_tuto1.glsl");
//
//
//	// ==============================================================
//
//	// ----------------------------------------------------
//	//  Vertices
//	// ----------------------------------------------------
//
//	// Objects Position
//	// -----------------------------------------------
//	vec3 cubePositions[] = {
//		vec3( 0.0f,  0.0f,  0.0f),
//		vec3( 2.0f,  5.0f, -15.0f),
//		vec3(-1.5f, -2.2f, -2.5f),
//		vec3(-3.8f, -2.0f, -12.3f),
//		vec3( 2.4f, -0.4f, -3.5f),
//		vec3(-1.7f,  3.0f, -7.5f),
//		vec3( 1.3f, -2.0f, -2.5f),
//		vec3( 1.5f,  2.0f, -2.5f),
//		vec3( 1.5f,  0.2f, -1.5f),
//		vec3(-1.3f,  1.0f, -1.5f)
//	};
//
//
//	// Vertices into buffer
//	// -----------------------------------------------
//	// --- Vertices
//	vector<float> verticesTmp = loadVerticesf("res/vertices/cubeTexture.txt");
//	float vertices[verticesTmp.size()];
//	copy(verticesTmp.begin(), verticesTmp.end(), vertices);
//
//	// --- Indexes
//	unsigned int indices[] = {
//			0, 2, 1,
//			1, 2, 3
//	};
//
//	nbVertices = sizeof(indices)/sizeof(*indices);
//
//
//	// Vertex buffers
//	// ------------------------------------------------
//	unsigned int VBO(0); glGenBuffers(1, &VBO);
//	unsigned int VAO(0); glGenVertexArrays(1, &VAO);
//	unsigned int EBO(0); glGenBuffers(1, &EBO);
//
//	// --- Bindings
//	// Vertex array object
//	glBindVertexArray(VAO);
//
//	// Vertex buffer object
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	/* TODO EBO
//	// Element buffer object
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	*/
//
//	// --- Interpretation of vertex datas
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
////	// color attribute TODO color
////	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
////	glEnableVertexAttribArray(1);
//
//	// texture coordinates
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//
//	// --- Unbind Buffers
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//
//	// ====================================================================
//
//
//	// ----------------------------------------------------
//	//  Texture
//	// ----------------------------------------------------
//
//	// --- Texture 1
//	// Creating textures and binding
//	unsigned int texture1(0);
//	glGenTextures(1, &texture1);
//	glBindTexture(GL_TEXTURE_2D, texture1);
//
//	// Options
//	// wrapping options
//	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f};
//	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//	// filtering options
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//	// Loading image
//	int width(0), height(0), nrChannels(0);
//	unsigned char *data = stbi_load("res/textures/container.jpg", &width, &height, &nrChannels,0);
//	if (data) {
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
//				GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	} else {
//		cout << "Failed to load texture 1" << endl;
//	}
//	// free memory
//	stbi_image_free(data);
//
//	// --- Texture 2
//	// Creating textures and binding
//	unsigned int texture2(0);
//	glGenTextures(1, &texture2);
//	glBindTexture(GL_TEXTURE_2D, texture2);
//
//	// Options
//	// wrapping options
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	// filtering options
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	// Loading image
//	stbi_set_flip_vertically_on_load(true);
//	data = stbi_load("res/textures/awesomeface.png", &width, &height, &nrChannels, 0);
//	if (data) {
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
//				GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	} else {
//		cout << "Failed to load texture 2" << endl;
//	}
//	// free memory
//	stbi_image_free(data);
//
//	// ==============================================================
//
//
//	// ------------------------------------------------
//	// Local to Clip space
//	// ------------------------------------------------
//
//	// --- Model
//	mat4 model = mat4(1.0f);
//	model = rotate(model, radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));
//
//	// --- View
//	// nothing now
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
//	// --- Rendering Settings
//	// Modes
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	glEnable(GL_DEPTH_TEST);
//
//	ourShader.use();
//
//	// Texture
//	ourShader.setInt("ourTexture1", 0);
//	ourShader.setInt("ourTexture2", 1);
//
//	// Transformation
//	unsigned int transformLoc = glGetUniformLocation(ourShader.getID(), "transform");
//	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(model));
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
//		processInput(window, &camera);
//
//		// transformations
//		// --------------------------------------------
//
//		// --- Model
//		model = mat4(1.0f);
//		ourShader.setMat4("model", model);
//
//		// --- View
//		camera.update(currentFrame);
//		ourShader.setMat4("view", camera.getViewMat());
//
//		// --- Projection
//		projection = perspective(radians(camera.getFov()),(float)SCR_WIDTH/SCR_HEIGHT, NEAR_PLANE, FAR_PLANE);
//		ourShader.setMat4("projection", projection);
//
//		// Rendering
//		//----------------------------------------------
//		// --- Reload buffers
//		glClearColor(BACKGROUND_COLOR.x, BACKGROUND_COLOR.y, BACKGROUND_COLOR.z, BACKGROUND_COLOR.w);
//		glClear(GL_COLOR_BUFFER_BIT);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// Bind Textures
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//
//		// --- Settings
//		ourShader.use();
//
//		// textures mixing
//		ourShader.setFloat("mixValue", texMixCoef);
//
//		// Render Objects
//		glBindVertexArray(VAO);
//		for (unsigned int i = 0; i < 10; i++) {
//			mat4 model(1.0f);
//
//			// place the object to its position
//			model = translate(model, cubePositions[i]);
//
//			// rotate it (or not)
//			float angle = radians(20.0f * i);
//			if (i%3 == 0) {
//				angle += currentFrame*radians(50.0f) * (i + 0.5) * 0.2;
//			}
//			model = rotate(model, angle, vec3(1.0f, 0.3f, 0.5f));
//
//
//			// apply and draw
//			ourShader.setMat4("model", model);
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//		//glDrawElements(GL_TRIANGLES, nbVertices, GL_UNSIGNED_INT, 0);
//
//
//		// glfw : check and call events and swap the buffers
//		// --------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// Unbindings and de-allocate all resources
//	// -----------------------------------------------------
//	glBindVertexArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//
//
//	// glfw : terminate, clearing all previously allocated GLFW resources
//	// -------------------------------------------------------
//	glfwTerminate();
//	return 0;
//}
//
///* =========================================================
// * =========================================================
// */
//
//
//// =========================================================
//// ---------------- Other functions ---------------------------------
//// =========================================================
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
//void processInput(GLFWwindow* window, Camera* camera) {
//	// Quit
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//
//	// increase/decrease mixing
//	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
//		texMixCoef += 0.01;
//		if (texMixCoef > 1.0f) texMixCoef = 1.0f;
//	}
//	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
//		texMixCoef -= 0.01;
//		if (texMixCoef < 0.0f) texMixCoef = 0.0f;
//	}
//
//	// Change mode
//	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
//		if (!R_WAS_PRESSED) {
//			R_WAS_PRESSED = true;
//			// switch camera mode
//			camera->switchMode();
//		}
//	} else {
//		if (R_WAS_PRESSED) {
//			R_WAS_PRESSED = false;
//		}
//	}
//
//	// linear moving
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera->forward(deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera->backward(deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera->toTheLeft(deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera->toTheRight(deltaTime);
//}
//
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
//// Utils
//// ------------------------------------------------------------
//
///* load an array of vertices from a text file
// */
//vector<float> loadVerticesf(char const *fileName) {
//	vector<float> values;
//	string word;
//	ifstream input;
//	input.exceptions(ifstream::failbit | ifstream::badbit);
//	try {
//		// open file
//		input.open(fileName);
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
