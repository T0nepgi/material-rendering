/*
 * Mesh.h
 *
 *  Created on: Dec 4, 2019
 *      Author: sophie
 */

#ifndef MESH_H_
#define MESH_H_

// Shader
#include "Shader.h"

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//utils
#include <string>
#include <vector>

using namespace glm;
using namespace std;

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	string type;
};

class Mesh {
public:

	// Attributes
	// ==========================================================

	// Mesh Data
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	// Functions
	// ==========================================================

	/*
	 * Constructor
	 */
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	/*
	 * Draw
	 */
	void Draw(Shader shader);

private:

	// Attributes
	// ==========================================================
	unsigned int VAO, VBO, EBO;

	// Functions
	// ==========================================================
	void setupMesh();

};

#endif /* MESH_H_ */
