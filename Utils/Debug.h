#pragma once

// DEBUG_PRINT
#ifdef _DEBUG
#include <iostream>
#define DEBUG_PRINT(x) std::cout << x << std::endl
#else
#define DEBUG_PRINT(x)
#endif

/*
// DEBUG_CODE
#ifdef _DEBUG
#include <iostream>
#define DEBUG_CODE(x) std::cout << "******** DEBUG CODE ********" << std::endl << "File: " << __FILE__ << std::endl << "Line: " << __LINE__ << std::endl << "Message: " << x << std::endl << "****************************" << std::endl
#else
#define DEBUG_CODE(x)
#endif
*/
