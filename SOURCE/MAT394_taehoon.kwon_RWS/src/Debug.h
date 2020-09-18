#pragma once
#include <windows.h>
#include <cstdio>
#include <cstring>

class DebugFunctions
{
public:
	static bool DebugAssert(bool express, const char* outputMsg,
		const char* functionName, const char* fileName, unsigned lineNumber);
	static void DebugCreateConsole(void);
	static void DebugDestroyConsole(void);
};

#if defined(DEBUG) | defined(_DEBUG)
#include <cstdio>
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#define DEBUG_CLEAR() system("cls")
#define DEBUG_ASSERT(exp, str) if(DebugFunctions::DebugAssert((exp),(str),      \
  __FUNCTION__,__FILE__, __LINE__))     \
{DebugBreak();} 
#define DEBUG_CREATE_CONSOLE() DebugFunctions::DebugCreateConsole();
#define DEBUG_DESTROY_CONSOLE() DebugFunctions::DebugDestroyConsole();

#else
#define DEBUG_PRINT(...)
#define DEBUG_CLEAR()
#define DEBUG_ASSERT(expression, outputMessage)
#define DEBUG_CREATE_CONSOLE()
#define DEBUG_DESTROY_CONSOLE()
#endif