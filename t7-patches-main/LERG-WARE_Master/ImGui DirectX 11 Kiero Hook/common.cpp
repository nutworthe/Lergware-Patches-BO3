#include "common.h"

std::vector<std::string> vec;

//bool tr;
//bool tp;

//CORE
bool notify = true;
bool friendsonly = false;
int kick_selection;
int kick[] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5 };
int kick_sel = 0;

const char* kicks[] = {
    "DROP",
    "KICK",
    "BADDLC",
    "KICK_PARTY",
    "HOSTRELOAD",
    "NOPARTYCHAT"
};


float flHue;
float rgb_speed = 0.25;

char spoofName[32]{};
char nameBuffer[32]{};

//GAME FUNCTIONS
std::uintptr_t dwProcessBase = reinterpret_cast<std::uintptr_t>(GetModuleHandleA(nullptr));

tGetPersonaName oGetPersonaName;
tLiveSteam_FilterPersonaName oLiveSteam_FilterPersonaName = (tLiveSteam_FilterPersonaName)(dwProcessBase + 0x1EB0350);
DWORD_PTR pGetPersonaNameReturn = dwProcessBase + 0x1EB0E7C;
DWORD_PTR ISteamFriends = *(DWORD_PTR*)(dwProcessBase + 0x10BBEBA0);
DWORD_PTR pUserData = dwProcessBase + 0x14FB5420;
DWORD_PTR pNameBuffer = dwProcessBase + 0x15E86638;

XSESSION_INFO get_session_info(const InfoResponseLobby& lobby)
{
    XSESSION_INFO sess_info{};
    sess_info.sessionID = lobby.secId;
    sess_info.keyExchangeKey = lobby.secKey;
    sess_info.hostAddress = lobby.serializedAdr.xnaddr;

    return sess_info;
}