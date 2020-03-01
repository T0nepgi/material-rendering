/*
 * Shader.h
 *
 *  Created on: Nov 19, 2019
 *      Author: Sophie
 */

#ifndef SHADER_H_
#define SHADER_H_

// GLAD
#include <glad/glad.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
using namespace glm;

const string VERTEX_SHADERS_PATH = "include/Shaders/";
const string FRAGMENT_SHADERS_PATH = "include/Shaders/";

class Shader
{
public:
	// constructor reads and builds the shader
	Shader(string vertexFile, string fragmentFile);

	// getters
	unsigned int getID();

	// activate the shader
	void use();

	// utility uniform functions
	void setBool(const string &name, bool value) const;
	void setInt (const string &name, int value) const;
	void setFloat (const string &name, float value) const;
	void setMat4(const string &name, mat4 matrix) const;
	void setMat3(const string &name, mat3 matrix) const;
	void setMat2(const string &name, mat2 matrix) const;
	void setVec3(const string &name, vec3 vector) const;

private :
	// the program ID
	unsigned int ID;

};

#endif /* SHADER_H_ */
