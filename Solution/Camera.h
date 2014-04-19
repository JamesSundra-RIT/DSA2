#ifndef __CAMERA__
#define __CAMERA__

#include "System.h"

#define PI 3.14159265

class Camera{
	private:
		float yaw;
		float pitch;
		float zoom;

	public:
		Camera(float yaw, float pitch, float zoom);
		Camera(const Camera& otherCamera);
		Camera& Camera::operator=(const Camera& otherCamera);

		void Rotate(glm::vec3 rotation);
		void Rotate(glm::vec3 axis, float amount);
		void Rotate(float yaw, float pitch, float roll);

		glm::vec3 GetPosition();
};

#endif //__CAMERA__