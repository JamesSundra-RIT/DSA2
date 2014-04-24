#include "TextureManagerClass.h"
TextureManagerClass* TextureManagerClass::m_pInstance = nullptr;
TextureManagerClass* TextureManagerClass::GetInstance(void)
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new TextureManagerClass();
	}
	return m_pInstance;
}
TextureManagerClass::TextureManagerClass(void) { Init(); }
TextureManagerClass::TextureManagerClass(const TextureManagerClass& other) { }
TextureManagerClass& TextureManagerClass::operator=(const TextureManagerClass& other) { return *this; }
TextureManagerClass::~TextureManagerClass(void) { Release(); }
//--- Non Standard Singleton Methods
void TextureManagerClass::Release(void)
{
	int nTextures = GetNumberOfTextures();
	for(int i = 0; i < nTextures; i++)
	{
		TextureClass* mTemp = m_vTextures[i];
		delete mTemp;
	}
}
void TextureManagerClass::Init(void) { }
int TextureManagerClass::IdentifyTexure(String a_sName)
{
	int nTextures = GetNumberOfTextures();
	for(int i = 0; i < nTextures; i++)
	{
		if(m_vTextures[i]->TextureName == a_sName)
			return i;
	}
	return -1;
}
int TextureManagerClass::LoadTexture(String a_sName)
{
	int nTexture = IdentifyTexure(a_sName);
	if(nTexture == -1)
	{
		TextureClass* texture = new TextureClass();
		texture->LoadTexture(a_sName);
		m_vTextures.push_back(texture);
		nTexture = GetNumberOfTextures() -1;
	}
	return nTexture;
}
//Accessors
int TextureManagerClass::GetNumberOfTextures(void){return static_cast<int> (m_vTextures.size());}
GLuint TextureManagerClass::ReturnGLIndex(int a_nIndex)
{
	if(a_nIndex < 0 || a_nIndex >= GetNumberOfTextures())
		assert(false); //Index out of bound

	return m_vTextures[a_nIndex]->GLTextureID;
};