/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _TEXTUREMANAGERCLASS_H
#define _TEXTUREMANAGERCLASS_H

#include "TextureClass.h"

class TextureManagerClass
{
	static TextureManagerClass* m_pInstance; //Singleton
	TextureManagerClass(void); //Constructor	
	TextureManagerClass(const TextureManagerClass& other); //Copy Constructor
	TextureManagerClass& operator=(const TextureManagerClass& other);//Copy Assignment Operator
	void Release(void); //Release the fields in the class
	void Init(void); //Initialize variables

public:
	std::vector<TextureClass*> m_vTextures; //Vector of Textures
	static TextureManagerClass* GetInstance(); //Singleton Accessor
	~TextureManagerClass(void); //Destructor
	int IdentifyTexure(String sName); //Returns the ID number of the texture, -1 if it does not exist.
	int LoadTexture(String sName);	//Loads a texture and returns the ID of where its stored in the vector
//Accessors
	int GetNumberOfTextures(void); //Returns the number of texures in the vector
	GLuint ReturnGLIndex(int a_nIndex); //Returns the OpenGL Buffer ID in the vector location of the provided Index

};
#endif //_EMPTYSINGLETONCLASS_H