#include "ModelManagerClass.h"
ModelManagerClass* ModelManagerClass::m_pInstance = nullptr;
ModelManagerClass* ModelManagerClass::GetInstance(void)
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new ModelManagerClass();
	}
	return m_pInstance;
}
ModelManagerClass::ModelManagerClass(void) { Init(); }
ModelManagerClass::ModelManagerClass(const ModelManagerClass& other) { }
ModelManagerClass& ModelManagerClass::operator=(const ModelManagerClass& other) { return *this; }
ModelManagerClass::~ModelManagerClass(void) { Release(); }
//--- Non Standard Singleton Methods
void ModelManagerClass::Release(void)
{
	int nInstances =  GetNumberOfInstances();
	int nModels =  GetNumberOfModels();
	for(int i = 0; i < nInstances; i++)
	{
		InstanceClass* temp = m_vInstance[i];
		delete temp;
	}
	for(int i = 0; i < nModels; i++)
	{
		ModelClass* temp = m_vModel[i];
		delete temp;
	}
	m_vInstance.clear();
	m_vModel.clear();
}
void ModelManagerClass::Init(void) { }
int ModelManagerClass::GetNumberOfInstances(void)
{
	return static_cast<int>(m_vInstance.size());
}
int ModelManagerClass::GetNumberOfModels(void)
{
	return static_cast<int>(m_vModel.size());
}
int ModelManagerClass::IdentifyModel(String a_sFileName)
{
	int nModels = GetNumberOfModels();
	for(int i = 0; i < nModels; i++)
	{
		if(a_sFileName == m_vModel[i]->Name)
			return i;
	}
	return -1;
}
int ModelManagerClass::IdentifyInstance(String a_sName)
{
	int nInstances = GetNumberOfInstances();
	for(int i = 0; i < nInstances; i++)
	{
		if(a_sName == m_vInstance[i]->Name)
			return i;
	}
	return -1;
}
Results ModelManagerClass::LoadModel(String a_sFileName, String a_sInstanceName)
{
	static int nInstanceFailSafe = 0;
	int nModel = IdentifyModel(a_sFileName);
	if(nModel == -1) //new model
	{
		ModelClass* model = new ModelClass();
		if(model->LoadOBJ(a_sFileName) == ERROR_FREE)
		{
			m_vModel.push_back(model);
			InstanceClass* instance = new InstanceClass();
			instance->InstanceModel(*model);
			String sInstanceName = a_sInstanceName;
			int nInstance = IdentifyInstance(sInstanceName);
			while(nInstance != -1)
			{
				sInstanceName = a_sInstanceName + std::to_string(nInstanceFailSafe);
				nInstance = IdentifyInstance(sInstanceName);
				nInstanceFailSafe++;
			}
			instance->Name = sInstanceName;
			m_vInstance.push_back(instance);
		}
	}
	else //Model already in pile
	{
		InstanceClass* instance = new InstanceClass();
		instance->InstanceModel(*m_vModel[nModel]);
		String sInstanceName = a_sInstanceName;
		int nInstance = IdentifyInstance(sInstanceName);
		while(nInstance != -1)
		{
			sInstanceName = a_sInstanceName + std::to_string(nInstanceFailSafe);
			nInstance = IdentifyInstance(sInstanceName);
			nInstanceFailSafe++;
		}
		instance->Name = sInstanceName;
		m_vInstance.push_back(instance);
	}

	return ERROR_FREE;
}
void ModelManagerClass::RenderModel(String a_sInstance)
{
	if(a_sInstance == "All_Models")
	{
		int nInstances = GetNumberOfInstances();
		for(int i = 0; i < nInstances; i++)
		{
			m_vInstance[i]->Render();
		}
	}
	else
	{
		int nInstance = IdentifyInstance(a_sInstance);
		if(nInstance == -1)
			return;
		m_vInstance[nInstance]->Render();
	}
}
void ModelManagerClass::SetModelMatrix(glm::mat4 a_mMatrix, String a_sInstance)
{
	if(a_sInstance == "All_Models")
	{
		int nInstances = GetNumberOfInstances();
		for(int i = 0; i < nInstances; i++)
		{
			m_vInstance[i]->ModelMatrix = a_mMatrix;
		}
	}
	else
	{
		int nInstance = IdentifyInstance(a_sInstance);
		if(nInstance >= 0)
		{
			m_vInstance[nInstance]->ModelMatrix = a_mMatrix;
		}
	}
}
matrix4 ModelManagerClass::GetModelMatrix(String a_sInstance)
{
	matrix4 matrix = matrix4(1.0f);
	int nInstance = IdentifyInstance(a_sInstance);
	if(nInstance >= 0)
	{
		matrix = m_vInstance[nInstance]->ModelMatrix;
	}

	return matrix;
}