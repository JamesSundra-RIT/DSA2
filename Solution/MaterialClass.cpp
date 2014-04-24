#include "MaterialClass.h"

MaterialClass::MaterialClass(String a_sName): m_sName(a_sName) { Init(); }
MaterialClass::MaterialClass(const MaterialClass& other): m_sName(other.m_sName + "1") { }
MaterialClass& MaterialClass::operator=(const MaterialClass& other) { return *this; }
MaterialClass::~MaterialClass(void) { Release(); }
	
void MaterialClass::Release(void)
{
	m_pSystem = nullptr;
	m_pTextureManager = nullptr;
}
void MaterialClass::Init(void)
{
	m_pSystem = SystemClass::GetInstance();
	m_pTextureManager = TextureManagerClass::GetInstance();
	m_nMapDiffuse = -1;
	m_nMapNormal = -1;
	m_sMapDiffuse = "";
	m_sMapNormal = "";
}
void MaterialClass::SetName(String a_sName)
{
	m_sName = a_sName;
}
String MaterialClass::GetName(void)
{
	return m_sName;
}
GLuint MaterialClass::GetDiffuseMap(void)
{
	return m_nMapDiffuse;
}
GLuint MaterialClass::GetNormalMap(void)
{
	return m_nMapNormal;
}

Results MaterialClass::LoadDiffuse(String a_sFileName)
{
	m_nMapDiffuse = m_pTextureManager->ReturnGLIndex(
			m_pTextureManager->LoadTexture(a_sFileName));
	if(m_nMapDiffuse == -1)
		return ERROR_FILE_MISSING;

	return ERROR_FREE;
}
Results MaterialClass::LoadNormal(String a_sFileName)
{
	m_nMapNormal = m_pTextureManager->ReturnGLIndex(
			m_pTextureManager->LoadTexture(a_sFileName));
	if(m_nMapNormal == -1)
		return ERROR_FILE_MISSING;

	return ERROR_FREE;
}