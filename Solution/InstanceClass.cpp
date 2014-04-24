#include "InstanceClass.h"

InstanceClass::InstanceClass(void) { Init(); }
InstanceClass::InstanceClass(const InstanceClass& other)
{
	Init();
	m_sName = m_sName;
	m_vShape = m_vShape;
}
InstanceClass& InstanceClass::operator=(const InstanceClass& other)
{
	if(this!=&other)
	{
		Release();
		InstanceClass Temp(other);
		Init();
		Swap(Temp);
	}
	return *this;
}
void InstanceClass::Swap(InstanceClass&other)
{
	std::swap(m_mModel, other.m_mModel);
	std::swap(m_sName, other.m_sName);
	std::swap(m_vShape, other.m_vShape);
}
InstanceClass::~InstanceClass(void) { Release(); }
	
void InstanceClass::Release(void)
{
	m_vShape.clear();
}
void InstanceClass::Init(void)
{
	m_pSystem = SystemClass::GetInstance();
	m_pMaterialManager = MaterialManagerClass::GetInstance();
	m_sName = "";
}

void InstanceClass::InstanceModel(ModelClass& a_Model)
{
	Release();
	int nGroups = a_Model.GetNumberOfGroups();
	for(int i = 0; i < nGroups; i++)
	{
		ShapeClass temp = a_Model.ReturnShape(i);
		temp.ReleaseVectors();
		m_vShape.push_back(temp);
		temp.DisconectOpenGLFromShape();
	}
}

//Accessors
void InstanceClass::SetName(String a_sName){ m_sName = a_sName; }
String InstanceClass::GetName(void) { return m_sName; }
void InstanceClass::SetModelMatrix(const glm::mat4 a_mModel)
{
	m_mModel = a_mModel;
	for(unsigned int i = 0; i < m_vShape.size(); i++)
		m_vShape[i].ModelMatrix = m_mModel;
}

glm::mat4& InstanceClass::GetModelMatrix(void)
{
	return m_mModel;
}

void InstanceClass::Render(void)
{
	for(unsigned int i = 0; i < m_vShape.size(); i++)
		m_vShape[i].Render(GL_TRIANGLES);
}