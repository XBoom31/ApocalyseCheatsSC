
#include "Dumping.h"

#define DUMPIDTOFILE

void Dump::DumpClassIds()
{
#ifdef DUMPIDTOFILE
	Utilities::EnableLogFile("ClassID.txt");
#endif
	ClientClass* cClass = Interfaces::Client->GetAllClasses();
	while (cClass)
	{
		Utilities::Log("%s = %d,", cClass->m_pNetworkName, cClass->m_ClassID);
		cClass = cClass->m_pNext;
	}
}