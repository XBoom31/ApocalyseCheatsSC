/*
// FILENAME: VMTManager.h
// DESC: Provides functions for managing
	VMT tables, hooking, storing backups,
	and restoring the tables when done,
	all in an anti-cheat safe way.
*/

// - Class for managing a single VTable -//


#define VMTSIGNATURE 35492835

//Includes
#include "stdafx.h"

class VMTManager
{
private:
	DWORD	*OriginalTable;
	DWORD	*CustomTable;
	int		MethodCount(DWORD* InstancePointer);
	bool	initComplete;
	DWORD	*Instance;
public:
	bool	Initialise(DWORD* InstancePointer); // Pass a &class
	
	DWORD	HookMethod(DWORD NewFunction, int Index);
	void	UnhookMethod(int Index);

	static bool IsTableHooked(DWORD* InstancePointer);

	void	RestoreOriginal();
	void	RestoreCustom();

	DWORD	GetOriginalFunction(int Index);
};