/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _EMPTYCLASS_H
#define _EMPTYCLASS_H

//#include

class EmptyClass
{
	int m_nVariable; //Example Variable
public:
	EmptyClass(void); //Constructor
	EmptyClass(const EmptyClass& other); //Copy Constructor
	EmptyClass& operator=(const EmptyClass& other); //Copy Assignment Operator
	void Release(void); //Release the fields in the class
	~EmptyClass(void); //Destructor
//Accessors
	void SetVariable(int a_nVariable); //Sets Variable
	int GetVariable(void);//Gets Variable
	__declspec(property(get = GetVariable, put = SetVariable)) int Variable; //Property
private:
	void Init(void); //Initializes the variables
};
#endif //_EMPTY_H
