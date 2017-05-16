

// Credits to Valve and Shad0w

#include "NetVars.h"
#include "ClientRecvProps.h"
#include "CRC32.h"
#include "Utilities.h"

#include "SDK.h"

using namespace std;

CNetVar NetVar;

const char* AlignText(int align)
{
	static char buffer[256];
	int i = 0;
	for (i = 0; i < align; i++)
	{
		buffer[i] = ' ';
	}
	buffer[i + 1] = 0;
	return buffer;
}

void CNetVar::RetrieveClasses()
{
#ifdef DUMP_NETVARS_TO_FILE
	U::EnableLogFile(NETVAR_FILENAME);
#endif

	ClientClass *clientClass = Interfaces::Client->GetAllClasses();

	if (!clientClass)
		return;

	//Clear netvar vector incase of another call, not necesarry as it doesnt add duplicates

	vars.clear();

	while (clientClass != 0)
	{
		if (clientClass == 0)
			break;

		LogNetVar(clientClass->m_pRecvTable, 0);

		clientClass = clientClass->m_pNext;
	}
}

void CNetVar::LogNetVar(RecvTable *table, int align)
{
	if (table->m_nProps < 0)
		return;

#ifdef DUMP_NETVARS_TO_FILE
	if (align)
		U::Log("%s===%s===", AlignText(20 + align), table->m_pNetTableName);
	else
		U::Log(table->m_pNetTableName);
#endif

	for (auto i = 0; i < table->m_nProps; ++i)
	{
		RecvProp *prop = &table->m_pProps[i];

		if (!prop)
			continue;

		char szCRC32[150];

		sprintf_s(szCRC32, "%s%s", table->m_pNetTableName, prop->m_pVarName);

		DWORD_PTR dwCRC32 = CRC32((void*)szCRC32, strlen(szCRC32));

#ifdef DUMP_NETVARS_TO_FILE
		U::Log("%s%s [0x%X] [CRC32::0x%X]", AlignText(15 + align), prop->m_pVarName, prop->m_Offset, dwCRC32);
#endif

		//Dont add duplicates

		bool bAddNetVar = true;

		for (auto netvar = 0; netvar < (int)vars.size(); ++netvar)
		{
			netvar_info_s *netvars = &vars[netvar];

			if (netvars->dwCRC32 == dwCRC32)
				bAddNetVar = false;

#ifdef DUMP_NETVARS_TO_FILE

			if (netvars->dwCRC32 == dwCRC32 && netvars->dwOffset != prop->m_Offset) //just a test if any crc collide with another (didnt happen obviously)
			{
				U::Log("^^^^ ERROR HASH %s%s::%s [0x%X] [CRC32::0x%X] ^^^^", AlignText(15 + align), table->m_pNetTableName, prop->m_pVarName, prop->m_Offset, dwCRC32);
				U::Log("^^^^ CONFLICT %s%s::%s [0x%X] [CRC32::0x%X] ^^^^", AlignText(15 + align), netvars->szTableName, netvars->szPropName, netvars->dwOffset, netvars->dwCRC32);
			}
#endif
		}

		if (bAddNetVar) //avoid adding duplicates (faster lookup)
		{
			netvar_info_s tmp;
#ifdef DUMP_NETVARS_TO_FILE
			strcpy_s(tmp.szTableName, table->m_pNetTableName);
			strcpy_s(tmp.szPropName, prop->m_pVarName);
#endif
			tmp.dwCRC32 = dwCRC32;

			tmp.dwOffset = prop->m_Offset;

			vars.push_back(tmp);
		}

		if (prop->m_pDataTable)
			LogNetVar(prop->m_pDataTable, 5);
	}
}

DWORD_PTR CNetVar::GetNetVar(DWORD_PTR dwCRC32) //returns 0xFFFFFFFF (-1) if not found (ex: if(GetNetVar(0xD34DB33F)==-1) return false;
{
	for (auto i = 0; i < (int)vars.size(); ++i)
	{
		if (vars[i].dwCRC32 == dwCRC32)
			return vars[i].dwOffset;
	}

	return 0xFFFFFFFF;
}