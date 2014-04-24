/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _SHAPECLASS_H
#define _SHAPECLASS_H
#include "SystemClass.h"
#include "CameraClass.h"
#include "AngelShaderCompiler.h"
#include "MaterialManagerClass.h"

class ShapeClass
{
public:
	glm::mat4 m_mModel; //GLM Model Matrix
	MaterialManagerClass* m_pMaterialManager; //Material Manager
	int m_nMaterialIndex; //Material of the Shape

protected:
	GLuint m_vao; //OpenGL Vertex Array Object
	GLuint m_VertexBuffer; //OpenGL Buffer (Will hold the vertex buffer pointer)
	GLuint m_ColorBuffer; //OpenGL Buffer (Will hold the color buffer pointer)
	GLuint m_UVBuffer; //OpenGL Buffer (Will hold the UV buffer pointer)
	GLuint m_NormalBuffer;	//OpenGL Buffer (will hold the Nomal Buffer)
	GLuint m_ShaderProgram; //OpenGL Shader Program

	String m_sVShaderFile; //Vertex Shader File Name
	String m_sFShaderFile; //Fragment Shader File Name

	String m_sName;

	int m_nVertices; //Number of vertices in the shape
	std::vector<vector3> m_vVertexPosition; //Vector of Vertices
	std::vector<vector3> m_vVertexColor; //Vector of Colors
	std::vector<vector3> m_vVertexNormal; //Vecotr of Normals
	std::vector<vector2> m_vVertexUV; //vector of UVS
	
	CameraClass* m_pCamera; //Pointer to the singleton of CameraClass

	bool m_bGPUInitialized; //Indicate if memory has been reserved for GPU variables

	void Init(void); //Initializes various settings

public:
	//Constructor
	ShapeClass();
	//Copy Constructor
	ShapeClass(const ShapeClass& other);
	//Copy Assignment Operator
	virtual ShapeClass& operator=(const ShapeClass& other);

	//Destructor
	~ShapeClass(void);
	
	//Release
	void Release (void);

	//Initializes the OpenGL vao, Buffer and Program
	void InitGPU(	String a_sVShaderFile = "Shaders\\vshader.glsl", 
					String a_sFShaderFile = "Shaders\\fshader.glsl");
	
	//Sets the Model Matrix in base of another Matrix (No Parameters sets the Identity)
	void SetModelMatrix(const glm::mat4 a_mModel = glm::mat4(1.0f));
	//Returns the Model Matrix
	glm::mat4& GetModelMatrix(void);
	//Property of th ModelMatrix
	__declspec(property(put = SetModelMatrix, get = GetModelMatrix)) glm::mat4 ModelMatrix;

	void SetName(String input);
	String GetName(void);
	__declspec(property(put = SetName, get = GetName)) String Name;

	//Swaps the content with other shape
	void Swap(ShapeClass& other);
	
	//Renders the content of the shape
	virtual void Render(GLenum mode = GL_TRIANGLE_FAN);

	//Adds a new point to the vector of vertices
	void AddVertexPosition(vector3 input);
	void AddVertexPosition(const float x, const float y, const float z);

	//Adds a new color to the vector of vertices
	void AddVertexColor(vector3 input);
	void AddVertexColor(const float r, const float g, const float b);

	//Adds a new normal to the vector of vertices
	void AddVertexNormal(vector3 input);
	void AddVertexNormal(const float x, const float y, const float z);

	//Adds a new uv to the vector of vertices
	void AddVertexUV(vector2 input);
	void AddVertexUV(const float u, const float v);

	//Releases the vectors (leaving the OpenGL buffer initializated)
	void ReleaseVectors(void);

	//Disconects this shape from the OpenGL Buffers, 
	//warning: do not use if buffers are not hook up with another shape, will cause memory leaks
	void DisconectOpenGLFromShape(void);

protected:
	//Clears OpenGL Buffers
	void ReleaseOpenGL(void);
private:
};

#endif //_SHAPECLASS_H