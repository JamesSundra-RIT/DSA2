#include "MaterialManagerClass.h"
//  MaterialManagerClass
MaterialManagerClass* MaterialManagerClass::m_pInstance = nullptr;
MaterialManagerClass* MaterialManagerClass::GetInstance(void)
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new MaterialManagerClass();
	}
	return m_pInstance;
}
MaterialManagerClass::MaterialManagerClass(void){Init();}
MaterialManagerClass::MaterialManagerClass(MaterialManagerClass const& other){}
MaterialManagerClass& MaterialManagerClass::operator=(MaterialManagerClass const& other) {	return *this; }
MaterialManagerClass::~MaterialManagerClass(void){Release();};

//--- Non Standard Singleton Methods
void  MaterialManagerClass::Release(void)
{
	int nMaterials = static_cast<int>(m_vMaterial.size());
	for(int i = nMaterials; i >= 0; i--)
	{
		MaterialClass* temp = m_vMaterial[i];
		delete temp;
	}
	m_vMaterial.clear();
	m_pSystem = nullptr;
}
void MaterialManagerClass::Init(void)
{
	m_pSystem = SystemClass::GetInstance();
}

int MaterialManagerClass::AddMaterial(String a_sName)
{
	int nMaterials = static_cast<int>(m_vMaterial.size());
	//Look for the material in the vector of materials, if a match is found return that material's index
	int nMaterial = IdentifyMaterial(a_sName);
	if (nMaterial != -1)
		return nMaterial;

	//if no material was found create a new material and add it to the vector
	MaterialClass* Material = new MaterialClass(a_sName);
	m_vMaterial.push_back(Material);

	//return the newly added material's index
	return m_vMaterial.size() -1;
}
int MaterialManagerClass::IdentifyMaterial(String a_sName)
{
	int nMaterials = GetNumberOfMaterials();
	for(int i = 0; i < nMaterials; i++)
	{
		if(m_vMaterial[i]->Name == a_sName)
		{
			return i;
		}
	}
	return -1;
}
int MaterialManagerClass::GetNumberOfMaterials(void)
{
	return static_cast<int>(m_vMaterial.size());
}