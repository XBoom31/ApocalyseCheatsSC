#pragma once
#include "stdafx.h"

#define INRANGE(x, a, b)	(x >= a && x <= b) 
#define GETBITS(x)			(INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GETBYTE(x)			(GETBITS(x[0]) << 4 | GETBITS(x[1]))

class CUtils
{
public:
	DWORD PFindPattern(std::string moduleName, std::string pattern) {
		const char* pat = pattern.c_str();
		DWORD firstMatch = 0;
		DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
		MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
		DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
		for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++) {
			if (!*pat)
				return firstMatch;
			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == GETBYTE(pat)) {
				if (!firstMatch)
					firstMatch = pCur;
				if (!pat[2])
					return firstMatch;
				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;
				else
					pat += 2;
			}
			else {
				pat = pattern.c_str();
				firstMatch = 0;
			}
		}
		return NULL;
	}


	ULONG PatternSearch(std::string sModuleName, PBYTE pbPattern, std::string sMask, ULONG uCodeBase, ULONG uSizeOfCode)
	{
		BOOL bPatternDidMatch = FALSE;
		HMODULE hModule = GetModuleHandle(sModuleName.c_str());

		if (!hModule)
			return 0x0;

		PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER(hModule);
		PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS(LONG(hModule) + pDsHeader->e_lfanew);
		PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pPeHeader->OptionalHeader;

		if (uCodeBase == 0x0)
			uCodeBase = (ULONG)hModule + pOptionalHeader->BaseOfCode;

		if (uSizeOfCode == 0x0)
			uSizeOfCode = pOptionalHeader->SizeOfCode;

		ULONG uArraySize = sMask.length();

		if (!uCodeBase || !uSizeOfCode || !uArraySize)
			return 0x0;

		for (size_t i = uCodeBase; i <= uCodeBase + uSizeOfCode; i++)
		{
			for (size_t t = 0; t < uArraySize; t++)
			{
				if (*((PBYTE)i + t) == pbPattern[t] || sMask.c_str()[t] == '?')
					bPatternDidMatch = TRUE;

				else
				{
					bPatternDidMatch = FALSE;
					break;
				}
			}

			if (bPatternDidMatch)
				return i;
		}

		return 0x0;
	}

	HMODULE GetModuleHandleSafe(const char* pszModuleName)
	{
		HMODULE hmModuleHandle = NULL;

		do
		{
			hmModuleHandle = GetModuleHandle(pszModuleName);
			Sleep(1);
		} while (hmModuleHandle == NULL);

		return hmModuleHandle;
	}
};

extern CUtils Utils;