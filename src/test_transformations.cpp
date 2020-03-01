///*
// * test_transformations.cpp
// *
// *  Created on: Dec 12, 2019
// *      Author: sophie
// */
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
//#include "Shader.h"
//
//using namespace std;
//using namespace glm;
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//const unsigned int NB_VERTICES = 12;
//const unsigned int AXES_NB_VERTICES = 36;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//GLFWwindow* initialisation();
//void processInput(GLFWwindow* window);
//void displayMatrix3(mat3 matrix, string name = "");
//
//vec3 BACKGROUND_COLOR = vec3(0.2f, 0.2f, 0.2f);
//
//int main() {
//
//	// Initialisation
//	GLFWwindow* window = initialisation();
//	if (window == NULL) {
//		glfwTerminate();
//		return -1;
//	}
//
//	// Shader
//	Shader shaderTriangles("include/Shaders/vertexShaders/vTestTransformations.glsl",
//				  "include/Shaders/fragmentShaders/fTestTransformations.glsl");
//
//	// Buffers
//	unsigned int VBOs[2];
//	unsigned int VAOs[2];
//	glGenBuffers(2, VBOs);
//	glGenVertexArrays(2, VAOs);
//
//	glBindVertexArray(VAOs[0]);
//
//	float verticesTriangles[] = {
//			-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,
//			-0.3f, 0.5f,  		1.0f, 0.0f, 0.0f,
//			-0.3f, -0.5f,		1.0f, 0.0f, 0.0f,
//
//			-0.5f, 0.5f, 		0.0f, 1.0f, 0.0f,
//			-0.5f, -0.5f, 		0.0f, 1.0f, 0.0f,
//			-0.3f, -0.5f, 		0.0f, 1.0f, 0.0f,
//
//			-0.3f, 0.5f, 		0.0f, 0.0f, 1.0f,
//			-0.3f, 0.3f, 		0.0f, 0.0f, 1.0f,
//			0.2f, 0.5f,			0.0f, 0.0f, 1.0f,
//
//			-0.3f, 0.3f, 		0.9f, 0.0f, 0.7f,
//			0.2f, 0.5f, 		0.9f, 0.0f, 0.7f,
//			0.2f, 0.3f, 		0.9f, 0.0f, 0.7f
//	};
//
//	// binding
//	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangles), verticesTriangles, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (2* sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	// axes
//	glBindVertexArray(VAOs[1]);
//
//	float axeVertices[] = {
//			-1.0f, 0.0f,		1.0f, 1.0f, 1.0f,
//			1.0f, 0.0f,			1.0f, 1.0f, 1.0f,
//			0.0f, -1.0f,		1.0f, 1.0f, 1.0f,
//			0.0f, 1.0f, 		1.0f, 1.0f, 1.0f,
//
//			0.2, 0.05f,			1.0f, 1.0f, 1.0f,
//			0.2, -0.05f, 		1.0f, 1.0f, 1.0f,
//			0.4, 0.05f,			1.0f, 1.0f, 1.0f,
//			0.4, -0.05f, 		1.0f, 1.0f, 1.0f,
//			0.6, 0.05f,			1.0f, 1.0f, 1.0f,
//			0.6, -0.05f, 		1.0f, 1.0f, 1.0f,
//			0.8, 0.05f,			1.0f, 1.0f, 1.0f,
//			0.8, -0.05f, 		1.0f, 1.0f, 1.0f,
//
//			-0.2, 0.05f,		1.0f, 1.0f, 1.0f,
//			-0.2, -0.05f, 		1.0f, 1.0f, 1.0f,
//			-0.4, 0.05f,		1.0f, 1.0f, 1.0f,
//			-0.4, -0.05f, 		1.0f, 1.0f, 1.0f,
//			-0.6, 0.05f,		1.0f, 1.0f, 1.0f,
//			-0.6, -0.05f, 		1.0f, 1.0f, 1.0f,
//			-0.8, 0.05f,		1.0f, 1.0f, 1.0f,
//			-0.8, -0.05f, 		1.0f, 1.0f, 1.0f,
//
//			0.05, 0.2f,			1.0f, 1.0f, 1.0f,
//			-0.05, 0.2f, 		1.0f, 1.0f, 1.0f,
//			0.05, 0.4f,			1.0f, 1.0f, 1.0f,
//			-0.05, 0.4f, 		1.0f, 1.0f, 1.0f,
//			0.05, 0.6f,			1.0f, 1.0f, 1.0f,
//			-0.05, 0.6f, 		1.0f, 1.0f, 1.0f,
//			0.05, 0.8f,			1.0f, 1.0f, 1.0f,
//			-0.05, 0.8f, 		1.0f, 1.0f, 1.0f,
//
//			0.05, -0.2f,		1.0f, 1.0f, 1.0f,
//			-0.05, -0.2f, 		1.0f, 1.0f, 1.0f,
//			0.05, -0.4f,		1.0f, 1.0f, 1.0f,
//			-0.05, -0.4f, 		1.0f, 1.0f, 1.0f,
//			0.05, -0.6f,		1.0f, 1.0f, 1.0f,
//			-0.05, -0.6f, 		1.0f, 1.0f, 1.0f,
//			0.05, -0.8f,		1.0f, 1.0f, 1.0f,
//			-0.05, -0.8f, 		1.0f, 1.0f, 1.0f,
//	};
//	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(axeVertices), axeVertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	// unbinds
//	glBindVertexArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	// model
//	mat3 model = mat3(1.0f);
//
//	mat3 scale = mat3(1.0f);
//	scale[0][0] = 0.5; scale[1][1] = 0.5;
//
//	mat3 rot = mat3(1.0f);
//	rot[0][0] = 0.86f;
//	rot[1][0] = -0.5f;
//	rot[0][1] = 0.5f;
//	rot[1][1] = 0.86f;
//
//	mat3 trans = mat3(1.0f);
//	trans[2][0] = 0.8f;
//	trans[2][1] = 0.0f;
//
//	model = scale * trans;
//	displayMatrix3(scale, "scale");
//	displayMatrix3(trans, "trans");
//	displayMatrix3(model, "result");
//
//	mat3 model2 = mat3(1.0f);
//	model2 = trans * scale ; // voulu
//
//	// Rendering
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window);
//		glClearColor(BACKGROUND_COLOR.x, BACKGROUND_COLOR.y, BACKGROUND_COLOR.z,
//				1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// axes
//		shaderTriangles.use();
//		shaderTriangles.setMat3("model", mat3(1.0f));
//		glBindVertexArray(VAOs[1]);
//		glDrawArrays(GL_LINES, 0, AXES_NB_VERTICES);
//
//		// triangles
//		shaderTriangles.setMat3("model", model2);
//		glBindVertexArray(VAOs[0]);
//		glDrawArrays(GL_TRIANGLES, 0, NB_VERTICES);
//
//		shaderTriangles.setMat3("model", mat3(1.0f));
//		glDrawArrays(GL_TRIANGLES, 0, NB_VERTICES);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// deallocate resources
//	glDeleteVertexArrays(2, VAOs);
//	glDeleteBuffers(2, VBOs);
//
//	glfwTerminate();
//	return 0;
//
//}
//
//void displayMatrix3(mat3 matrix, string name) {
//	cout << name << endl;
//	for (unsigned int i = 0; i < 3; i++) {
//		for (unsigned int j = 0; j < 3; j++) {
//			cout << matrix[j][i] << "     ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//
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
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL",
//	NULL, NULL);
//	if (window == NULL) {
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
//
//	// glad : load all OpenGL function pointers
//	// -------------------------------------------------------------
//	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
//		cout << "Failed to initialize GLAD" << endl;
//		return NULL;
//	}
//
//	return window;
//}
//
//void processInput(GLFWwindow* window) {
//	// Quit
//	// -----------------------------------------------------------
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//}
