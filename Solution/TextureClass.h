/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _TEXTURECLASS_H
#define _TEXTURECLASS_H

#include "SystemClass.h"
#include "SOIL.h"

class TextureClass
{
	SystemClass* m_pSystem;
	GLuint m_nGLTextureID;
	String m_sName;
	String m_sFileName;
public:
	TextureClass(void); //Constructor
	TextureClass(const TextureClass& other); //Copy Constructor
	TextureClass& operator=(const TextureClass& other); //Copy Assignment Operator
	void Release(void); //Release the fields in the class
	~TextureClass(void); //Destructor

	void LoadTexture(String a_sFileName);
//Accessors
	GLuint GetGLTextureID(void); //Returns the OpenGL Identifier
	__declspec(property(get = GetGLTextureID)) GLuint GLTextureID;
	String GetTextureName(void); //Returns the name of the texture
	__declspec(property(get = GetTextureName)) String TextureName;
	String GetTextureFileName(void); //Returns the filename of the texture
	__declspec(property(get = GetTextureFileName)) String TextureFileName;

private:
	void Init(void); //Initializes the variables
};
#endif //_TEXTURECLASS_H
