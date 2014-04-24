#include "EmptySingletonClass.h"
EmptySingletonClass* EmptySingletonClass::m_pInstance = nullptr;
EmptySingletonClass* EmptySingletonClass::GetInstance(void)
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new EmptySingletonClass();
	}
	return m_pInstance;
}
EmptySingletonClass::EmptySingletonClass(void) { Init(); }
EmptySingletonClass::EmptySingletonClass(const EmptySingletonClass& other) { }
EmptySingletonClass& EmptySingletonClass::operator=(const EmptySingletonClass& other) { return *this; }
EmptySingletonClass::~EmptySingletonClass(void) { Release(); }
//--- Non Standard Singleton Methods
void EmptySingletonClass::Release(void) { }
void EmptySingletonClass::Init(void) { }