#include "Debug.h"

#define MAX_MESSAGE 1024 /* The max Assert message size */
#define MAX_LINE 10 /* The Max line number size */

bool DebugFunctions::DebugAssert(bool express, const char* outputMsg,
	const char* functionName, const char* fileName, unsigned lineNumber)
{
	if (!express)
	{
		int returnValue;
		char message[MAX_MESSAGE] = { 0 }; /* The message to print */
		char lineString[MAX_LINE] = { 0 }; /* To convert the line to a string */

		/* Convert the line number to a string */
		sprintf_s(lineString, MAX_LINE, "%d", lineNumber);

		/* Set output message */
		strcat_s(message, MAX_MESSAGE, "ASSERTION FAILURE:");
		strcat_s(message, MAX_MESSAGE, "\nFile: ");
		strcat_s(message, MAX_MESSAGE, fileName);
		strcat_s(message, MAX_MESSAGE, "\nLine: ");
		strcat_s(message, MAX_MESSAGE, lineString);
		strcat_s(message, MAX_MESSAGE, "\nFunction: ");
		strcat_s(message, MAX_MESSAGE, functionName);
		strcat_s(message, MAX_MESSAGE, "\n\n Description: ");
		strcat_s(message, MAX_MESSAGE, outputMsg);

		/* display a message to the user */
		returnValue = MessageBox(NULL, message, "ASSERT!", MB_TASKMODAL | MB_SETFOREGROUND | MB_YESNO | MB_ICONERROR);

		if (returnValue == IDYES)
		{
			return true;
		}
		ExitProcess((unsigned)(-1));
	}
	return false;
}

void DebugFunctions::DebugCreateConsole(void)
{
	FILE* pFile;
	AllocConsole();

	freopen_s(&pFile, "CONOUT$", "wt", stdout);
	freopen_s(&pFile, "CONOUT$", "wt", stderr);
	SetConsoleTitle(TEXT("Debug Console"));
}

void DebugFunctions::DebugDestroyConsole(void)
{
	FreeConsole();
}