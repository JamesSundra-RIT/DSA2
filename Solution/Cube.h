#ifndef __CUBE_H_
#define __CUBE_H_

//Header to include all the necessary headers and definitions to our application.
#include "System.h"

class Cube
{
	public:
		Cube(glm::vec3 anOrigin, GLfloat size);
		Cube(const Cube& otherCube);
		Cube& Cube::operator=(const Cube& otherCube);
		virtual ~Cube(void);
		
		void Init(void);
		void Render(glm::mat4x4* projectionMaxtrix, glm::mat4x4* viewMatrix);
		glm::vec3 GetOrigin(void);
		GLfloat GetSize(void);
		
	private:
		void GeneratePoints(void);

		glm::vec3 origin;
		GLfloat size;
		glm::vec3 points[36]; 
		GLuint  myShaderProgram;
		GLuint	myBuffer;
};

#endif //__CUBE_H_