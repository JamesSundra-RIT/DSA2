#include "EmptyClass.h"

EmptyClass::EmptyClass(void) { Init(); }
EmptyClass::EmptyClass(const EmptyClass& other) { }
EmptyClass& EmptyClass::operator=(const EmptyClass& other) { return *this; }
EmptyClass::~EmptyClass(void) { Release(); }
	
void EmptyClass::Release(void) { }
void EmptyClass::Init(void) { }

//Accessors
void EmptyClass::SetVariable(int a_nVariable){ m_nVariable = a_nVariable; }
int EmptyClass::GetVariable(void) { return m_nVariable; }