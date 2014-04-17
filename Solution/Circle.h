/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2014
--------------------------------------------------------------------------------------------------*/
#ifndef __CIRCLE_H_
#define __CIRCLE_H_

//Header to include all the necessary headers and definitions to our application.
#include "System.h"

const int NUM_VERTICES = 100; // Lower to increase performance but lower circle 'roundness'.

class Circle
{
	public:
		Circle(glm::vec3 anOrigin, GLfloat aRadius);
		Circle(const Circle& otherCircle);
		Circle& Circle::operator=(const Circle& otherCircle);
		virtual ~Circle(void);
		
		void Init(void);
		void Render(void);
		glm::vec3 GetOrigin(void);
		GLfloat GetRadius(void);
		void AddForce(glm::vec3 vForce);
		
	private:
		void GeneratePoints(void);

		glm::vec3 origin;
		glm::vec3 velocity;
		GLfloat radius;
		glm::vec3 points[NUM_VERTICES]; 
		GLuint  myShaderProgram;
		GLuint	myBuffer;
};

#endif //__CIRCLE_H_