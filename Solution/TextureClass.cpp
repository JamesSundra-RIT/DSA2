#include "TextureClass.h"

TextureClass::TextureClass(void) { Init(); }
TextureClass::TextureClass(const TextureClass& other) { }
TextureClass& TextureClass::operator=(const TextureClass& other) { return *this; }
TextureClass::~TextureClass(void) { Release(); }

void TextureClass::Release(void)
{
	m_pSystem = nullptr;
	glDeleteTextures(1, &m_nGLTextureID);
}
void TextureClass::Init(void)
{
	m_nGLTextureID = -1;
	m_pSystem = SystemClass::GetInstance();
}
void TextureClass::LoadTexture(String a_sFileName)
{
	m_sName = a_sFileName;
	m_sFileName = m_pSystem->m_pFolder->Root;
	m_sFileName += m_pSystem->m_pFolder->Data;
	m_sFileName += m_pSystem->m_pFolder->Textures;
	m_sFileName += m_sName;

	if(m_nGLTextureID == -1)
	{
		 m_nGLTextureID = SOIL_load_OGL_texture
		(
			m_sFileName.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
		);
	}
	else
	{
		m_nGLTextureID = SOIL_load_OGL_texture
		(
			m_sFileName.c_str(),
			SOIL_LOAD_AUTO,
			m_nGLTextureID,
			SOIL_FLAG_INVERT_Y
		);
	}
}
//Accessors
GLuint TextureClass::GetGLTextureID(void){return m_nGLTextureID;}
String TextureClass::GetTextureName(void){return m_sName;}
String TextureClass::GetTextureFileName(void){return m_sFileName;}