#include "Camera.h"

Camera::Camera(float yaw, float pitch, float zoom){
	this->yaw = yaw;
	this->pitch = pitch;
	this->zoom = zoom;
}

Camera::Camera(const Camera& otherCamera){
	yaw = otherCamera.yaw;
	pitch = otherCamera.pitch;
	zoom = otherCamera.zoom;
}

Camera& Camera::operator=(const Camera& otherCamera){
	if(this != &otherCamera){
		yaw = otherCamera.yaw;
		pitch = otherCamera.pitch;
		zoom = otherCamera.zoom;
	}
	return *this;
}

void Camera::Rotate(glm::vec3 rotation){
	Rotate(rotation.x, rotation.y, rotation.z);
}

void Camera::Rotate(glm::vec3 axis, float amount){
	Rotate(axis.x * amount, axis.y * amount, axis.z * amount);
}

void Camera::Rotate(float yaw, float pitch, float roll){
	this->yaw = fmod(this->yaw + yaw, 360);
	this->pitch = fmod(this->pitch + pitch, 360);
}

glm::vec3 Camera::GetPosition(){
	return glm::vec3(cos(pitch * PI/180) * sin(yaw * PI/180) * zoom,
					 sin(pitch * PI/180) * zoom,
					 cos(pitch * PI/180) * cos(yaw * PI/180) * zoom);
}