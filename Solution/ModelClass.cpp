#include "ModelClass.h"
//Auxiliaries
String GetFirstWord(String input, int a_nLenght = 6)
{
	String sWord = "";
	if(static_cast<int>(input.size()) >= a_nLenght)
		for(int i = 0; i < a_nLenght; i++)
			sWord += input[i];
	return sWord;
}
//ModelClass
ModelClass::ModelClass(void) { Init(); }
ModelClass::ModelClass(const ModelClass& other)
{
	Init();
	m_vShape = other.m_vShape;
	m_sModelName = other.m_sModelName;
}
ModelClass& ModelClass::operator=(const ModelClass& other)
{
	if(this != &other)
	{
		Release();
		ModelClass Temp(other);
		Swap(Temp);
	}
	return *this;
}
void ModelClass::Swap(ModelClass& other)
{
	std::swap( m_vShape, other.m_vShape);
}
ModelClass::~ModelClass(void) { Release(); }
void ModelClass::Release(void)
{
	m_vShape.clear();
	m_pSystem = nullptr;
	m_pMaterialManager = nullptr;
	m_sModelName = "";
}
void ModelClass::Init(void)
{
	m_pSystem = SystemClass::GetInstance();
	m_pMaterialManager = MaterialManagerClass::GetInstance();
	m_sModelName = "";
}
Results ModelClass::LoadMTL(String a_sFileName)
{
	String sAbsoluteRoute;
	sAbsoluteRoute = m_pSystem->m_pFolder->Root;
	sAbsoluteRoute += m_pSystem->m_pFolder->Data;
	sAbsoluteRoute += m_pSystem->m_pFolder->MOBJ;
	sAbsoluteRoute += a_sFileName;
	
	FileReaderClass reader;
	Results result = reader.ReadFile(sAbsoluteRoute);
	if(result != Results::ERROR_FREE)
		return result;

	reader.Rewind();
	int nMaterial = -1;
	while(reader.ReadNextLine() != Results::DONE)
	{
		char* sTemp = new char[reader.m_sLine.size() +1];
		String sWord = GetFirstWord(reader.m_sLine);

		if(sWord == "newmtl")
		{
			sscanf_s(reader.m_sLine.c_str(), "newmtl %s", sTemp, reader.m_sLine.size());
			String sTempMaterial = m_sModelName + "\\" + sTemp;
			nMaterial = m_pMaterialManager->AddMaterial(sTempMaterial);
		}
		else if(sWord == "map_Kd")
		{
			sscanf_s(reader.m_sLine.c_str(), "map_Kd %s", sTemp, reader.m_sLine.size());
			if(nMaterial > -1)
				m_pMaterialManager->m_vMaterial[nMaterial]->LoadDiffuse(static_cast<String>(sTemp));
		}

		delete[] sTemp;
	}

	return ERROR_FREE;
}
Results ModelClass::LoadOBJ(String a_sFileName)
{
	String sAbsoluteRoute;
	sAbsoluteRoute = m_pSystem->m_pFolder->Root;
	sAbsoluteRoute += m_pSystem->m_pFolder->Data;
	sAbsoluteRoute += m_pSystem->m_pFolder->MOBJ;
	sAbsoluteRoute += a_sFileName;

	m_sModelName = a_sFileName;
	//m_sModelName = "";
	//int nLenght = static_cast<int>(a_sFileName.size());
	//for(int i = 0; i < nLenght -4; i++)
	//{
	//	m_sModelName += a_sFileName[i];
	//}
	
	FileReaderClass reader;
	Results result = reader.ReadFile(sAbsoluteRoute);
	if(result != Results::ERROR_FREE)
		return result;

#ifdef DEBUG
	std::cout << "File read @: " << sAbsoluteRoute << std::endl;
#endif

	reader.Rewind();
	int nGroupIndex = -1;
	std::vector<vector3> vPosition; //Vector of Vertices
	std::vector<vector3> vNormal; //Vecotr of Normals
	std::vector<vector2> vUV; //vector of UVS
	int nMaterial = 0;

	while(reader.ReadNextLine() != DONE)
	{
		char* sTemp = new char[reader.m_sLine.size() +1];
		String sWord = GetFirstWord(reader.m_sLine);
#pragma region Vertex
		if(reader.m_sLine[0] == 'v')
		{
			float x = 0.0f, y = 0.0f, z = 0.0f;
			if(reader.m_sLine[1] == ' ')
			{
				sscanf_s(reader.m_sLine.c_str(), "v %f %f %f", &x, &y, &z);
				vPosition.push_back(vector3( x, y, z ));
			}
			else if(reader.m_sLine[1] == 't')
			{
				sscanf_s(reader.m_sLine.c_str(), "vt %f %f", &x, &y);
				vUV.push_back( vector2(x, y));
			}
			else if(reader.m_sLine[1] == 'n')
			{
				sscanf_s(reader.m_sLine.c_str(), "vn %f %f %f", &x, &y, &z);
				vNormal.push_back(vector3( x, y, z ));
			}
		}
#pragma endregion
#pragma region Group
		else if(reader.m_sLine[0] == 'g')
		{
			//Verify if new group or existing one
			//If different from current Group, change nGroup Index
			String sName;

			int nLineSize = static_cast<int>(reader.m_sLine.size()) + 1;
			char* zsTemp = new char[nLineSize];
			strcpy_s(zsTemp, nLineSize, reader.m_sLine.c_str());
			
			char seps[] = " ,\t\n";

			char *token, *next_token;

			token = strtok_s(zsTemp, seps, &next_token);
			//nEmptyGroups will count the number of Empty groups at the end of the group name
			int nemprtyGroups = 0;
			String sGroupNames;
			sGroupNames = "";
			while (token != NULL)//Go to next word
			{
				sName = token;
				if(sName[0] == 'N')
				{
					if(sName[1] == 'U')
					{
						if(sName[2] == 'L')
						{
							if(sName[3] == 'L')
							{
								if(sName[4] == '_')
								{
									//This is an Empty group
								}
								else
								{
									sGroupNames += sName;
									sGroupNames + " ";
								}
							}
							else
							{
								sGroupNames += sName;
								sGroupNames += " ";
							}
						}
						else
						{
							sGroupNames += sName;
							sGroupNames += " ";
						}
					}
					else
					{
						sGroupNames += sName;
						sGroupNames += " ";
					}
				}
				else
				{
					sGroupNames += sName;
					sGroupNames += " ";
				}
				if(token != NULL)
					token = strtok_s(NULL, seps, &next_token);
			}
			delete[] zsTemp;
			zsTemp = 0;
			zsTemp = new char [sGroupNames.size() +1];
			strcpy_s(zsTemp, sGroupNames.size() +1, sGroupNames.c_str());
			token = strtok_s(zsTemp, seps, &next_token);
			while (token != NULL)//Go to next word
			{
				sName = token;

				if(token != NULL)
					token = strtok_s(NULL, seps, &next_token);
			}
			delete[] zsTemp;
			zsTemp = 0;

			if(sName != "default")
			{
				int nTemp = -1;
				for(int n = 0; n < static_cast<int> (m_vShape.size()); ++n)
				{
					if(m_vShape[n].Name == sName)
					{
						nTemp = n;
						break;
					}
				}

				if(nTemp >= 0) //Did exist
				{
					nGroupIndex = nTemp;
				}
				else //New group
				{
					ShapeClass group;
					group.Name = sName;
					m_vShape.push_back(group);
					nGroupIndex = static_cast<int>(m_vShape.size()) -1;
				}
			}
		}
#pragma endregion
#pragma region Faces
		else if(reader.m_sLine[0] == 'f')
		{
			int nP1 = 0, nT1 = 0, nN1 = 0;
			int nP2 = 0, nT2 = 0, nN2 = 0;
			int nP3 = 0, nT3 = 0, nN3 = 0;

			sscanf_s( reader.m_sLine.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
																				&nP1, &nT1, &nN1,
																				&nP2, &nT2, &nN2,
																				&nP3, &nT3, &nN3);
			m_vShape[nGroupIndex].AddVertexPosition(vPosition[nP1-1]);
			m_vShape[nGroupIndex].AddVertexPosition(vPosition[nP2-1]);
			m_vShape[nGroupIndex].AddVertexPosition(vPosition[nP3-1]);

			m_vShape[nGroupIndex].AddVertexColor(vector3(1.0f,1.0f,1.0f));
			m_vShape[nGroupIndex].AddVertexColor(vector3(1.0f,1.0f,1.0f));
			m_vShape[nGroupIndex].AddVertexColor(vector3(1.0f,1.0f,1.0f));

			m_vShape[nGroupIndex].AddVertexUV(vUV[nT1-1]);
			m_vShape[nGroupIndex].AddVertexUV(vUV[nT2-1]);
			m_vShape[nGroupIndex].AddVertexUV(vUV[nT3-1]);

			m_vShape[nGroupIndex].AddVertexNormal(vNormal[nN1-1]);
			m_vShape[nGroupIndex].AddVertexNormal(vNormal[nN2-1]);
			m_vShape[nGroupIndex].AddVertexNormal(vNormal[nN3-1]);
			m_vShape[nGroupIndex].m_nMaterialIndex = nMaterial;
		}
#pragma endregion
#pragma region Material Library
		else if(sWord == "mtllib")
		{
			sscanf_s(reader.m_sLine.c_str(), "mtllib %s", sTemp, reader.m_sLine.size());
			LoadMTL(static_cast<String>(sTemp));
		}
#pragma endregion
#pragma region Use Material
		else if(sWord == "usemtl")
		{
			sscanf_s(reader.m_sLine.c_str(), "usemtl %s", sTemp, reader.m_sLine.size());
			String sTempMaterial = m_sModelName + "\\" + sTemp;
			nMaterial = m_pMaterialManager->IdentifyMaterial(sTempMaterial);
		}
#pragma endregion
		delete[] sTemp;
	}
	for(unsigned int i = 0; i < m_vShape.size(); i++)
		m_vShape[i].InitGPU();
	return Results::ERROR_FREE;
}
int ModelClass::GetNumberOfGroups(void)
{
	return static_cast<int>(m_vShape.size());

}
ShapeClass ModelClass::ReturnShape(int a_nIndex)
{
	if(a_nIndex < 0 || a_nIndex > static_cast<int>(a_nIndex))
		assert(false);

	return m_vShape[a_nIndex];
}
String ModelClass::GetName(void){ return m_sModelName; };