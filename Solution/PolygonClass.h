/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _POLYGONCLASS_H
#define _POLYGONCLASS_H

#include "ShapeClass.h"

class PolygonClass : public ShapeClass
{
	typedef ShapeClass super;
public:
	//Constructor
	PolygonClass();
	//Copy Constructor
	PolygonClass(const PolygonClass& other);
	//Copy Assignment Operator
	virtual PolygonClass& operator=(const PolygonClass& other);

	//Destructor
	~PolygonClass(void);

	//Generates a shape
	void GeneratePoligon(int a_nSides = 3, float a_fSize = 1.0f);
	
	//Renders the content of the shape
	virtual void Render(GLenum mode = GL_TRIANGLE_FAN);
};

#endif //_POLYGONCLASS_H