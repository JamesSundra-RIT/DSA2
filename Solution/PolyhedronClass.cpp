#include "PolyhedronClass.h"

PolyhedronClass::PolyhedronClass(void) { }
PolyhedronClass::PolyhedronClass(const PolyhedronClass& other) { }
PolyhedronClass& PolyhedronClass::operator=(const PolyhedronClass& other) { return *this; }
PolyhedronClass::~PolyhedronClass(void) { }

void PolyhedronClass::GeneratePoints(int a_nLevels, float a_fSize)
{
	//Create a basic 4 sides polyhedron, values have been precalculated
	vector3 p0(-0.500000f * a_fSize,-0.408248f * a_fSize, -0.288675f * a_fSize); // Left, Down, Back 
	vector3 p1( 0.500000f * a_fSize,-0.408248f * a_fSize, -0.288675f * a_fSize); // Right, Down, Back
	vector3 p2( 0.000000f * a_fSize,-0.408248f * a_fSize,  0.577350f * a_fSize); // Center, Down, Front
	vector3 p3( 0.000000f * a_fSize, 0.408248f * a_fSize,  0.000000f * a_fSize); // Center, Up, Center

	vector3 red(1.0f, 0.0f, 0.0f);
	vector3 green(0.0f, 1.0f, 0.0f);
	vector3 blue(0.0f, 0.0f, 1.0f);
	vector3 yellow(1.0f, 1.0f, 0.0f);

	//This seccion is work in progress.
	if(a_nLevels < 0 || a_nLevels > 0)
		a_nLevels = 0;

	if(a_nLevels == 0)
	{
		//Bottom Face
		AddVertexPosition(p0);
		AddVertexPosition(p1);
		AddVertexPosition(p2);
		AddVertexColor(yellow);
		AddVertexColor(yellow);
		AddVertexColor(yellow);
		AddVertexUV(0.0f, 0.0f);
		AddVertexUV(0.0f, 0.0f);
		AddVertexUV(0.0f, 0.0f);
	
		//Right Face
		AddVertexPosition(p2);
		AddVertexPosition(p1);
		AddVertexPosition(p3);
		AddVertexColor(red);
		AddVertexColor(red);
		AddVertexColor(red);
		AddVertexUV(0.0f, 0.0f);
		AddVertexUV(0.0f, 0.0f);
		AddVertexUV(0.0f, 0.0f);

		//Back Face
		AddVertexPosition(p1);
		AddVertexPosition(p0);
		AddVertexPosition(p3);
		AddVertexColor(green);
		AddVertexColor(green);
		AddVertexColor(green);
		AddVertexUV(0.0f, 0.0f);
		AddVertexUV(0.0f, 0.0f);
		AddVertexUV(0.0f, 0.0f);

		//Left Face
		AddVertexPosition(p0);
		AddVertexPosition(p2);
		AddVertexPosition(p3);
		AddVertexColor(blue);
		AddVertexColor(blue);
		AddVertexColor(blue);
		AddVertexUV(0.0f, 0.0f);
		AddVertexUV(0.0f, 0.0f);
		AddVertexUV(0.0f, 0.0f);
	}
	InitGPU();
}
void PolyhedronClass::Render(GLenum mode)
{
	super::Render(mode);
}