#include "FileReaderClass.h"

FileReaderClass::FileReaderClass(void) { Init(); }
FileReaderClass::FileReaderClass(const FileReaderClass& other) { }
FileReaderClass& FileReaderClass::operator=(const FileReaderClass& other) { return *this; }
FileReaderClass::~FileReaderClass(void) { Release(); }
	
void FileReaderClass::Release(void) { }
void FileReaderClass::Init(void)
{
	m_pFile = nullptr;
	m_pSystem = SystemClass::GetInstance();
}

Results FileReaderClass::ReadFile(String a_sFileName)
{
	if(m_pFile != nullptr)
		CloseFile();

	fopen_s(&m_pFile, a_sFileName.c_str(), "r");
	
	if(m_pFile == nullptr)
		return ERROR_FILE_MISSING;

	return ERROR_FREE;
}

void FileReaderClass::CloseFile(void)
{
	if(m_pFile != nullptr)
		fclose(m_pFile);
}

void FileReaderClass::Rewind(void) const
{
	if(m_pFile != nullptr)
		rewind(m_pFile);
}

Results FileReaderClass::ReadNextLine(bool bSkipComments)
{
	if(!m_pFile)
		return ERROR_FILE_MISSING;

	int nSpacer = 1;
	int nBufferSize = 255;
	int nNewBufferSize = nBufferSize * nSpacer;
	char* zsLine = new char[nBufferSize * nSpacer];
	//we check memory assignment
	if(!zsLine)
	{
		zsLine = NULL;
		//If we were not able to reserve memory we return false;
		return ERROR_MEMORY;
	}
	char c = fgetc(m_pFile);
	if(c == EOF)
	{
		return DONE;
	}
	zsLine[0] = c;
	int nPointer = 1;
	while(c != 10)
	{
		if(nPointer >= (nNewBufferSize -1))
		{
			zsLine[nPointer] = 0;
			nSpacer++;
			nNewBufferSize = nBufferSize * nSpacer;
			char* zsTemp = new char[nNewBufferSize];
			//We check that we could reserve new memory
			if(zsTemp == 0)
			{
				//if we coulnt then we delete the previous array
				delete[] zsLine;
				//and return false;
				return ERROR_MEMORY;
			}

			//We cleanup the new string
			strcpy_s(zsTemp, nNewBufferSize, zsLine);
			//We delete the previous string
			delete[] zsLine;
			//Copy Backedup data
			zsLine = zsTemp;
		}
		c = fgetc(m_pFile);
		if(c == EOF)
		{
			nPointer++;
			break;
		}
		if(c == 9)
			c = 32;
		zsLine[nPointer] = c;
		nPointer++;
	}
	nPointer--;
	zsLine[nPointer] = 0;
	
	if(RemoveBlanks(&zsLine) != DONE)
	{
		if(zsLine != 0)
			delete[] zsLine;
		return ERROR_MEMORY;
	}

	m_sLine = zsLine;

	if(zsLine)
		delete[] zsLine;

	if(bSkipComments)
	{
		if(m_sLine[0] == '#')
		{
			if(ReadNextLine(bSkipComments) == DONE)
				return DONE;
		}
		if(m_sLine[0] == '/')
		{
			if(m_sLine[1] == '/')
			{
				if(ReadNextLine(bSkipComments) == DONE)
					return DONE;
			}
		}
		if(m_sLine[0] == 0)
		{
			if(ReadNextLine(bSkipComments) == DONE)
				return DONE;
		}
	}

	return RUNNING;
};
Results FileReaderClass::RemoveBlanks(char** zsInput) const
{
	int nLength = static_cast<int>(strlen(*zsInput)) + 1;

	if( nLength == 0)
		return ERROR_MEMORY;

	int character = 0; //Counts how many characters or tabs there are before each line	
	
	while ((*zsInput)[character] == 9)
		character ++;

	while ((*zsInput)[character] == 32)
		character ++;
	
	if(character > 0)	//If there is more than one character
	{
		nLength -= character;
		char *zsTemp = new char[nLength];	//we create a new temp line
		if(zsTemp == 0)
			return ERROR_MEMORY;

		//Backup the original values
		for(int n = 0; n < nLength; n++)
		{
			zsTemp[n] = (*zsInput)[character + n];
		}
		zsTemp[nLength - 1] = '\0';
		
		//Clean up and initialize original
		delete[] (*zsInput);
		(*zsInput) = new char[nLength];
		//realloc( zsInput, sizeof(char) * nLength );
		
		if((*zsInput) == 0)
		{
			delete[] zsTemp;
			return ERROR_MEMORY;
		}

		//Restor the original values
		for(int n = 0; n < nLength; n++)
		{
			(*zsInput)[n] = zsTemp[n];
		}
		delete[] zsTemp;
	}

	return DONE;
};