/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _EMPTYCLASS_H
#define _EMPTYCLASS_H

#include "SystemClass.h"
#include "TextureManagerClass.h"

class MaterialClass
{
	String m_sName;
	GLuint m_nMapDiffuse;
	GLuint m_nMapNormal;
	String m_sMapDiffuse;
	String m_sMapNormal;

	SystemClass* m_pSystem;
	TextureManagerClass* m_pTextureManager;
public:
	MaterialClass(String a_sName);
	
	MaterialClass(const MaterialClass& other);
	MaterialClass& operator=(const MaterialClass& other);
	~MaterialClass(void);
	
	void Release(void);

	void SetName(String a_sName);
	String GetName(void);
	__declspec(property(put = SetName, get = GetName)) String Name;

	GLuint GetDiffuseMap(void);
	__declspec(property(get = GetDiffuseMap)) GLuint DiffuseMap;

	GLuint GetNormalMap(void);
	__declspec(property(get = GetNormalMap)) GLuint NormalMap;

	Results LoadDiffuse(String a_sFileName);

	Results LoadNormal(String a_sFileName);

private:
	void Init(void);
};
#endif //_EMPTY_H
