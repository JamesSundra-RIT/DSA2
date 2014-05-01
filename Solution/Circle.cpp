#include "Circle.h"

Circle::Circle(glm::vec3 anOrigin, GLfloat aRadius)
{
	origin = glm::vec3(anOrigin);
	velocity = glm::vec3();
	radius = aRadius;
	GeneratePoints();
	Init();
}

Circle::Circle(const Circle& otherCircle)
{
	origin = otherCircle.origin;
	velocity = glm::vec3();
	radius = otherCircle.radius;
	GeneratePoints();
	Init();
}

Circle& Circle::operator=(const Circle& otherCircle)
{
	if(this != &otherCircle)
	{
		origin = otherCircle.origin;
		velocity = glm::vec3();
		radius = otherCircle.radius;
		GeneratePoints();
		Init();
	}

	return *this;
}

void Circle::Init()
{
	// Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

	// Create and initialize a buffer object for each circle.
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

	// Get the location of a uniform shader variable named 'ortho'.
	GLint perspectiveLoc = glGetUniformLocation(myShaderProgram, "perspective");
	// Now set it to the orthographic projection.
	//glm::mat4 cameraMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f);
	//glm::mat4 cameraMatrix = glm::frustum(-10.0f, 10.0f, -10.0f, 10.0f, .01f, 10.0f);
	//glm::mat4 cameraMatrix = glm::perspective(60.0f, 1.0f, 0.1f, 100.0f);
	//glProgramUniformMatrix4fv(myShaderProgram, perspectiveLoc, 1, false, glm::value_ptr(cameraMatrix));
}

void Circle::Render(void)
{
	// Use the buffer and shader for each circle.
	glUseProgram( myShaderProgram );
	glBindBuffer( GL_ARRAY_BUFFER, myBuffer );

	// Initialize the vertex position attribute from the vertex shader.
    GLuint loc = glGetAttribLocation( myShaderProgram, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	GLint d_loc = glGetUniformLocation(myShaderProgram, "rot");
	

	/*origin += velocity / 500.0f;

	if (origin.x + radius > 20.0f || origin.x - radius < -20.0f)
		velocity.x *= -1;

	if (origin.y + radius > 20.0f || origin.y - radius < -20.0f)
		velocity.y *= -1;*/

	glDrawArrays(GL_TRIANGLE_FAN, 0, NUM_VERTICES);
}

void Circle::GeneratePoints(void)
{
	GLfloat x, y, z, theta = 0;
	for (int i = 0; i < NUM_VERTICES; i++) 
	{
		// you could condense the following, but I expanded it to clarify the algorithm:
		theta += static_cast<GLfloat>(2*M_PI/NUM_VERTICES);
		x = static_cast<GLfloat>(radius*cos(theta));
		y = static_cast<GLfloat>(radius*sin(theta));
		// Offset the x and y coordinate by the origin, thus displacing the circle.
		x += origin.x;
		y += origin.y;
		z = 1;
		points[i] = glm::vec3(x,y,z);
	}
}

glm::vec3 Circle::GetOrigin(void)
{
	return origin;
}

GLfloat Circle::GetRadius(void)
{
	return radius;
}

Circle::~Circle(void)
{
}
void Circle::AddForce(glm::vec3 aVector)
{
	velocity += aVector;
}
