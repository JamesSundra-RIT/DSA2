/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _TETRAHEDRON_H
#define _TETRAHEDRON_H

#include <iostream>
#include "Figure.h"

class Tetrahedron : public Figure
{
	
public:
	Point3D m_Camera;

	Tetrahedron(float _size = 1.0f, float _originX = 0.0f, float _originY = 0.0f, float _originZ = 0.0f) : 
		Figure(12, _size, _originX, _originY, _originZ) 
	{
		Point3D p0( 1.0f * _size, -1.0f * _size, 1.0f * _size);
		Point3D p1( 0.0f * _size,  1.0f * _size, 0.0f * _size);
		Point3D p2(-1.0f * _size, -1.0f * _size, 1.0f * _size);
		Point3D p3( 0.0f * _size, -1.0f * _size,-1.0f * _size);

		this->m_pPoint[0] = p0;
		this->m_pPoint[1] = p1;
		this->m_pPoint[2] = p2;

		this->m_pPoint[3] = p0;
		this->m_pPoint[4] = p3;
		this->m_pPoint[5] = p1;

		this->m_pPoint[6] = p3;
		this->m_pPoint[7] = p2;
		this->m_pPoint[8] = p1;
		
		this->m_pPoint[9] = p3;
		this->m_pPoint[10] = p0;
		this->m_pPoint[11] = p2;

		CompileFigure();
	}

	virtual void Render(void)
	{
		// Use the buffer and shader for each circle.
		glUseProgram( m_ShaderProgram );
		glBindBuffer( GL_ARRAY_BUFFER, m_Buffer );

		GLint color = glGetUniformLocation(m_ShaderProgram, "fColorIn");
		glProgramUniform4f(m_ShaderProgram, color, 1.0f, 1.0f, 1.0f, 1.0f);

		// Initialize the vertex position attribute from the vertex shader.
		GLuint loc = glGetAttribLocation( m_ShaderProgram, "vPosition" );
		glEnableVertexAttribArray( loc );
		glVertexAttribPointer( loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		// Get the location of a uniform shader variable named 'modelView'.
		GLint modelView = glGetUniformLocation(m_ShaderProgram, "modelView");
		static float angle = 0.0f;
		vec4 eye( 0.0f, 0.0f, 3.0f, 1.0f);
		//vec4 eye( sin(angle * DegreesToRadians), 0.0f, -cos(angle * DegreesToRadians), 1.0f);
		//angle += 0.1f;
		vec4 at(  0.0f, 0.0f, 0.0f, 1.0f);
		vec4 up(  0.0f, 1.0f, 0.0f, 0.0f);
		

		mat4 mv = LookAt( eye, at, up);
		glUniformMatrix4fv( modelView, 1, GL_TRUE, mv );

		GLint projection = glGetUniformLocation( m_ShaderProgram, "projection" );
		GLfloat  left = -1.0f, right = 1.0f;
		GLfloat  bottom = -1.0f, top = 1.0f;
		GLfloat  zNear = 0.5f, zFar = 3.0f;

		mat4  p = Frustum( left, right, bottom, top, zNear, zFar );
		//mat4  p = Translate( 0.0f, 0.0f, 0.0f);
		glUniformMatrix4fv( projection, 1, GL_TRUE, p );

		GLint worldLoc = glGetUniformLocation(m_ShaderProgram, "world");
		glUniformMatrix4fv(worldLoc, 1, GL_TRUE, Translate(m_Camera.x, m_Camera.y, m_Camera.z));

		// Draw the array of this figure
		glDrawArrays(GL_TRIANGLES, 0, m_nVertices);
		glProgramUniform4f(m_ShaderProgram, color, 0.0f, 0.0f, 1.0f, 1.0f);
		glDrawArrays(GL_LINE_LOOP, 0, m_nVertices);
	}

private:
	virtual void InitBuffer(void)
	{
		// Create a vertex array object
		GLuint vao;
		glGenVertexArrays( 1, &vao );
		glBindVertexArray( vao );

		// Create and initialize a buffer object for each circle.
		glGenBuffers( 1, &m_Buffer );
		glBindBuffer( GL_ARRAY_BUFFER, m_Buffer );
		glBufferData( GL_ARRAY_BUFFER, m_nVertices * sizeof(Point3D), m_pPoint, GL_STATIC_DRAW );

		// Load shaders and use the resulting shader program
		m_ShaderProgram = InitShader( "Shaders\\vshader2.glsl", "Shaders\\fshader2.glsl" );
	}
};


#endif //_TETRAHEDRON_H