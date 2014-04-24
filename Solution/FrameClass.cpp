#include "FrameClass.h"

FrameClass::FrameClass() { 	GeneratePoints(); }
FrameClass::FrameClass(const FrameClass& other) { }
FrameClass& FrameClass::operator=(const FrameClass& other) { return *this; }
FrameClass::~FrameClass() { }

void FrameClass::GeneratePoints(void)
{
	//Asign values for the FrameClass points
	AddVertexPosition(-100.0f, 0.0f, 0.0f);
	AddVertexPosition( 100.0f, 0.0f, 0.0f);
	AddVertexColor( 1.0f, 0.0f, 0.0f);
	AddVertexColor( 1.0f, 0.0f, 0.0f);
	AddVertexUV(0.0f, 0.0f);
	AddVertexUV(0.0f, 0.0f);

	AddVertexPosition( 0.0f,-100.0f, 0.0f);
	AddVertexPosition( 0.0f, 100.0f, 0.0f);
	AddVertexColor( 0.0f, 1.0f, 0.0f);
	AddVertexColor( 0.0f, 1.0f, 0.0f);
	AddVertexUV(0.0f, 0.0f);
	AddVertexUV(0.0f, 0.0f);
	
	AddVertexPosition( 0.0f, 0.0f,-100.0f);
	AddVertexPosition( 0.0f, 0.0f, 100.0f);
	AddVertexColor( 0.0f, 0.0f, 1.0f);
	AddVertexColor( 0.0f, 0.0f, 1.0f);
	AddVertexUV(0.0f, 0.0f);
	AddVertexUV(0.0f, 0.0f);

	InitGPU();
}

void FrameClass::Render(GLenum mode)
{
	super::Render(mode);
}
void FrameClass::RenderGrid(int a_nOption, float a_fSpacing)
{
	if(!m_bGPUInitialized)
		return;

	// Use the buffer and shader
	glUseProgram( m_ShaderProgram );

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MatrixID = glGetUniformLocation( m_ShaderProgram, "MVP" );
	GLuint vPosition = glGetAttribLocation( m_ShaderProgram, "vPosition" );
	GLuint vColor = glGetAttribLocation( m_ShaderProgram, "vColor" );
	
	// Final Projection of the Camera
	glm::mat4 MVP;

	//position
	glEnableVertexAttribArray( vPosition );
	glBindBuffer( GL_ARRAY_BUFFER, m_VertexBuffer );
	glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	//Color
	glEnableVertexAttribArray( vColor );
	glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
	glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	switch (a_nOption)
	{
	case MyEnum::XY:
#pragma region CASEXY
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(0.0, a_fSpacing * i, 0.0f )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 0, 2);
		}
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(a_fSpacing * i, 0.0, 0.0f )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 2, 2);
		}
#pragma endregion
		break;
	case MyEnum::XZ:
#pragma region CASEXZ
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(0.0, 0.0f, a_fSpacing * i )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 0, 2);
		}
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(a_fSpacing * i, 0.0, 0.0f )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 4, 2);
		}
#pragma endregion
		break;
	case MyEnum::YZ:
#pragma region CASEYZ
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(0.0, a_fSpacing * i, 0.0f )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 4, 2);
		}
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3( 0.0, 0.0f, a_fSpacing * i )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 2, 2);
		}
#pragma endregion
		break;
	case MyEnum::XY | MyEnum::XZ:
#pragma region CASEXY|XZ
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(0.0, a_fSpacing * i, 0.0f )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 0, 2);
		}
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(a_fSpacing * i, 0.0, 0.0f )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 2, 2);
		}
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(0.0, 0.0f, a_fSpacing * i )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 0, 2);
		}
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(a_fSpacing * i, 0.0, 0.0f )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 4, 2);
		}
#pragma endregion
		break;
	case MyEnum::XY | MyEnum::YZ:
#pragma region CASEXY|YZ
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(0.0, a_fSpacing * i, 0.0f )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 0, 2);
		}
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(a_fSpacing * i, 0.0, 0.0f )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 2, 2);
		}
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(0.0, a_fSpacing * i, 0.0f )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 4, 2);
		}
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3( 0.0, 0.0f, a_fSpacing * i )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 2, 2);
		}
#pragma endregion
		break;
	case MyEnum::XY | MyEnum::XZ | MyEnum::YZ:
#pragma region CASEXY|XZ|YZ
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(0.0, a_fSpacing * i, 0.0f )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 0, 2);
		}
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(a_fSpacing * i, 0.0, 0.0f )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 2, 2);
		}
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(0.0, 0.0f, a_fSpacing * i )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 0, 2);
		}
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(a_fSpacing * i, 0.0, 0.0f )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 4, 2);
		}
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3(0.0, a_fSpacing * i, 0.0f )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 4, 2);
		}
		for(int i = -100; i < 100; i ++)
		{
			MVP = m_pCamera->CalculateProjection(glm::translate(m_mModel, vector3( 0.0, 0.0f, a_fSpacing * i )));
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
			glDrawArrays(GL_LINES, 2, 2);
		}
#pragma endregion
		break;
	}
	Render();
}