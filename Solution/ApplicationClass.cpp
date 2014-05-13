#include "ApplicationClass.h"
ApplicationClass* ApplicationClass::m_pInstance = nullptr;
ApplicationClass* ApplicationClass::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new ApplicationClass();
	}
	return m_pInstance;
}
ApplicationClass::ApplicationClass(){Init();}
ApplicationClass::ApplicationClass(ApplicationClass const& other){}
ApplicationClass& ApplicationClass::operator=(ApplicationClass const& other) {	return *this; }
ApplicationClass::~ApplicationClass(){Release();};
// Redefinable Functions
void ApplicationClass::Init(void)
{
	m_pSystem = SystemClass::GetInstance();
	m_pCamera = CameraClass::GetInstance();

	//m_pCamera->SetPosition(glm::vec3( 1.0f, 1.0f, 1.0f));

	m_Frame = new FrameClass();

	m_pPolygon = new PolygonClass();
	m_pPolygon->GeneratePoligon( 3, 0.25f);
	m_pPolygon->ModelMatrix = glm::translate(m_pPolygon->GetModelMatrix(), glm::vec3(1.0f,1.0f,0.0f));

	m_pPolyhedron = new PolyhedronClass();
	m_pPolyhedron->GeneratePoints(0);

	m_pModelManager = ModelManagerClass::GetInstance();
	m_pModelManager->LoadModel("Earth.obj", "Earth");

	m_bArcBallActive = false;
	m_bGridActive = true;
	bUseQuaterions = false;

	m_pSystem->StartClock();
}
void ApplicationClass::Release(void)
{
	delete m_pModelManager;
	delete m_pPolyhedron;
	delete m_pPolygon;
	delete m_Frame;

	m_pCamera = nullptr;
	m_pSystem = nullptr;
}
void ApplicationClass::Update(void)
{
	float time = m_pSystem->LapClock();
	if(time > 1)
	{
		/*matrix4 matrix = m_pModelManager->GetModelMatrix("Earth");
		matrix = glm::translate(matrix, vector3(0.5f, 0.0f, 0.0f));
		m_pModelManager->SetModelMatrix(matrix, "Earth");*/
		m_pSystem->StartClock();
	}
}
void ApplicationClass::Display(void)
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );     // clear the window

	if(m_bGridActive)
	{
		/*m_Frame->RenderGrid(	FrameClass::MyEnum::XY | 
								FrameClass::MyEnum::XZ | 
								FrameClass::MyEnum::YZ);*/
		m_Frame->Render();
	}


	if(bUseQuaterions)
		m_pPolygon->Render();

	//m_pModelManager->RenderModel("cono");
	m_pModelManager->RenderModel();
	
	glutSwapBuffers();
	m_pSystem->UpdateTime();
}
void ApplicationClass::Idle(void)
{
	m_pSystem->UpdateTime();

	Update();

	if(m_bArcBallActive)
		ArcBall(0.1f);

	glutPostRedisplay();
}
void ApplicationClass::Reshape(int a_nWidth, int a_nHeight)
{
	m_pSystem->WindowWidth = a_nWidth;
	m_pSystem->WindowHeight = a_nHeight;
	m_pCamera->SetProjection();
}
void ApplicationClass::Keyboard(unsigned char key, int x, int y)
{
	static float fAngX = 0.0f;
	static float fAngY = 0.0f;
	static float fAngZ = 0.0f;

	float fSpeed = 5.0f;

	switch (key)
	{
		case 's':
			fAngX += fSpeed;
			break;
		
		case 'w':
			fAngX -= fSpeed;
			break;
		case 'q':
			fAngY += fSpeed;
			break;
		case 'e':
			fAngY -= fSpeed;
			break;
		case 'a':
			fAngZ += fSpeed;
			break;
		case 'd':
			fAngZ -= fSpeed;
			break;
		case 'r':
		case 'R':
			fAngX = 0.0f;
			fAngY = 0.0f;
			fAngZ = 0.0f;
			break;
	}
	
	if(bUseQuaterions == false)
	{
		glm::mat4 orientation;
		glm::mat4 oX;
		glm::mat4 oY;
		glm::mat4 oZ;
		oX = glm::rotate(glm::mat4(1.0f), fAngX, glm::vec3( 1.0f, 0.0f, 0.0f));
		oY = glm::rotate(glm::mat4(1.0f), fAngY, glm::vec3( 0.0f, 1.0f, 0.0f));
		oZ = glm::rotate(glm::mat4(1.0f), fAngZ, glm::vec3( 0.0f, 0.0f, 1.0f));
		orientation = oX * oZ * oY;
		
		matrix4 matrix = m_pModelManager->GetModelMatrix("Earth");
		matrix = orientation;
		m_pModelManager->SetModelMatrix(matrix, "Earth");
	}
	else
	{
		glm::quat orientation = glm::quat(glm::vec3( glm::radians(fAngX), glm::radians(fAngY), glm::radians(fAngZ)));
		m_pPolyhedron->ModelMatrix = glm::mat4_cast(orientation);
	}
}
void ApplicationClass::KeyboardUp(unsigned char key, int x, int y)
{
	switch ( key ) {
    case 033:
	case 13:
        exit( EXIT_SUCCESS );
		break;
	case 'G':
	case 'g':
		m_bGridActive = !m_bGridActive;
		break;
	case 'Q':
	case 'q':
		bUseQuaterions = !bUseQuaterions;
		break;
    }
}
void ApplicationClass::OnSpecial(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP:
			if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
				m_pCamera->MoveForward(-1.1f);
			m_pCamera->MoveForward(-0.1f);
			break;
		case GLUT_KEY_DOWN:
			if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
				m_pCamera->MoveForward( 1.1f);
			m_pCamera->MoveForward( 0.1f);
			break;
		case GLUT_KEY_LEFT:
			if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
				m_pCamera->MoveSideways(-1.1f);
			m_pCamera->MoveSideways(-0.1f);
			break;
		case GLUT_KEY_RIGHT:
			if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
				m_pCamera->MoveSideways( 1.1f);
			m_pCamera->MoveSideways( 0.1f);
			break;
		case GLUT_KEY_PAGE_UP:
			if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
				m_pCamera->MoveVertical(1.1f);
			m_pCamera->MoveVertical(0.1f);
			break;
		case GLUT_KEY_PAGE_DOWN:
			if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
				m_pCamera->MoveVertical(-1.1f);
			m_pCamera->MoveVertical(-0.1f);
			break;
	}
}
void ApplicationClass::OnSpecialUp(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP:
			break;
		case GLUT_KEY_DOWN:
			break;
		case GLUT_KEY_LEFT:
			break;
		case GLUT_KEY_RIGHT:
			break;
		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;
	}
}
void ApplicationClass::Mouse(int button, int state, int x, int y)
{
	switch(button)
	{
	case GLUT_LEFT_BUTTON :
		switch(state)
		{
		case GLUT_UP:
			m_bArcBallActive = false;
			break;
		case GLUT_DOWN:
			m_bArcBallActive = true;
			break;
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		switch(state)
		{
		case GLUT_UP:
			break;
		case GLUT_DOWN:
			break;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		switch(state)
		{
		case GLUT_UP:
			break;
		case GLUT_DOWN:
			break;
		}
		break;
	}
}
void ApplicationClass::MouseWheel(int wheel, int direction, int x, int y)
{

}
void ApplicationClass::ArcBall(float a_fSensitivity)
{
	static glm::mat4 arcball = glm::mat4(1.0);
	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	CenterX = m_pSystem->WindowX + m_pSystem->WindowWidth / 2;
	CenterY = m_pSystem->WindowY + m_pSystem->WindowHeight / 2;
	
	float DeltaMouse;
	POINT pt;

	GetCursorPos(&pt);
	
	MouseX = pt.x;
	MouseY = pt.y;

	SetCursorPos(CenterX, CenterY);

	if(MouseX < CenterX)
	{
		DeltaMouse = static_cast<float>(CenterX - MouseX);
		arcball = glm::rotate(arcball, a_fSensitivity * DeltaMouse, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else if(MouseX > CenterX)
	{
		DeltaMouse = static_cast<float>(MouseX - CenterX);
		arcball = glm::rotate(arcball, -a_fSensitivity * DeltaMouse, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	if(MouseY < CenterY)
	{
		DeltaMouse = static_cast<float>(CenterY - MouseY);
		arcball = glm::rotate(arcball, a_fSensitivity * DeltaMouse, glm::vec3(1.0f, 0.0f, 0.0f));
	}
	else if(MouseY > CenterY)
	{
		DeltaMouse = static_cast<float>(MouseY - CenterY);
		arcball = glm::rotate(arcball, -a_fSensitivity * DeltaMouse, glm::vec3(1.0f, 0.0f, 0.0f));
	}
	m_pModelManager->SetModelMatrix(arcball);
}