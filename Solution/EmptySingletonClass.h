/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _EMPTYSINGLETONCLASS_H
#define _EMPTYSINGLETONCLASS_H

//#include

class EmptySingletonClass
{
	static EmptySingletonClass* m_pInstance; //Singleton
	EmptySingletonClass(void); //Constructor	
	EmptySingletonClass(const EmptySingletonClass& other); //Copy Constructor
	EmptySingletonClass& operator=(const EmptySingletonClass& other);//Copy Assignment Operator
	void Release(void); //Release the fields in the class
	void Init(void); //Initialize variables

public:
	static EmptySingletonClass* GetInstance(); //Singleton Accessor
	~EmptySingletonClass(void); //Destructor

};
#endif //_EMPTYSINGLETONCLASS_H