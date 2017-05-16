
// Credits to Valve and Shad0w

#pragma once

//uncomment me if you wish to dump netvars
//#define DUMP_NETVARS_TO_FILE 

#include "CommonIncludes.h"
#include <memory>

class NetvarDatabase;
struct NetvarTable;

struct netvar_info_s
{
#ifdef DUMP_NETVARS_TO_FILE
	char szTableName[128];
	char szPropName[128];
#endif
	DWORD_PTR dwCRC32;
	DWORD_PTR dwOffset;
};

struct RecvTable;

class CNetVar
{
public:
	void RetrieveClasses();
	void LogNetVar(RecvTable *table, int align);
	DWORD_PTR GetNetVar(DWORD_PTR dwCRC32);
	void HookProxies();
private:
	std::vector<netvar_info_s>vars;
};

class NetvarManager
{
private:
	static NetvarManager* instance;

	NetvarManager();
	~NetvarManager();

	NetvarManager(const NetvarManager&) = delete;

public:
	static NetvarManager* Instance()
	{
		if (!instance) instance = new NetvarManager;
		return instance;
	}

	void CreateDatabase();
	void DestroyDatabase();

	void Dump(std::ostream& stream);
	void Dump(const std::string& file);

	int GetNetvarCount() { return m_netvarCount; }
	int GetTableCount() { return m_tableCount; }

	template<typename ...Args>
	uint32_t GetOffset(const std::string& szTableName, Args&&... args)
	{
		return GetOffset(szTableName, { std::forward<Args>(args)... });
	}
private:
	std::unique_ptr<NetvarTable>  InternalLoadTable(RecvTable* pRecvTable, uint32_t offset);
	void                          Dump(std::ostream& output, NetvarTable& table, int level);
	uint32_t                      GetOffset(const std::string& szTableName, const std::initializer_list<std::string>& props);

private:
	std::unique_ptr<NetvarDatabase>    m_pDatabase = nullptr;
	uint32_t                           m_tableCount = 0;
	uint32_t                           m_netvarCount = 0;
};

#ifdef DUMP_NETVARS_TO_FILE
#define NETVAR_FILENAME "netvars.txt"
#endif

extern CNetVar NetVar;

#define GET_NETVAR(table, ...) NetvarManager::Instance()->GetOffset(table, __VA_ARGS__)