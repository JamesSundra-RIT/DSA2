/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2014
--------------------------------------------------------------------------------------------------*/

#include "Application.h" //Include our application library
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//this line hides the command window

Circle* g_Circle = nullptr;

void Init( void )
{
	glm::vec3 vOrigin(0.0f, 0.0f, 0.0f);

	g_Circle = new Circle(vOrigin, 1.0f);
	
	glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
}

void Display( void )
{
	glClear(GL_COLOR_BUFFER_BIT);

	g_Circle->Render();

	glutSwapBuffers();
	glutPostRedisplay();
}
void Idle(void)
{
}
void OnSpecialUp( int key, int x, int y)
{
	/*switch (key)
	{
		case GLUT_KEY_UP:
			g_Circle->AddForce(glm::vec2(0.0f, 1.5f));
			break;
		case GLUT_KEY_DOWN:
			g_Circle->AddForce(glm::vec2(0.0f, -1.5f));
			break;
		case GLUT_KEY_LEFT:
			g_Circle->AddForce(glm::vec2(-1.5f, 0.0f));
			break;
		case GLUT_KEY_RIGHT:
			g_Circle->AddForce(glm::vec2(1.5f, 0.0f));
			break;
	}*/
}

int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 512, 512 );

    glutCreateWindow("Diffraction!");

	glewExperimental = GL_TRUE;
    glewInit();

	Init();
    
	glutDisplayFunc( Display );
	glutIdleFunc(Idle);
	glutSpecialUpFunc( OnSpecialUp );
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutMainLoop();
	if(g_Circle)
	{
		delete g_Circle;
		g_Circle = nullptr;
	}
    return 0;
}
