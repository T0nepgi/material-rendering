/*
 * A class to modelise a camera in the world
 *
 *  Created on: Nov 24, 2019
 *      Author: sophie
 */

#ifndef CAMERA_H_
#define CAMERA_H_

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

//enum Mode {ROTATE, LINEAR};

// --- Constants
// pitch
const float MAX_PITCH = 89.0f;
const float MIN_PITCH = 0.0f;

// frustrum
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 100.0f;

// zoom
const float INITIAL_ZOOM = 45.0f;
const float	MIN_ZOOM = 1.0f;
const float MAX_ZOOM = 60.0f;

// --- Class
class Camera {

public:

	/**
	 * Constructor
	 * the initial position is (0, 0 , 3), pointing toward the origin
	 */
	Camera();
	Camera(vec3 initialPosition);
	Camera(vec3 initialPosition, float speed);

//	/**
//	 * Update : the camera evolute over time (move or not)
//	 */
//	void update(double time);

	// Getters
	// -----------------------------------------------------

	/**
	 * computes the view matrice from the current space settings
	 */
	mat4 getViewMat() const;

	// zoom
	float getFov() const;

	vec3 getPos() const;

	vec3 getDirection() const;

	// Setters
	// -----------------------------------------------------

//	//--- Moving mode
//	// Switch Mode
//	void switchMode();
//
//	// Rotate
//	void rotate();
//	void rotate(float radius);
//	void rotate(float radius, float speed);

	// linear moving
	void toTheLeft(float deltaTime);
	void toTheRight(float deltaTime);
	void forward(float deltaTime);
	void backward(float deltaTime);

	// frustrum
	void updateYawAndPitch(float yawOffset, float pitchOffset);
	void updateFov(float fovOffset);

private :

	// Attributes
	// -------------------------------------------------------

	// Camera space settings
	vec3 position;
	vec3 target;
	vec3 direction; //z
	vec3 right; 	//x
	vec3 up; 		//y

	// frustrum
	float pitch;
	float yaw;
	float zoom;

	// rotate setting
	float radius;

	// Moving
	float speed;
//	Mode mode;
	bool toLeft;
	bool toFront;


	// Functions
	// -------------------------------------------------------

	// --- Space
	void setPosition(vec3 position, bool targetIsFixed);
	void setUpVector(vec3 newUpVector);

	// adapt new space settings
	void adaptNewSpace(bool targetIsFixed);

};

#endif /* CAMERA_H_ */
