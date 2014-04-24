/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "GL\freeglut_ext.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\quaternion.hpp"
#include "glm\gtx\quaternion.hpp"
#include "glm\gtx\euler_angles.hpp"
#include "glm\gtx\norm.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "FolderClass.h"
//#include "MaterialManagerClass.h"

typedef glm::vec2 vector2;
typedef glm::vec3 vector3;
typedef glm::vec4 vector4;
typedef std::string String;
typedef glm::mat4 matrix4;

enum Results
{
	ERROR_FREE,
	ERROR_FILE_MISSING,
	ERROR_CONTEXT,
	ERROR_MEMORY,
	ERROR_GENERAL,
	ERROR_NAME,
	ERROR_NOT_INITIALIZED,
	ERROR_FILE,
	DONE,
	RUNNING
};


//namespace BTO
//{
class SystemClass
{
public:
	FolderClass* m_pFolder;
	//MaterialManagerClass* m_pMaterialManager; //Material Manager
private:
	SystemClass(void); // Constructor
	SystemClass(SystemClass const& other); //Copy Constructor
	SystemClass& operator=(SystemClass const& other); // Copy Assignment Operator

	void Release(void); // Release Memory
	void Init(void); // Initialize variables
	
	static SystemClass* m_pInstance; // Singleton

	int m_nWindowWidth; // Window width
	int m_nWindowHeight; // Window height
	int m_nWindowX; // Window Position X
	int m_nWindowY; // Window Position Y
	String m_sWindowName; // Window Name

	DWORD m_dStartingTime; //Start time of the program
	DWORD m_dLastFPS; //Last time the time was called
	int m_nFPS; //Frames per Second
	int m_nFrames; //Frames Passed
	
	DWORD m_dTimerStart; //Start time of the program
	float m_fSeconds; //Second Passed
	float m_fDeltaTime; //Time Difference
	
	void (*m_pDisplay) (void); //Display Functor
	void (*m_pReshape) (int nWidth, int nHeight); // Reshape Functor
	void (*m_pIdle) (void); // Idle Functor
	void (*m_pKeyboard) (unsigned char key, int x, int y); // Keyboard Functor
	void (*m_pKeyboardUp) (unsigned char key, int x, int y); // KeyboardUp Functor
	void (*m_pOnSpecial) (int key, int x, int y); // OnSpecial Functor
	void (*m_pOnSpecialUp) (int key, int x, int y); // OnSpecialUp Functor
	void (*m_pMouse) (int button, int state, int x, int y); //Mouse Functor
	void (*m_pMouseWheel) (int wheel, int direction, int x, int y); //Mouse Wheel Functor

public:
	static SystemClass* GetInstance(); // Singleton Accessor
	~SystemClass(void); // Destructor

	// Window Width Property
	__declspec(property(get = GetWindowWidth, put = SetWindowWidth)) int WindowWidth;
	void SetWindowWidth(int nWidth);
	int GetWindowWidth(void);

	// Window Height Property
	__declspec(property(get = GetWindowHeight, put = SetWindowHeight)) int WindowHeight;
	void SetWindowHeight(int nHeight);
	int GetWindowHeight(void);

	// WindowX Property
	__declspec(property(get = GetWindowX, put = SetWindowX)) int WindowX;
	void SetWindowX(int nX);
	int GetWindowX(void);

	// WindowY Property
	__declspec(property(get = GetWindowY, put = SetWindowY)) int WindowY;
	void SetWindowY(int nY);
	int GetWindowY(void);
	
	// Window Name Property
	__declspec(property(get = GetWindowName, put = SetWindowName)) String WindowName;
	void SetWindowName(String sWindowName);
	String GetWindowName(void);

	// Display functor Property
	void SetDisplayFunctor(void (*Functor) (void));
	__declspec(property(put = SetDisplayFunctor)) void (*Display) (void);
	
	// Reshape functor Property
	void SetReshapeFunctor(void (*Functor) (int, int));
	__declspec(property(put = SetReshapeFunctor)) void (*Reshape) (int, int);
	
	// Idle functor Property
	void SetIdleFunctor(void (*Functor) (void));
	__declspec(property(put = SetIdleFunctor)) void (*Idle) (void);
	
	// OnTime functor Property
	void SetOnTimeFunctor(void (*Functor) (int));
	__declspec(property(put = SetOnTimeFunctor)) void (*OnTime) (int);
	
	// Keyboard functor Property
	void SetKeyboardFunctor(void (*Functor)(unsigned char, int, int));
	__declspec(property(put = SetKeyboardFunctor)) void (*Keyboard) (unsigned char, int, int);
	
	// KeyboardUp functor Property
	void SetKeyboardUpFunctor(void (*Functor)(unsigned char, int, int));
	__declspec(property(put = SetKeyboardUpFunctor)) void (*KeyboardUp) (unsigned char, int, int);
	
	// OnSpecialFunctor Property
	void SetOnSpecialFunctor(void (*Functor)(int, int, int));
	__declspec(property(put = SetOnSpecialFunctor)) void (*OnSpecial) (int, int, int);
	
	// OnSpecialUpFunctor Property
	void SetOnSpecialUpFunctor(void (*Functor)(int, int, int));
	__declspec(property(put = SetOnSpecialUpFunctor)) void (*OnSpecialUp) (int, int, int);
	
	// MouseFunctor Property
	void SetMouseFunctor(void (*Functor)(int, int, int, int));
	__declspec(property(put = SetMouseFunctor)) void (*Mouse) (int, int, int, int);
	
	// MouseWheelFunctor Property
	void SetMouseWheelFunctor(void (*Functor)(int, int, int, int));
	__declspec(property(put = SetMouseWheelFunctor)) void (*MouseWheel) (int, int, int, int);
	
	bool InitRenderingContext(int* argc, char **argv); // Creates the OpenGL "hooks"
	bool InitCallbacks(void); // Indicates OpenGL what functors are going to be used as callbacks
	void StartRenderLoop(void); // Iniciates the renderLoop

	void UpdateTime(void);//Updates the current time
	void StartClock(void);//Starts a time count
	float StopClock(void);//Stops the time count and returns the number of seconds passed
	float LapClock(void);//Checks the time difference between startclock and current call
};
//}
//using namespace BTO;


#endif //_SYSTEM_H