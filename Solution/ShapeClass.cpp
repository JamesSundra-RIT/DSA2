#include "ShapeClass.h"
void ShapeClass::Init(void)
{
	m_vao = 0;
	m_ShaderProgram = 0;

	m_VertexBuffer = 0;
	m_ColorBuffer = 0;
	m_NormalBuffer = 0;
	m_TangentBuffer = 0;
	m_UVBuffer = 0;

	m_nVertices = 0;

	m_sVShaderFile = "";
	m_sFShaderFile = "";

	m_sName = "";

	m_bGPUInitialized = false;
	
	SetModelMatrix();

	m_pMaterialManager = MaterialManagerClass::GetInstance();
	m_pCamera = CameraClass::GetInstance();

	m_nMaterialIndex = -1;
}
ShapeClass::ShapeClass() { Init(); }
ShapeClass::ShapeClass(const ShapeClass& other)
{
	Init();

	m_mModel = other.m_mModel;
	m_nVertices = other.m_nVertices;
	m_sName = other.m_sName;

	m_ShaderProgram = other.m_ShaderProgram;

	m_nMaterialIndex = other.m_nMaterialIndex;
	m_VertexBuffer = other.m_VertexBuffer;
	m_ColorBuffer = other. m_ColorBuffer;
	m_UVBuffer = other.m_UVBuffer;
	m_NormalBuffer = other.m_NormalBuffer;
	m_TangentBuffer = other.m_TangentBuffer;

	m_vVertexPosition = other.m_vVertexPosition;
	m_vVertexColor = other.m_vVertexColor;
	m_vVertexUV = other.m_vVertexUV;
	m_vVertexNormal = other.m_vVertexNormal;
	m_vVertexTangent = other.m_vVertexTangent;

	m_sVShaderFile = other.m_sVShaderFile;
	m_sFShaderFile = other.m_sFShaderFile;

	m_bGPUInitialized = other.m_bGPUInitialized;
}

ShapeClass& ShapeClass::operator=(const ShapeClass& other)
{
	if(this != &other)
	{
		Release();
		ShapeClass temporal(other);
		Swap(temporal);
	}
	return *this;
}

void ShapeClass::Swap(ShapeClass& other)
{
	std::swap(this->m_vao, other.m_vao);
	std::swap(this->m_VertexBuffer, other.m_VertexBuffer);
	std::swap(this->m_ColorBuffer, other.m_ColorBuffer);
	std::swap(this->m_ShaderProgram, other.m_ShaderProgram);

	std::swap(this->m_sVShaderFile, other.m_sVShaderFile);
	std::swap(this->m_sFShaderFile, other.m_sFShaderFile);

	std::swap(this->m_vVertexPosition, other.m_vVertexPosition);
	std::swap(this->m_vVertexColor, other.m_vVertexColor);
	std::swap(this->m_vVertexNormal, other.m_vVertexNormal);
	std::swap(this->m_vVertexTangent, other.m_vVertexTangent);
	std::swap(this->m_vVertexUV, other.m_vVertexUV);

	std::swap(this->m_mModel, other.m_mModel);

	std::swap(this->m_bGPUInitialized, other.m_bGPUInitialized);
}

ShapeClass::~ShapeClass(void)
{
	Release();
	m_pCamera = nullptr;
	m_pMaterialManager = nullptr;
}

void ShapeClass::Release (void)
{
	ReleaseVectors();
	//CleanUp VBO, Buffer and Shader Program
	ReleaseOpenGL();
}
void ShapeClass::ReleaseVectors(void)
{
	m_vVertexPosition.clear();
	m_vVertexColor.clear();
	m_vVertexUV.clear();
	m_vVertexNormal.clear();
	m_vVertexTangent.clear();
}
void ShapeClass::ReleaseOpenGL(void)
{
	if(m_NormalBuffer >= 0 )
	{
		glDeleteBuffers(1, &m_NormalBuffer);
		m_NormalBuffer = -1;
	}
	if(m_TangentBuffer >=0 )
	{
		glDeleteBuffers(1, &m_TangentBuffer);
		m_TangentBuffer = -1;
	}
	if(m_UVBuffer >= 0 )
	{
		glDeleteBuffers(1, &m_UVBuffer);
		m_UVBuffer = -1;
	}
	if(m_ColorBuffer >= 0 )
	{
		glDeleteBuffers(1, &m_ColorBuffer);
		m_ColorBuffer = -1;
	}
	if(m_VertexBuffer >= 0 )
	{
		glDeleteBuffers(1, &m_VertexBuffer);
		m_VertexBuffer = -1;
	}
	if(m_ShaderProgram >= 0 )
	{
		glDeleteProgram(m_ShaderProgram);
		m_ShaderProgram = -1;
	}
	if(m_vao >= 0 )
	{
		glDeleteVertexArrays(1, &m_vao);
		m_vao = -1;
	}
}
void ShapeClass::DisconectOpenGLFromShape(void)
{
	m_NormalBuffer = -1;
	m_TangentBuffer = -1;
	m_UVBuffer = -1;
	m_ColorBuffer = -1;
	m_VertexBuffer = -1;
	m_ShaderProgram = -1;
	m_vao = -1;
}

void ShapeClass::SetModelMatrix(const glm::mat4 a_mModel)
{
	m_mModel = a_mModel;
}

glm::mat4& ShapeClass::GetModelMatrix(void)
{
	return m_mModel;
}

void ShapeClass::AddVertexPosition(const float x, const float y, const float z)
{
	AddVertexPosition(vector3(x,y,z));
}
void ShapeClass::AddVertexPosition(vector3 input)
{
	m_vVertexPosition.push_back(input);
	m_nVertices++;
}
void ShapeClass::AddVertexColor(const float r, const float g, const float b)
{
	AddVertexColor(vector3(r,g,b));
}
void ShapeClass::AddVertexColor(vector3 input)
{
	m_vVertexColor.push_back(input);
}
void ShapeClass::AddVertexNormal(const float x, const float y, const float z)
{
	AddVertexNormal(vector3(x,y,z));
}
void ShapeClass::AddVertexNormal(vector3 input)
{
	m_vVertexNormal.push_back(input);
}

void ShapeClass::AddVertexTangent(const float x, const float y, const float z)
{
	AddVertexTangent(vector3(x, y, z));
}

void ShapeClass::AddVertexTangent(vector3 input)
{
	m_vVertexTangent.push_back(input);
}

void ShapeClass::AddVertexUV(const float u, const float v)
{
	AddVertexUV(vector2(u,v));
}
void ShapeClass::AddVertexUV(vector2 input)
{
	m_vVertexUV.push_back(input);
}

void ShapeClass::SetName(String input) { m_sName = input; }
String ShapeClass::GetName(void) { return m_sName; }

void ShapeClass::InitGPU(String a_sVShaderFile, String a_sFShaderFile)
{
	if(m_bGPUInitialized)
		ReleaseOpenGL();

	// Create a vertex array object
	glGenVertexArrays( 1, &m_vao );
	glBindVertexArray( m_vao );

	// Create and initialize a buffer object for each shape.
	glGenBuffers( 1, &m_VertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, m_VertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, m_nVertices * sizeof(vector3), &m_vVertexPosition[0], GL_STATIC_DRAW );

	//Initialize the color buffer for the object.
	glGenBuffers(1, &m_ColorBuffer);
	glBindBuffer( GL_ARRAY_BUFFER, m_ColorBuffer);
	glBufferData( GL_ARRAY_BUFFER, m_nVertices * sizeof(vector3), &m_vVertexColor[0], GL_STATIC_DRAW );

	//Initialize the UV Buffer for the object
	glGenBuffers(1, &m_UVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_nVertices * sizeof(vector2), &m_vVertexUV[0], GL_STATIC_DRAW);

	//normal
	glGenBuffers(1, &m_NormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_nVertices * sizeof(vector3), &m_vVertexNormal[0], GL_STATIC_DRAW);

	//tangent
  	glGenBuffers(1, &m_TangentBuffer);
  	glBindBuffer(GL_ARRAY_BUFFER, m_TangentBuffer);
  	glBufferData(GL_ARRAY_BUFFER, m_nVertices * sizeof(vector3), &m_vVertexTangent[0], GL_STATIC_DRAW);

	m_sVShaderFile = a_sVShaderFile;
	m_sFShaderFile = a_sFShaderFile;

	// Initialize the shaders
	m_ShaderProgram = CompileShader( m_sVShaderFile.c_str(), m_sFShaderFile.c_str() );

	if(m_nMaterialIndex == -1)
	{
		m_nMaterialIndex = m_pMaterialManager->AddMaterial(m_sName + "\\Material");
	}

	m_bGPUInitialized = true;
}

void ShapeClass::Render (GLenum mode)
{
	if(!m_bGPUInitialized)
		return;

	// Use the buffer and shader
	glUseProgram( m_ShaderProgram );

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MatrixID = glGetUniformLocation( m_ShaderProgram, "MVP" );
	GLuint vPosition = glGetAttribLocation( m_ShaderProgram, "vPosition" );
	GLuint vUV = glGetAttribLocation( m_ShaderProgram, "vUV" );
	GLuint vColor = glGetAttribLocation( m_ShaderProgram, "vColor" );
	GLuint normal = glGetAttribLocation(m_ShaderProgram, "normal");
	GLuint tangent = glGetAttribLocation(m_ShaderProgram, "tangent");
	GLuint TextureID  = glGetUniformLocation(m_ShaderProgram, "TextureID");


	GLuint model = glGetUniformLocation(m_ShaderProgram, "model");
	GLuint view = glGetUniformLocation(m_ShaderProgram, "view");

	GLuint hiliteColor = glGetUniformLocation(m_ShaderProgram, "hiliteColor");
	GLuint lightPosition = glGetUniformLocation(m_ShaderProgram, "lightPosition");
	GLuint eyePosition = glGetUniformLocation(m_ShaderProgram, "eyePosition");
	GLuint r = glGetUniformLocation(m_ShaderProgram, "r");
	GLuint d = glGetUniformLocation(m_ShaderProgram, "d");

	

	GLuint nTexture = glGetUniformLocation(m_ShaderProgram, "nTexture");
	
	// Final Projection of the Camera
	glm::mat4 MVP = m_pCamera->CalculateProjection(m_mModel);
	glm::mat4 viewMat = m_pCamera->GetView();
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_mModel));
	glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));

	glUniform3fv(hiliteColor, 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5))); //rgb between 0-1
	glUniform3fv(lightPosition, 1, glm::value_ptr(glm::vec3(0.0, 1.5, 1.0))); //position light is coming from
	glUniform3fv(eyePosition, 1, glm::value_ptr(m_pCamera->GetPosition())); //position of viewer

	glUniform1f(d, 0.8); //between 0-1; diffraction (width of bump)
	glUniform1f(r, 4.0); //roughness factor

	//normal
	glEnableVertexAttribArray(normal);
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalBuffer);
	glVertexAttribPointer(normal, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);

	//tangent
	glEnableVertexAttribArray(tangent);
	glBindBuffer(GL_ARRAY_BUFFER, m_TangentBuffer);
	glVertexAttribPointer(tangent, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);


	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_pMaterialManager->m_vMaterial[m_nMaterialIndex]->DiffuseMap);
	glUniform1i(TextureID, 0);
	if(m_pMaterialManager->m_vMaterial[m_nMaterialIndex]->DiffuseMap != -1)
		glUniform1i(nTexture, 1);

	//position
	glEnableVertexAttribArray( vPosition );
	glBindBuffer( GL_ARRAY_BUFFER, m_VertexBuffer );
	glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	//Color
	glEnableVertexAttribArray( vColor );
	glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
	glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	//UV
	glEnableVertexAttribArray(vUV);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBuffer);
	glVertexAttribPointer( vUV, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	//Color and draw
	glDrawArrays(mode, 0, static_cast<int>(m_nVertices));
}