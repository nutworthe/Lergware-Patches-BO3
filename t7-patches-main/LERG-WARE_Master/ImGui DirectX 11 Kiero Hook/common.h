#pragma once
#include "includes.h"

extern std::vector<std::string> vec;

//extern bool tr;
//extern bool tp;

//CORE
extern bool notify;
extern bool friendsonly;
extern float flHue;
extern float rgb_speed;

extern int kick_selection;
extern int kick[6];
extern int kick_sel;

extern const char* kicks[6];

extern char spoofName[32];
extern char nameBuffer[32];

//GAME FUNCTIONS
extern std::uintptr_t dwProcessBase;

using ControllerIndex_t = std::uint32_t;
using ClientNum_t = std::uint32_t;

//HOOKED FUNCTIONS
const static auto LobbyVM_OnDisconnect = reinterpret_cast<__int64(__fastcall*)(LobbySession * lobbySession, __int64 xuid, __int32 disconnectClient)>(dwProcessBase + 0x1EEFF10);
const static auto dwInstantDispatchMessage = reinterpret_cast<__int64(__fastcall*)(int64 SenderId, unsigned int controllerIndex, __int64 msg, unsigned int messageSize)>(dwProcessBase + 0x143A600);
const static auto CL_ConnectionlessCMD = reinterpret_cast<char(__fastcall*)(LocalClientNum_t localClientNum, netadr_t from, msg_t * msg)>(dwProcessBase + 0x134CDAD);

//ESSENTIAL FUNCTIONS
const static auto dwRegisterSecIDAndKey = reinterpret_cast<bool(*)(const bdSecurityID*, const bdSecurityKey*)>(dwProcessBase + 0x143E120);
const static auto dwCommonAddrToNetadr = reinterpret_cast<bool(*)(netadr_t* const, const void* const, const bdSecurityID*)>(dwProcessBase + 0x143C360);
const static auto CL_GetConfigString = reinterpret_cast<const char* (*)(int configStringIndex)>(dwProcessBase + 0x1321110);
const static auto CL_StoreConfigString = reinterpret_cast<const char* (*)(int configStringIndex, const char* string)>(dwProcessBase + 0x13667C0);
const static auto Com_IsInGame = reinterpret_cast<bool(*)()>(dwProcessBase + 0x2148D20);
const static auto Live_IsUserInGame = reinterpret_cast<bool(*)(const ControllerIndex_t controllerIndex)>(dwProcessBase + 0x1E0D7E0);
const static auto LiveFriends_IsFriendByXUID = reinterpret_cast<bool(__fastcall*)(int controllerIndex, int64_t XUID)>(dwProcessBase + 0x1DF9430);
const static auto Dvar_SetFromString = reinterpret_cast<std::uintptr_t(__fastcall*)(const char* dvarname, const char* value, bool createifmissing)>(dwProcessBase + 0x22C7F60);
const static auto Cmd_ExecuteSingleCommand = reinterpret_cast<std::uintptr_t(__fastcall*)(int, int, const char* text, bool)>(dwProcessBase + 0x20EDC20);
const static auto LiveStats_SetClanTagText = reinterpret_cast<std::uintptr_t(__fastcall*)(int, const char*)>(dwProcessBase + 0x1EA5510);
const static auto CL_AddReliableCommand = reinterpret_cast<std::uintptr_t(__fastcall*)(int, const char*)>(dwProcessBase + 0x135D4C0);
const static auto Cbuf_AddText = reinterpret_cast<std::uintptr_t(__fastcall*)(int, const char*)>(dwProcessBase + 0x20EC8B0);
const static auto LobbyVM_JoinEvent = reinterpret_cast<std::uintptr_t(__fastcall*)(int controllerIndex, uint64_t xuid, int joinType)>(dwProcessBase + 0x1EEF8E0);

const static auto Live_IsUserSignedInToDemonware = reinterpret_cast<bool(*)(const ControllerIndex_t)>(dwProcessBase + 0x1E0D830);
const static auto CL_IsLocalClientInGame = reinterpret_cast<std::uintptr_t(__fastcall*)(int localClientNum)>(dwProcessBase + 0x13598E0);
const static auto MSG_InitReadOnly = reinterpret_cast<void(*)(msg_t*, const char*, int)>(dwProcessBase + 0x2155A70);
const static auto MSG_BeginReading = reinterpret_cast<void(*)(msg_t*)>(dwProcessBase + 0x2155760);
const static auto MSG_ReadByte = reinterpret_cast<std::uint8_t(*)(msg_t*)>(dwProcessBase + 0x2155EB0);
const static auto MSG_ReadData = reinterpret_cast<void(*)(msg_t*, void*, int)>(dwProcessBase + 0x2155F10);
const static auto MSG_InfoResponse = reinterpret_cast<bool(*)(void*, LobbyMsg*)>(dwProcessBase + 0x1EE1EB0);
const static auto LobbyMsg_HandleIM = reinterpret_cast<std::uintptr_t(__fastcall*)(unsigned int targetController, __int64 senderXuid, void* buff, int len)>(dwProcessBase + 0x1EF6430);
const static auto Sys_Milliseconds = reinterpret_cast<std::uint64_t(*)()>(dwProcessBase + 0x2333430);
const static auto dwNetadrToCommonAddr = reinterpret_cast<bool(*)(netadr_t, void*, const unsigned int, bdSecurityID*)>(dwProcessBase + 0x143DA60);
const static auto LobbyMsgRW_PrepReadMsg = reinterpret_cast<bool(*)(LobbyMsg*, msg_t*)>(dwProcessBase + 0x1EF6A40);
const static auto LobbyMsg_SendInfoRequest = reinterpret_cast<bool(__fastcall*)(const ControllerIndex_t, const std::uint64_t*, int, const Msg_InfoRequest*)>(dwProcessBase + 0x1EE54C0);
const static auto LobbyMsgRW_PrepReadData = reinterpret_cast<bool(__fastcall*)(LobbyMsg*, char*, int)>(dwProcessBase + 0x1EF6A10);


typedef char* (__fastcall* tGetPersonaName) (DWORD_PTR _this);
typedef __int64(__fastcall* tLiveSteam_FilterPersonaName)(char* buffer, int size, char asciionly);

extern tGetPersonaName oGetPersonaName;
extern tLiveSteam_FilterPersonaName oLiveSteam_FilterPersonaName;
extern DWORD_PTR pGetPersonaNameReturn;
extern DWORD_PTR ISteamFriends;
extern DWORD_PTR pUserData;
extern DWORD_PTR pNameBuffer;

// Utils
#define Hook(original, hook) (DetourTransactionBegin(), DetourUpdateThread(GetCurrentThread()), DetourAttach((LPVOID*)&original, (LPVOID)hook), DetourTransactionCommit())
#define Unhook(original, hook) (DetourTransactionBegin(), DetourUpdateThread(GetCurrentThread()), DetourDetach((LPVOID*)&original, (LPVOID)hook), DetourTransactionCommit())

inline DWORD_PTR HookVMT(DWORD_PTR pVtable, DWORD_PTR hook, int index)
{
    DWORD_PTR* vtable = *(DWORD_PTR**)pVtable;
    DWORD_PTR backup = 0;
    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery((LPCVOID)vtable, &mbi, sizeof(mbi));
    VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect);
    backup = vtable[index];
    vtable[index] = (DWORD_PTR)hook;
    VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);
    return backup;
}

inline void RenamePreGame(std::string name)
{
    if (name.size() > 31)
        name.resize(31);

    strncpy_s((char*)(pUserData + 0x8), 32, name.c_str(), name.size());
    strncpy_s((char*)(pNameBuffer), 32, name.c_str(), name.size());
}

XSESSION_INFO get_session_info(const InfoResponseLobby& lobby);