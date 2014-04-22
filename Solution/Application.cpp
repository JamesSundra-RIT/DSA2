/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2014
--------------------------------------------------------------------------------------------------*/

#include "Application.h" //Include our application library
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//this line hides the command window

Camera* camera = nullptr;
Circle* disk = nullptr;
Cube* cube = nullptr;


void Init( void )
{
	glm::vec3 vOrigin(0.0f, 0.0f, 0.0f);

	camera = new Camera(0, 0, 10.0f);

	disk = new Circle(vOrigin, 1.0f);
	cube = new Cube(vOrigin, 1.0f);
	
	glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
}

void Display( void )
{
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 projectionMatrix = glm::perspective(45.0f, 1.0f*1/1, 0.1f, 100.0f);
	glm::mat4 viewMatrix = glm::lookAt(camera->GetPosition(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	disk->Render(&projectionMatrix, &viewMatrix);
	//cube->Render(&projectionMatrix, &viewMatrix);

	glutSwapBuffers();
	glutPostRedisplay();
}

void Idle(void)
{
	
}

void OnSpecialKeyDown(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT:
			camera->Rotate(1, 0, 0);
			break;
		case GLUT_KEY_RIGHT:
			camera->Rotate(-1, 0, 0);
			break;
		case GLUT_KEY_UP:
			camera->Rotate(0, 1, 0);
			break;
		case GLUT_KEY_DOWN:
			camera->Rotate(0, -1, 0);
			break;
	}
}

void OnKeyDown(unsigned char key, int x, int y){
	switch(key){
		case 'a':
			camera->Rotate(1, 0, 0);
			break;
		case 'd':
			camera->Rotate(-1, 0, 0);
			break;
		case 'w':
			camera->Rotate(0, 1, 0);
			break;
		case 's':
			camera->Rotate(0, -1, 0);
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
    
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutSpecialFunc(OnSpecialKeyDown);
	glutKeyboardFunc(OnKeyDown);
	//glutSpecialUpFunc( OnSpecialUp );
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutMainLoop();
	if(disk){
		delete disk;
		disk = nullptr;
	}
	if(cube){
		delete cube;
		cube = nullptr;
	}

    return 0;
}
