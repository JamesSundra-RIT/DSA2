#include "Cube.h"

Cube::Cube(glm::vec3 anOrigin, GLfloat aSize)
{
	origin = glm::vec3(anOrigin);
	size = aSize;
	GeneratePoints();
	Init();
}

Cube::Cube(const Cube& otherCube)
{
	origin = otherCube.origin;
	size = otherCube.size;
	GeneratePoints();
	Init();
}

Cube& Cube::operator=(const Cube& otherCube)
{
	if(this != &otherCube)
	{
		origin = otherCube.origin;
		size = otherCube.size;
		GeneratePoints();
		Init();
	}

	return *this;
}

void Cube::Init()
{
	// Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

	// Create and initialize a buffer object for each Cube.
	GLuint aBuffer;
    glGenBuffers( 1, &aBuffer );
	myBuffer = aBuffer;
    glBindBuffer( GL_ARRAY_BUFFER, myBuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

	// Load shaders and use the resulting shader program
	GLuint program = CompileShader( "Shaders\\vshader.glsl", "Shaders\\fshader.glsl" );
	myShaderProgram = program;
    glUseProgram( myShaderProgram );

	// Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( myShaderProgram, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
}

void Cube::Render(glm::mat4x4* projectionMatrix, glm::mat4x4* viewMatrix)
{
	// Use the buffer and shader for each Cube.
	glUseProgram( myShaderProgram );
	glBindBuffer( GL_ARRAY_BUFFER, myBuffer );

	// Initialize the vertex position attribute from the vertex shader.
    GLuint loc = glGetAttribLocation( myShaderProgram, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	GLint worldLoc = glGetUniformLocation(myShaderProgram, "world");
	glm::mat4 mat4Translate = glm::translate(origin.x, origin.y, origin.z);
	glm::mat4 mat4Scale = glm::scale(size, size, 1.0f);
	glm::mat4 mat4Composed = mat4Translate * mat4Scale;
	glProgramUniformMatrix4fv(myShaderProgram, worldLoc, 1, true,  glm::value_ptr(mat4Composed) );

	// Get the location of a uniform shader variable named 'projection'.
	GLint viewLoc = glGetUniformLocation(myShaderProgram, "view");
	glProgramUniformMatrix4fv(myShaderProgram, viewLoc, 1, false, glm::value_ptr(*viewMatrix));

	// Get the location of a uniform shader variable named 'projection'.
	GLint projectionLoc = glGetUniformLocation(myShaderProgram, "projection");
	glProgramUniformMatrix4fv(myShaderProgram, projectionLoc, 1, false, glm::value_ptr(*projectionMatrix));

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::GeneratePoints(void)
{
	points[0] = glm::vec3(-1.0f,-1.0f,-1.0f);
	points[1] = glm::vec3(-1.0f,-1.0f, 1.0f);
	points[2] = glm::vec3(-1.0f, 1.0f, 1.0f);
	points[3] = glm::vec3(1.0f, 1.0f,-1.0f);
	points[4] = glm::vec3(-1.0f,-1.0f,-1.0f);
	points[5] = glm::vec3(-1.0f, 1.0f,-1.0f);
	points[6] = glm::vec3(1.0f,-1.0f, 1.0f);
	points[7] = glm::vec3(-1.0f,-1.0f,-1.0f);
	points[8] = glm::vec3(1.0f,-1.0f,-1.0f);
	points[9] = glm::vec3(1.0f, 1.0f,-1.0f);
	points[10] = glm::vec3(1.0f, -1.0f,-1.0f);
	points[11] = glm::vec3(-1.0f,-1.0f,-1.0f);
	points[12] = glm::vec3(-1.0f,-1.0f,-1.0f);
	points[13] = glm::vec3(-1.0f, 1.0f, 1.0f);
	points[14] = glm::vec3(-1.0f, 1.0f,-1.0f);
	points[15] = glm::vec3(1.0f,-1.0f, 1.0f);
	points[16] = glm::vec3(-1.0f,-1.0f, 1.0f);
	points[17] = glm::vec3(-1.0f,-1.0f,-1.0f);
	points[18] = glm::vec3(-1.0f, 1.0f, 1.0f);
	points[19] = glm::vec3(-1.0f,-1.0f, 1.0f);
	points[20] = glm::vec3(1.0f,-1.0f, 1.0f);
	points[21] = glm::vec3(1.0f, 1.0f, 1.0f);
	points[22] = glm::vec3(1.0f,-1.0f,-1.0f);
	points[23] = glm::vec3(1.0f, 1.0f,-1.0f);
	points[24] = glm::vec3(1.0f,-1.0f,-1.0f);
	points[25] = glm::vec3(1.0f, 1.0f, 1.0f);
	points[26] = glm::vec3(1.0f,-1.0f, 1.0f);
	points[27] = glm::vec3(1.0f, 1.0f, 1.0f);
	points[28] = glm::vec3(1.0f, 1.0f,-1.0f);
	points[29] = glm::vec3(-1.0f, 1.0f,-1.0f);
	points[30] = glm::vec3(1.0f, 1.0f, 1.0f);
	points[31] = glm::vec3(-1.0f, 1.0f,-1.0f);
	points[32] = glm::vec3(-1.0f, 1.0f, 1.0f);
	points[33] = glm::vec3(1.0f, 1.0f, 1.0f);
	points[34] = glm::vec3(-1.0f, 1.0f, 1.0f);
	points[35] = glm::vec3(1.0f,-1.0f, 1.0f);
}

glm::vec3 Cube::GetOrigin(void)
{
	return origin;
}

GLfloat Cube::GetSize(void)
{
	return size;
}

Cube::~Cube(void)
{
}
