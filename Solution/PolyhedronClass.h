/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _POLYHEDRON_H
#define _POLYHEDRON_H

#include "ShapeClass.h"

class PolyhedronClass : public ShapeClass
{
	typedef ShapeClass super;
public:
	//Constructor
	PolyhedronClass();
	//Copy Constructor
	PolyhedronClass(const PolyhedronClass& other);
	//Copy Assignment Operator
	virtual PolyhedronClass& operator=(const PolyhedronClass& other);

	//Destructor
	~PolyhedronClass(void);

	//Generates a shape
	void GeneratePoints(int a_nLevels = 0, float a_fSize = 1.0f);
	
	//Renders the content of the shape
	virtual void Render(GLenum mode = GL_TRIANGLES);
};

#endif //_POLYHEDRON_H