/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _INSTANCECLASS_H
#define _INSTANCECLASS_H

#include "ModelClass.h"

class InstanceClass
{
	SystemClass* m_pSystem;
	MaterialManagerClass* m_pMaterialManager;		

	String m_sName; //Example Variable
	std::vector<ShapeClass> m_vShape; //Vector of shapes

	glm::mat4 m_mModel; //GLM Model Matrix
public:
	InstanceClass(void); //Constructor
	InstanceClass(const InstanceClass& other); //Copy Constructor
	InstanceClass& operator=(const InstanceClass& other); //Copy Assignment Operator
	void Release(void); //Release the fields in the class
	~InstanceClass(void); //Destructor

	void InstanceModel(ModelClass& a_Model); //Create an Instance of a previously loaded model

	void Render(void);//Render all groups

	void Swap(InstanceClass& other); //Swaps Content with other Instance class

//Accessors
	void SetModelMatrix(const glm::mat4 a_mModel = glm::mat4(1.0f));
	glm::mat4& GetModelMatrix(void);
	__declspec(property(put = SetModelMatrix, get = GetModelMatrix)) glm::mat4 ModelMatrix;

	void SetName(String a_sName); //Sets Variable
	String GetName(void);//Gets Variable
	__declspec(property(get = GetName, put = SetName)) String Name; //Property
private:
	void Init(void); //Initializes the variables
};
#endif //_INSTANCECLASS_H
