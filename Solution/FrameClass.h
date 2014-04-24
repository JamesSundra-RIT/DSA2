/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _FRAME_H
#define _FRAME_H

#include "SystemClass.h"
#include "AngelShaderCompiler.h"
#include "CameraClass.h"
#include "ShapeClass.h"

class FrameClass : public ShapeClass
{
public:
	enum MyEnum
	{
		XY = 1,
		XZ = 2,
		YZ = 4
	};
protected:
	typedef ShapeClass super;
public:
	//Constructor
	FrameClass();
	//Copy Constructor
	FrameClass(const FrameClass& other);
	//Copy Assignment Operator
	virtual FrameClass& operator=(const FrameClass& other);

	//Destructor
	~FrameClass(void);
	
	//Renders the content of the shape
	virtual void Render(GLenum mode = GL_LINES);

	//Renders a grid in the planes
	void RenderGrid(int a_nOptions, float a_fSpacing = 1.0f);

protected:
	//Generate Points
	void GeneratePoints(void);
};

#endif //_FRAME_H