/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _FOLDERCLASS_H
#define _FOLDERCLASS_H

#include <string>
#include <Windows.h>

typedef std::string String;
class FolderClass
{
public:
	static FolderClass* GetInstance(void);
	~FolderClass(void);

	void SetFolderRoot(String input);
	String GetFolderRoot(void);
	__declspec(property(put = SetFolderRoot, get = GetFolderRoot)) String Root;

	void SetFolderData(String input);
	String GetFolderData(void);
	__declspec(property(put = SetFolderData, get = GetFolderData)) String Data;

	void SetFolderM3DS(String input);
	String GetFolderM3DS(void);
	__declspec(property(put = SetFolderM3DS, get = GetFolderM3DS)) String M3DS;

	void SetFolderMBTO(String input);
	String GetFolderMBTO(void);
	__declspec(property(put = SetFolderMBTO, get = GetFolderMBTO)) String MBTO;

	void SetFolderMPOM(String input);
	String GetFolderMPOM(void);
	__declspec(property(put = SetFolderMPOM, get = GetFolderMPOM)) String MPOM;

	void SetFolderMFBX(String input);
	String GetFolderMFBX(void);
	__declspec(property(put = SetFolderMFBX, get = GetFolderMFBX)) String MFBX;

	void SetFolderMOBJ(String input);
	String GetFolderMOBJ(void);
	__declspec(property(put = SetFolderMOBJ, get = GetFolderMOBJ)) String MOBJ;

	void SetFolderWRL(String input);
	String GetFolderWRL(void);
	__declspec(property(put = SetFolderWRL, get = GetFolderWRL)) String WRL;

	void SetFolderTextures(String input);
	String GetFolderTextures(void);
	__declspec(property(put = SetFolderTextures, get = GetFolderTextures)) String Textures;

private:
	String m_sRoot;
	String m_sData;
	String m_s3DS;
	String m_sBTO;
	String m_sPOM;
	String m_sFBX;
	String m_sOBJ;
	String m_sWRL;
	String m_sTextures;

	static FolderClass* m_pInstance;

	FolderClass(void);
	FolderClass(const FolderClass& other);
	FolderClass& operator=(const FolderClass& other);

	void Init(void);
	void Release(void);

	String GetRealProgramPath(void);
};


#endif //_FOLDERCLASS_H
