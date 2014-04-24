/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef _MAIN_H
#define _MAIN_H

#include <iostream>
#include <utility>
#include "ApplicationClass.h"

#ifndef DEBUG
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

// Application Instance, we dont initialize it with GetInstance() here because the
//constructor need OpenGL calls that has now being initializated jet.
ApplicationClass* App;
void (*Function) (void); // function pointer
void Function0 (void); //Forward declaration of Function0

#endif //_MAIN_H
