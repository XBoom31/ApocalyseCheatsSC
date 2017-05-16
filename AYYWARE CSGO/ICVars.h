#pragma once
#include "stdafx.h"
#define FORCEINLINE_CVAR
#pragma region CVAR Flags
#define FCVAR_NONE                      0 
#define FCVAR_UNREGISTERED              (1<<0)    // If this is set, don't add to linked list, etc.
#define FCVAR_DEVELOPMENTONLY           (1<<1)    // Hidden in released products. Flag is removed automatically if ALLOW_DEVELOPMENT_CVARS is defined.
#define FCVAR_GAMEDLL                   (1<<2)    // defined by the game DLL
#define FCVAR_CLIENTDLL                 (1<<3)  // defined by the client DLL
#define FCVAR_HIDDEN                    (1<<4)    // Hidden. Doesn't appear in find or autocomplete. Like DEVELOPMENTONLY, but can't be compiled out.

// ConVar only
#define FCVAR_PROTECTED                 (1<<5)  // It's a server cvar, but we don't send the data since it's a password, etc.  Sends 1 if it's not bland/zero, 0 otherwise as value
#define FCVAR_SPONLY                    (1<<6)  // This cvar cannot be changed by clients connected to a multiplayer server.
#define   FCVAR_ARCHIVE                 (1<<7)    // set to cause it to be saved to vars.rc
#define   FCVAR_NOTIFY                  (1<<8)    // notifies players when changed
#define   FCVAR_USERINFO                (1<<9)    // changes the client's info string
#define FCVAR_CHEAT                     (1<<14) // Only useable in singleplayer / debug / multiplayer & sv_cheats

#define FCVAR_PRINTABLEONLY             (1<<10)  // This cvar's string cannot contain unprintable characters ( e.g., used for player name etc ).
#define FCVAR_UNLOGGED                  (1<<11)  // If this is a FCVAR_SERVER, don't log changes to the log file / console if we are creating a log
#define FCVAR_NEVER_AS_STRING           (1<<12)  // never try to print that cvar

// It's a ConVar that's shared between the client and the server.
// At signon, the values of all such ConVars are sent from the server to the client (skipped for local
//  client, of course )
// If a change is requested it must come from the console (i.e., no remote client changes)
// If a value is changed while a server is active, it's replicated to all connected clients
#define FCVAR_REPLICATED                (1<<13)   // server setting enforced on clients, TODO rename to FCAR_SERVER at some time
#define FCVAR_DEMO                      (1<<16)  // record this cvar when starting a demo file
#define FCVAR_DONTRECORD                (1<<17)  // don't record these command in demofiles

#define FCVAR_NOT_CONNECTED             (1<<22)   // cvar cannot be changed by a client that is connected to a server

#define FCVAR_ARCHIVE_XBOX              (1<<24) // cvar written to config.cfg on the Xbox

#define FCVAR_SERVER_CAN_EXECUTE        (1<<28)// the server is allowed to execute this command on clients via ClientCommand/NET_StringCmd/CBaseClientState::ProcessStringCmd.
#define FCVAR_SERVER_CANNOT_QUERY       (1<<29)// If this is set, then the server is not allowed to query this cvar's value (via IServerPluginHelpers::StartQueryCvarValue).
#define FCVAR_CLIENTCMD_CAN_EXECUTE     (1<<30)   // IVEngineClient::ClientCmd is allowed to execute this command. 
#pragma endregion


enum EConVar
{
	ConVar_GetName = 5,
	ConVar_GetBaseName = 6,
	ConVar_SetString = 14,
	ConVar_SetFloat,
	ConVar_SetInt
};

enum EICVar
{
	ICVar_FindVar = 15
};


class ConVar
{
public:

	const char* GetName();
	const char* GetBaseName();
	void SetValue(const char* value);
	void SetValue(float value);
	void SetValue(int value);

	char pad_0x0000[0x4];
	ConVar * pNext;
	int32 bRegistered;
	char* pszName;
	char* pszHelpString;
	int32 nFlags;
	char pad_0x0018[0x4];
	ConVar* pParent;
	char* pszDefaultValue;
	char* strString;
	int32 StringLength;
	float fValue;
	int32 nValue;
	int32 bHasMin;
	float fMinVal;
	int32 bHasMax;
	float fMaxVal;
	void *fnChangeCallback;
	float GetFloat(void) const
	{
		auto temp = *(int*)(&fValue);
		auto temp_result = (int)(temp ^ (DWORD)this);

		return *(float*)(&temp_result);
	}

};//Size=0x0048

  /*
  ///--------------------------------------------------------------------
  /// Methods from IAppSystem
  ///--------------------------------------------------------------------
  virtual bool                       Connect( CreateInterfaceFn factory ) = 0;                                              // 0
  virtual void                       Disconnect() = 0;                                                                      // 1
  virtual void*                      QueryInterface( const char *pInterfaceName ) = 0;                                      // 2
  virtual int                        Init() = 0;                                                                            // 3
  virtual void                       Shutdown() = 0;                                                                        // 4
  virtual const void*                GetDependencies() = 0;                                                                 // 5
  virtual int                        GetTier() = 0;                                                                         // 6
  virtual void                       Reconnect( CreateInterfaceFn factory, const char *pInterfaceName ) = 0;                // 7
  virtual void                       UnkFunc() = 0;                                                                         // 8
  ///--------------------------------------------------------------------
  virtual CVarDLLIdentifier_t        AllocateDLLIdentifier() = 0;                                                           // 9
  virtual void                       RegisterConCommand(ConCommandBase *pCommandBase) = 0;                                  // 10
  virtual void                       UnregisterConCommand(ConCommandBase *pCommandBase) = 0;                                // 11
  virtual void                       UnregisterConCommands(CVarDLLIdentifier_t id) = 0;                                     // 12
  virtual const char*                GetCommandLineValue(const char *pVariableName) = 0;                                    // 13
  virtual ConCommandBase*            FindCommandBase(const char *name) = 0;                                                 // 14
  virtual const ConCommandBase*      FindCommandBase(const char *name) const = 0;                                           // 15
  virtual ConVar*                    FindVar(const char *var_name) = 0;                                                     // 16
  virtual const ConVar*              FindVar(const char *var_name) const = 0;                                               // 17
  virtual ConCommand*                FindCommand(const char *name) = 0;                                                     // 18
  virtual const ConCommand*          FindCommand(const char *name) const = 0;                                               // 19
  virtual void                       InstallGlobalChangeCallback(FnChangeCallback_t callback) = 0;                          // 20
  virtual void                       RemoveGlobalChangeCallback(FnChangeCallback_t callback) = 0;                           // 21
  virtual void                       CallGlobalChangeCallbacks(ConVar *var, const char *pOldString, float flOldValue) = 0;  // 22
  virtual void                       InstallConsoleDisplayFunc(IConsoleDisplayFunc* pDisplayFunc) = 0;                      // 23
  virtual void                       RemoveConsoleDisplayFunc(IConsoleDisplayFunc* pDisplayFunc) = 0;                       // 24
  virtual void                       ConsoleColorPrintf(const Color& clr, const char *pFormat, ...) const = 0;              // 25
  virtual void                       ConsolePrintf(const char *pFormat, ...) const = 0;                                     // 26
  virtual void                       ConsoleDPrintf(const char *pFormat, ...) const = 0;                                    // 27
  virtual void                       RevertFlaggedConVars(int nFlag) = 0;                                                   // 28
  */


class ICVar
{
public:
	ConVar* FindVar(const char *var_name)
	{
		typedef ConVar*(__thiscall* FindVarFn)(void*, const char *);
		return getvfunc<FindVarFn>(this, 15)(this, var_name);
	}
};