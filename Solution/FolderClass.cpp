#include "FolderClass.h"
//  FolderClass
FolderClass* FolderClass::m_pInstance = nullptr;
FolderClass* FolderClass::GetInstance(void)
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new FolderClass();
	}
	return m_pInstance;
}
FolderClass::FolderClass(void){Init();}
FolderClass::FolderClass(FolderClass const& other){}
FolderClass& FolderClass::operator=(FolderClass const& other) {	return *this; }
FolderClass::~FolderClass(void){Release();};

//--- Non Standard Singleton Methods
void FolderClass::Release(void) { }
void FolderClass::Init(void)
{
	m_sRoot = GetRealProgramPath();
	if( IsDebuggerPresent() )
	{
		int nSize = m_sRoot.size();
		nSize -= 9;
		char* temporal = new char[nSize + 1];
		int i;
		for(i = 0; i < nSize; i++)
		{
			temporal[i] = m_sRoot[i];
		}
		temporal[i] = '\0';
		m_sRoot = temporal;
		delete[] temporal;
		m_sRoot += "_Binary\\";
	}
	m_sData = "Data\\";
	m_s3DS = "M3DS\\";
	m_sBTO = "MBTO\\";
	m_sPOM = "MPOM\\";
	m_sFBX = "MFBX\\";
	m_sOBJ = "MOBJ\\";
	m_sWRL = "WRL\\";
	m_sTextures = "Textures\\";
}
String FolderClass::GetRealProgramPath(void)
{
	TCHAR stCurrentDir[MAX_PATH];
	//Get the Program Path, the directory on which the program lives
	GetModuleFileName( 0, stCurrentDir, MAX_PATH);
	char* zsTemp1 = new char[MAX_PATH];
	if(!zsTemp1)
		return NULL;
	strcpy_s(zsTemp1, MAX_PATH, "");
	int nCounter = 0;
	while(stCurrentDir[nCounter] != 0)
	{
		zsTemp1[nCounter] = static_cast<char> (stCurrentDir[nCounter]);
		nCounter++;
	}
	zsTemp1[nCounter] = 0;
	
	// Count backwards until a slash is found or zero
	while(nCounter > 0)
	{
		if(zsTemp1[nCounter] == '\\')
			break;
		nCounter--;
	}
	char* zsTemp2 = new char[nCounter +2];
	if(!zsTemp2)
		return NULL;
	for(int n = 0; n < nCounter +1; n++)
	{
		zsTemp2[n] = zsTemp1[n];
	}
	zsTemp2[nCounter+1] = 0;
	delete[] zsTemp1;
	zsTemp1 = 0;
	//delete[] zsTemp2;
	//zsTemp2 = 0;
	return static_cast<String> (zsTemp2);
}

//m_sRoot
void FolderClass::SetFolderRoot(String input) {  m_sRoot = input; }
String FolderClass::GetFolderRoot(void) { return m_sRoot; }

//m_sData
void FolderClass::SetFolderData(String input) { m_sData = input; }
String FolderClass::GetFolderData(void) { return m_sData; }

//m_sTextures
void FolderClass::SetFolderTextures(String input) { m_sTextures = input; }
String FolderClass::GetFolderTextures(void) { return m_sTextures; }

//m_sM3DS
void FolderClass::SetFolderM3DS(String input) { m_s3DS = input; }
String FolderClass::GetFolderM3DS(void) { return m_s3DS; }

//m_sMBTO
void FolderClass::SetFolderMBTO(String input) { m_sBTO = input; }
String FolderClass::GetFolderMBTO(void) { return m_sBTO; }

//m_sMPOM
void FolderClass::SetFolderMPOM(String input) { m_sPOM = input; }
String FolderClass::GetFolderMPOM(void) { return m_sPOM; }

//m_sMFBX
void FolderClass::SetFolderMFBX(String input) { m_sFBX = input; }
String FolderClass::GetFolderMFBX(void) { return m_sFBX; }

//m_sMOBJ
void FolderClass::SetFolderMOBJ(String input) { m_sOBJ = input; }
String FolderClass::GetFolderMOBJ(void) { return m_sOBJ; }

//m_sWRL
void FolderClass::SetFolderWRL(String input) { m_sWRL = input; }
String FolderClass::GetFolderWRL(void) { return m_sWRL; }