/*
 * Camera.cpp
 *
 *  Created on: Nov 24, 2019
 *      Author: sophie
 */

#include <iostream>
#include "Camera.h"

// Constructors
// ---------------------------------------------------------

/**
 * Constructor
 * the initial position is (0, 0 , 3),
 */
Camera::Camera() :
		Camera(vec3(0.0f, 0.0f, 3.0f)) {
}

Camera::Camera(vec3 initialPosition) :
		Camera(initialPosition, 2.5f) {
}

Camera::Camera(vec3 initialPosition, float speed_) :
		speed(speed_) {
	// position and direction
	target = vec3(0.0f, 0.0f, 0.0f);
	position = initialPosition;
	direction = normalize(position - target);
	radius = initialPosition.z;

	// yaw - pitch
	yaw = 0.0f;
	pitch = 0.0f;
	zoom = INITIAL_ZOOM;

	// axis in the camera space
	vec3 upInWorld = vec3(0.0f, 1.0f, 0.0f);
	right = normalize(cross(upInWorld, direction));
	up = normalize(cross(direction, right));

	// moving settings
//	mode = LINEAR;
	toFront = true;
	toLeft = true;
}

///**
// * Update : The camera evolute over time
// */
//void Camera::update(double time) {
//	switch(mode) {
//		case ROTATE : {
//			target = vec3(0.0f, 0.0f, 0.0f);
//			float x = sin(time) * radius;
//			float z = cos(time) * radius;
//			setPosition(vec3(x, 0.0f, z), true);
//		}
//			break;
//		default :
//			break;
//	}
//}

// ==========================================================

// ----------------------------------------------------------
// Getters
// ----------------------------------------------------------

/**
 * computes the view matrice
 */
mat4 Camera::getViewMat() const {
	//return lookAt(position, position - direction, up);
	return lookAt(position, target, up);
}

float Camera::getFov() const {
	return zoom;
}

vec3 Camera::getPos() const {
	return position;
}

vec3 Camera::getDirection() const {
	return -direction;
}

//Mode Camera::getMode() const {
//	return mode;
//}

// ==========================================================

// ----------------------------------------------------------
// Setters
// ----------------------------------------------------------

// Moving
// ----------------------------------------------------------

//// --- Switch Mode
//void Camera::switchMode() {
//	if (mode == ROTATE)
//		mode = LINEAR;
//	else
//		mode = ROTATE;
//}
//
//// --- Rotate
//void Camera::rotate() {
//	mode = ROTATE;
//}
//void Camera::rotate(float radius) {
//	this->radius = radius;
//	rotate();
//}
//void Camera::rotate(float radius, float speed) {
//	this->speed = speed;
//	rotate(radius);
//}

// --- Linear Mode
void Camera::toTheLeft(float deltaTime) {
	setPosition(position - speed * deltaTime * right, false);
}

void Camera::toTheRight(float deltaTime) {
	setPosition(position + speed * deltaTime * right, false);
}

void Camera::forward(float deltaTime) {
	setPosition(position - speed * deltaTime * direction, false);
}

void Camera::backward(float deltaTime) {
	setPosition(position + speed * deltaTime * direction, false);
}

// --- frustrum
void Camera::updateYawAndPitch(float yawOffset, float pitchOffset) {
	yaw += yawOffset;
	pitch += pitchOffset;

	if (pitch > MAX_PITCH)
		pitch = MAX_PITCH;
	if (pitch < -MAX_PITCH)
		pitch = -MAX_PITCH;

	vec3 front = vec3(0.0f, 0.0f, 0.0f);
	front.x = cos(radians(pitch)) * sin(radians(yaw));
	front.y = sin(radians(pitch));
	front.z = cos(radians(pitch)) * cos(radians(yaw));

	direction = normalize(front);

	adaptNewSpace(false);
}

void Camera::updateFov(float fovOffset) {
	if (zoom >= MIN_ZOOM && zoom <= MAX_ZOOM) {
		zoom -= fovOffset;
	}
	if (zoom < MIN_ZOOM)
		zoom = MIN_ZOOM;
	if (zoom > MAX_ZOOM)
		zoom = MAX_ZOOM;
}

// ==============================================================

// ----------------------------------------------------------
// Private functions
// ----------------------------------------------------------

// Space
// ----------------------------------------------------------
void Camera::setPosition(vec3 newPosition, bool targetIsFixed) {
	position = newPosition;

	adaptNewSpace(targetIsFixed);
}

void Camera::setUpVector(vec3 newUpVector) {
	up = normalize(newUpVector);
	adaptNewSpace(true);
}

void Camera::adaptNewSpace(bool targetIsFixed = false) {
	if (targetIsFixed) {
		direction = normalize(position - target);
	} else {
		target = position - direction;
	}
	vec3 upInWorld = vec3(0.0f, 1.0f, 0.0f);
	right = normalize(cross(upInWorld, direction));
	up = normalize(cross(direction, right));
}

