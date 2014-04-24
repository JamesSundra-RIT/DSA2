#include "SystemClass.h"
//  SystemClass
SystemClass* SystemClass::m_pInstance = nullptr;
SystemClass* SystemClass::GetInstance(void)
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new SystemClass();
	}
	return m_pInstance;
}
SystemClass::SystemClass(void){Init();}
SystemClass::SystemClass(SystemClass const& other){}
SystemClass& SystemClass::operator=(SystemClass const& other) {	return *this; }
SystemClass::~SystemClass(void){Release();};

//--- Non Standard Singleton Methods
void  SystemClass::Release(void)
{
	Init();
	delete m_pFolder;
	//delete m_pMaterialManager;
}

void SystemClass::Init(void)
{
	m_pFolder = FolderClass::GetInstance();
	//m_pMaterialManager = MaterialManagerClass::GetInstance();

	std::cout << m_pFolder->Root << std::endl;

	m_nWindowX = 0;
	m_nWindowY = 0;

	m_nWindowHeight = 512;
	m_nWindowWidth = 512;
	m_sWindowName = "Window";

	m_pDisplay = nullptr;
	m_pReshape = nullptr;
	m_pIdle = nullptr;
	
	m_pKeyboard = nullptr;
	m_pKeyboardUp = nullptr;
	
	m_pOnSpecial = nullptr;
	m_pOnSpecialUp = nullptr;

	m_pMouse = nullptr;

	m_dStartingTime = GetTickCount();
	m_dLastFPS = GetTickCount();
	m_nFrames = 0;
	m_nFPS = 0;

	m_dTimerStart = m_dStartingTime;

	m_fSeconds = 0.0f;
	m_fDeltaTime = 0.0f;
}

void SystemClass::SetWindowX(int nX)
{
	m_nWindowX = nX;
}

int SystemClass::GetWindowX(void)
{
	return m_nWindowX;
}

void SystemClass::SetWindowY(int nY)
{
	m_nWindowY = nY;
}

int SystemClass::GetWindowY(void)
{
	return m_nWindowY;
}

void SystemClass::SetWindowWidth(int nWidth)
{
	m_nWindowWidth = nWidth;
}

int SystemClass::GetWindowWidth(void)
{
	return m_nWindowWidth;
}

void SystemClass::SetWindowHeight(int nHeight)
{
	m_nWindowHeight = nHeight;
}

int SystemClass::GetWindowHeight(void)
{
	return m_nWindowHeight;
}
	
void SystemClass::SetWindowName(String sWindowName)
{
	m_sWindowName = sWindowName;
}

String SystemClass::GetWindowName(void)
{
	return m_sWindowName;
}

void SystemClass::SetDisplayFunctor(void (*Functor) (void))
{
	m_pDisplay = Functor;
}
void SystemClass::SetReshapeFunctor(void (*Functor) (int, int))
{
	m_pReshape = Functor;
}
void SystemClass::SetIdleFunctor(void (*Functor) (void))
{
	m_pIdle = Functor;
}
void SystemClass::SetKeyboardFunctor(void (*Functor)(unsigned char, int, int))
{
	m_pKeyboard = Functor;
}
void SystemClass::SetKeyboardUpFunctor(void (*Functor)(unsigned char, int, int))
{
	m_pKeyboardUp = Functor;
}
void SystemClass::SetOnSpecialFunctor(void (*Functor)(int, int, int))
{
	m_pOnSpecial = Functor;
}
void SystemClass::SetOnSpecialUpFunctor(void (*Functor)(int, int, int))
{
	m_pOnSpecialUp = Functor;
}

void SystemClass::SetMouseFunctor(void (*Functor)(int, int, int, int))
{
	m_pMouse = Functor;
}

void SystemClass::SetMouseWheelFunctor(void (*Functor)(int, int, int, int))
{
	m_pMouseWheel = Functor;
}

void SystemClass::StartClock(void)
{
	m_dTimerStart = GetTickCount();
}

float SystemClass::StopClock(void)
{
	DWORD time = GetTickCount() - m_dTimerStart;
	m_dTimerStart = GetTickCount();
	return static_cast<float>(time/1000);
}
float SystemClass::LapClock(void)
{
	DWORD time = GetTickCount() - m_dTimerStart;
	return static_cast<float>(time/1000);
}
void SystemClass::UpdateTime(void)
{
	// Get FPS
	if( (GetTickCount() - m_dLastFPS) >= 1000 )	// When a Second has passed...
	{
		m_dLastFPS = GetTickCount();			// Refresh the value of frames
		m_nFPS = m_nFrames;						// save the number of frames that occured in this second
		m_nFrames = 0;							// Reset the frames
		return;
	}
	m_nFrames++;								// Increment the frame cont
	return;
}

bool SystemClass::InitRenderingContext(int* argc, char **argv)
{
	glutInit( argc, argv);
	glutInitDisplayMode( GLUT_RGBA );

	glutInitWindowSize( m_nWindowWidth, m_nWindowHeight );
	m_nWindowX = (GetSystemMetrics(SM_CXSCREEN) - m_nWindowWidth)  / 2;
	m_nWindowY = (GetSystemMetrics(SM_CYSCREEN) - m_nWindowHeight)  / 2;
	glutInitWindowPosition( m_nWindowX, m_nWindowY);

    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

	glutCreateWindow( m_sWindowName.c_str() );

    glewExperimental = GL_TRUE;
    glewInit();

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if its closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION); // Lets us execute after main loop. Handy!
	glClearColor( 0.0, 0.0, 0.0, 1.0 ); // white background

	return true;
}

bool SystemClass::InitCallbacks(void)
{
	if(m_pDisplay != nullptr)
		glutDisplayFunc(m_pDisplay);
	
	if(m_pReshape != nullptr)
		glutReshapeFunc(m_pReshape);

	if(m_pIdle != nullptr)
		glutIdleFunc( m_pIdle );

	if(m_pKeyboard != nullptr)
		glutKeyboardFunc( m_pKeyboard );
	
	if(m_pKeyboardUp != m_pKeyboard)
		glutKeyboardUpFunc( m_pKeyboardUp );
		
	if(m_pOnSpecial != nullptr)
		glutSpecialFunc(m_pOnSpecial);

	if(m_pOnSpecialUp != nullptr)
		glutSpecialUpFunc(m_pOnSpecialUp);

	if(m_pMouse != nullptr)
		glutMouseFunc(m_pMouse);

	if(m_pMouseWheel != nullptr)
		glutMouseWheelFunc(m_pMouseWheel);

	return true;
}

void SystemClass::StartRenderLoop(void)
{
	if(m_pDisplay != nullptr)
		glutMainLoop();
}