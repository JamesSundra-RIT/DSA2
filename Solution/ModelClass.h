/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _MODELCLASS_H
#define _MODELCLASS_H

#include "ShapeClass.h"
#include "FileReaderClass.h"
#include "MaterialManagerClass.h"

class ModelClass
{	
	SystemClass* m_pSystem;
	MaterialManagerClass* m_pMaterialManager;
	std::vector<ShapeClass> m_vShape;
	String m_sModelName;
public:
	ModelClass(void);
	ModelClass(const ModelClass& other);
	ModelClass& operator=(const ModelClass& other);
	~ModelClass(void);
	
	void Release(void);

	Results LoadOBJ(String a_sFileName);
	Results LoadMTL(String a_sFileName);

	void Swap(ModelClass& other);

	int GetNumberOfGroups(void); //Returns the number of shapes in the vector of shapes
	String GetName(void); //Return the name of the model
	__declspec(property(get = GetName)) String Name; //Name Property

	ShapeClass ReturnShape(int a_nIndex);//Returns the shape in the given index
private:
	void Init(void);
};
#endif //_MODEL_H