/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2014
--------------------------------------------------------------------------------------------------*/

#include "Application.h" //Include our application library
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//this line hides the command window

#define PI 3.14159265

//Most likely going to move these into a camera class later		- James
int cameraYaw = 0;
int cameraPitch = 0;
float cameraZoom = .2f;

Circle* disk = nullptr;


void Init( void )
{
	glm::vec3 vOrigin(0.0f, 0.0f, 0.0f);

	disk = new Circle(vOrigin, 0.5f);
	
	glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
}

void Display( void )
{
	glClear(GL_COLOR_BUFFER_BIT);

	glm::vec3 cameraPos = glm::vec3(cos(cameraPitch * PI/180) * sin(cameraYaw * PI/180) * cameraZoom,
									sin(cameraPitch * PI/180) * cameraZoom,
									cos(cameraPitch * PI/180) * cos(cameraYaw * PI/180) * cameraZoom);
	glm::mat4 projectionMatrix = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 viewMatrix = glm::translate(0.0f, 0.0f, 0.0f);

	disk->Render(&projectionMatrix, &viewMatrix);

	glutSwapBuffers();
	glutPostRedisplay();
}

void Idle(void)
{
	
}

//Most likely going to abstract this into a camera class later	- James
void MoveCamera(int yaw, int pitch){
	cameraYaw = (cameraYaw + yaw) % 360;
	cameraPitch = (cameraPitch + pitch) % 360;
}

void OnSpecialKeyDown(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT:
			MoveCamera(1, 0);
			break;
		case GLUT_KEY_RIGHT:
			MoveCamera(-1, 0);
			break;
		case GLUT_KEY_UP:
			MoveCamera(0, 1);
			break;
		case GLUT_KEY_DOWN:
			MoveCamera(0, -1);
			break;
	}
}

void OnKeyDown(unsigned char key, int x, int y){
	switch(key){
		case 'a':
			MoveCamera(1, 0);
			break;
		case 'd':
			MoveCamera(-1, 0);
			break;
		case 'w':
			MoveCamera(0, 1);
			break;
		case 's':
			MoveCamera(0, -1);
			break;
	}
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
	glutSpecialFunc(OnSpecialKeyDown);
	glutKeyboardFunc(OnKeyDown);
	//glutSpecialUpFunc( OnSpecialUp );
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutMainLoop();
	if(disk)
	{
		delete disk;
		disk = nullptr;
	}
    return 0;
}
