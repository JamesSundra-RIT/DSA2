#include "PolygonClass.h"

PolygonClass::PolygonClass() { }
PolygonClass::PolygonClass(const PolygonClass& other) { }
PolygonClass& PolygonClass::operator=(const PolygonClass& other) { return *this; }
PolygonClass::~PolygonClass(void) { }

void PolygonClass::GeneratePoligon(int a_nSides, float a_fSize)
{
	GLfloat theta = 0;
	for (int i = 0; i < a_nSides; i++) 
	{
		theta += static_cast<GLfloat>(2*M_PI/a_nSides);
		AddVertexPosition(vector3(	static_cast<GLfloat>(cos(theta)) * a_fSize,
							static_cast<GLfloat>(sin(theta)) * a_fSize,
							0.0f));
		AddVertexColor( 1.0f, 1.0f, 1.0f);
		AddVertexUV( 0.0f, 0.0f);
		AddVertexNormal(0.0f, 0.0f, 0.0f);
		AddVertexTangent(0.0f, 0.0f, 0.0f);
	}
	InitGPU();
}

void PolygonClass::Render(GLenum mode)
{
	super::Render(mode);
}