/*--------------------------------------------------------------------------------------------------
	Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _MATERIALMANAGERCLASS_H
#define _MATERIALMANAGERCLASS_H

#include "SystemClass.h"
#include "MaterialClass.h"

//namespace BTO
//{
class MaterialManagerClass
{
public:
	SystemClass* m_pSystem;
	std::vector<MaterialClass*> m_vMaterial; //Materials Vector
private:
	MaterialManagerClass(void); // Constructor
	MaterialManagerClass(MaterialManagerClass const& other); //Copy Constructor
	MaterialManagerClass& operator=(MaterialManagerClass const& other); // Copy Assignment Operator

	void Release(void); // Release Memory
	void Init(void); // Initialize variables
	
	static MaterialManagerClass* m_pInstance; // Singleton
	
public:
	static MaterialManagerClass* GetInstance(); // Singleton Accessor
	~MaterialManagerClass(void); // Destructor

	int IdentifyMaterial(String a_sName); //Identifies the material, if found return its index -1 otherwise

	//returns the index number of the material if it created a new one, otherwise it returns the index
	int AddMaterial(String a_sName);

	int GetNumberOfMaterials(void); //Return the number of materials in the vector
};
//}
//using namespace BTO;
#endif