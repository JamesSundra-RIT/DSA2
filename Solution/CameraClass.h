/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _CAMERA_H
#define _CAMERA_H

#include "SystemClass.h"

class CameraClass
{
public:
	static CameraClass* GetInstance(); // Singleton Accessor
	~CameraClass(void); //Destructor

	//Translate
	void SetPosition(glm::vec3 a_Position);
	void MoveSideways(float a_fDistance = 0.1f);
	void MoveVertical(float a_fDistance = 0.1f);
	void MoveForward(float a_fDistance = 0.1f);

	//Projection
	void SetProjection();
	void SetProjection(glm::mat4 a_mProjection);
	__declspec(property(put = SetProjection)) glm::mat4 Projection;
	glm::mat4 GetProjection();
	//View
	void SetView();
	void SetView(glm::mat4 a_mView);
	__declspec(property(put = SetView)) glm::mat4 View;
	glm::mat4 GetView();
	//MVP
	glm::mat4 CalculateProjection(glm::mat4 a_mModel = glm::mat4(1.0f));
	glm::mat4 GetMVP();
	__declspec(property(get = GetMVP)) glm::mat4 VMP;

	//Accessors to helpful variables
	glm::vec3 GetPosition();
	void Rotate(glm::vec3 rotation);
	void Rotate(glm::vec3 axis, float amount);
	void Rotate(float yaw, float pitch, float roll);
	
	glm::vec3 GetLightPosition();
	void RotateLight(glm::vec3 rotation);
	void RotateLight(glm::vec3 axis, float amount);
	void RotateLight(float yaw, float pitch, float roll);

private:
	CameraClass(void); // Constructor
	CameraClass(CameraClass const& other); //Copy Constructor
	CameraClass& operator=(CameraClass const& other); // Copy Assignment Operator

	void Release(void);// Releases the memory
	void Init(void); //Init the values

	static CameraClass* m_pInstance;//Singleton

	SystemClass* m_pSystem;

	//Projection
	glm::mat4 m_mProjection;
	//View
	glm::mat4 m_mView;
	//MVP
	glm::mat4 m_mMVP;

	//Helpful variables;
	glm::vec3 position;
	float yaw;
	float pitch;
	float roll;
	
	float lightYaw;
	float lightPitch;
	float lightRoll;
};


#endif //_CAMERA_H