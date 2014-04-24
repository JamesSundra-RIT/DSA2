/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _MODELMANAGERCLASS_H
#define _MODELMANAGERCLASS_H

#include "InstanceClass.h"

class ModelManagerClass
{
	std::vector<ModelClass*> m_vModel; //Vector of Models
	std::vector<InstanceClass*> m_vInstance; //Vetor of Model Instances
	static ModelManagerClass* m_pInstance; //Singleton
	ModelManagerClass(void); //Constructor	
	ModelManagerClass(const ModelManagerClass& other); //Copy Constructor
	ModelManagerClass& operator=(const ModelManagerClass& other);//Copy Assignment Operator
	void Release(void); //Release the fields in the class
	void Init(void); //Initialize variables

public:
	static ModelManagerClass* GetInstance(); //Singleton Accessor
	~ModelManagerClass(void); //Destructor
	Results LoadModel (String a_sFileName, String a_sInstanceName); //Creates an instance of the specified model.
	int GetNumberOfModels(void);
	int GetNumberOfInstances(void);
	int IdentifyModel(String a_sFileName);	//Returns the index of a model in the vector
	int IdentifyInstance(String a_sName);	//Returns the index of an intance in the vector
	void RenderModel(String a_sInstance = "All_Models"); //Renders the specified instance
	void SetModelMatrix(matrix4 a_mMatrix, String a_sInstance = "All_Models"); //Modify the model matrix of the models
	matrix4 GetModelMatrix(String a_sInstance); //Returns the model matrix for the specified model, the Identity if the model does not exist
};
#endif //_MODELMANAGERCLASS