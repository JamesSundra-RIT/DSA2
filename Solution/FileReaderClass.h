/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _FILEREADERCLASS_H
#define _FILEREADERCLASS_H

#include "SystemClass.h"

class FileReaderClass
{
	SystemClass* m_pSystem;
	FILE* m_pFile;
public:
	String m_sLine;
private:
	void Init(void);
public:
	FileReaderClass(void);
	
	FileReaderClass(const FileReaderClass& other);
	FileReaderClass& operator=(const FileReaderClass& other);
	~FileReaderClass(void);
	
	void Release(void);

	void Rewind(void) const;

	Results ReadFile(String a_sFileName);
	void CloseFile(void);
	Results ReadNextLine(bool bSkipComments = true);
	Results RemoveBlanks(char** szInput) const; //Modified by AndrewWilkinson88@gmail.com
};
#endif //_EMPTY_H
