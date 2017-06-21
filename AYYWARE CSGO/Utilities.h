/*
Syn's Apocalypse Framework
*/

#pragma once

// Includes
#include "CommonIncludes.h"
#include <time.h>
#include "Xor.h"

// Colors for the console
//Define extra colours
#define FOREGROUND_WHITE		    (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_YELLOW       	(FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_CYAN		        (FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_MAGENTA	        (FOREGROUND_RED | FOREGROUND_BLUE)
#define FOREGROUND_BLACK		    0

#define FOREGROUND_INTENSE_RED		(FOREGROUND_RED | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_GREEN	(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_BLUE		(FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_WHITE	(FOREGROUND_WHITE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_YELLOW	(FOREGROUND_YELLOW | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_CYAN		(FOREGROUND_CYAN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_MAGENTA	(FOREGROUND_MAGENTA | FOREGROUND_INTENSITY)
#define MakePtr (cast, ptr, addValue) ( cast )( (DWORD)( ptr ) + ( DWORD )( addValue ) )

// Utilities Namespace
// Purpose: Contains misc functionality for memory related functionality
namespace Utilities
{
	typedef void* (*CreateInterface_t)(const char*, int*);
	// Debug console controls
	void OpenConsole(std::string Title);
	void CloseConsole();
	void Log(const char *fmt, ...);

	void EnableLogFile(std::string filename);

	void SetConsoleColor(WORD color);  

	// Misc Shizz
	std::string GetTimeString();
	
	// Memory utils
	// Purpose: Provides memeory related functionality (pattern scanning ect)
	namespace Memory
	{
		inline void* CaptureInterface(const char* chHandle, const char* chInterfaceName)
		{
			volatile auto handlegotten = (GetModuleHandleA(chHandle) != nullptr);
			while (!GetModuleHandleA(chHandle)) Sleep(100);
			void* fnFinal = nullptr;
			auto PossibleInterfaceName = new char[strlen(chInterfaceName) + 4];
			auto TestInterface = reinterpret_cast<CreateInterface_t>(GetProcAddress(GetModuleHandleA(chHandle), XorStr("CreateInterface")));
			for (auto i = 100; i > 0; i--)
			{
				XorCompileTime::w_sprintf(PossibleInterfaceName, XorStr("%s%03i"), chInterfaceName, i);
				fnFinal = static_cast<void*>(TestInterface(PossibleInterfaceName, nullptr));

				if (fnFinal != nullptr)
					break;

			}
			delete PossibleInterfaceName;
			return fnFinal;
		}

		// Waits for a module to be available, before returning it's base address
		DWORD WaitOnModuleHandle(std::string moduleName);

		// Attempts to locate the given signature and mask in a memory range
		// Returns the address at which it has been found
		DWORD FindPattern(std::string moduleName, BYTE* Mask, char* szMask);

		// Attempts to locate the given text in a memory range
		// Returns the address at which it has been found
		DWORD FindTextPattern(std::string moduleName, char* string);

		class VMTManager
		{
		private:
			DWORD	*CustomTable;
			bool	initComplete;
			DWORD	*OriginalTable;
			DWORD	*Instance;

			int		MethodCount(DWORD* InstancePointer);
			
		public:
			bool	Initialise(DWORD* InstancePointer); // Pass a &class

			DWORD	HookMethod(DWORD NewFunction, int Index);
			void	UnhookMethod(int Index);

			void	RestoreOriginal();
			void	RestoreCustom();

			template<typename T>
			T GetMethod(size_t nIndex)
			{
				return (T)OriginalTable[nIndex];
			}

			DWORD	GetOriginalFunction(int Index);
		};
	};
};

template<typename T>
FORCEINLINE T GetMethod(const void* instance, size_t index)
{
	uintptr_t* vmt = *(uintptr_t**)instance;

	return (T)vmt[index];
}
