/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <iostream>
#include "SystemClass.h"
#include "PolygonClass.h"
#include "PolyhedronClass.h"
#include "ModelManagerClass.h"
#include "FrameClass.h"
#include "CameraClass.h"

class ApplicationClass
{
	static ApplicationClass* m_pInstance;
	SystemClass* m_pSystem;
	FrameClass* m_Frame;
	PolygonClass* m_pPolygon;
	PolyhedronClass* m_pPolyhedron;
	
	ModelManagerClass* m_pModelManager;

	bool m_bArcBallActive;
	bool m_bGridActive;
	bool bUseQuaterions;

public:
	CameraClass* m_pCamera;

	static ApplicationClass* GetInstance();
	~ApplicationClass();

	void Update (void);
	void Display (void);
	void Idle (void);
	void Reshape(int a_nWidth, int a_nHeight);
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void OnSpecial(int key, int x, int y);
	void OnSpecialUp(int key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void MouseWheel(int wheel, int direction, int x, int y);

private:
	ApplicationClass(void);
	ApplicationClass(ApplicationClass const& input);
	ApplicationClass& operator=(ApplicationClass const& input);
	void Release(void);
	void Init();
	void ArcBall(float a_fSensitivity = 0.5f);
};

#endif //_APPLICATION_H