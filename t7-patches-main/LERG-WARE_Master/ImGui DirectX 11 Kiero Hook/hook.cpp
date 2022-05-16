#include "includes.h"

Hooks hooks;
#define M_PI 3.14159265358979323846264338327950288

std::vector<std::string> legit_packets = { "connectResponse", "statresponse", "LM", "disconnect", "loadoutResponse", "infoResponse", "statusResponse", "keyAuthorize", "error", "print", "echo", "fastrestart", "ping", "pinga", "steamAuthReq", "cfl", "Nigger", "faggot", "N1gger", "F4ggot", "fagg0t", "f4gg0t", "n1gg3r", "nigg3r", "bitch", "b1tch", "fuck", "rape", "r4pe", "cock", "c0ck"};

std::string va(const char* fmt, ...)
{
	char result[2048] = { 0 };

	va_list ap;
	va_start(ap, fmt);

	vsnprintf_s(result, sizeof(result), _TRUNCATE, fmt, ap);

	va_end(ap);
	return result;
}

std::string adr_to_string(const netadr_t* address)
{
	XNADDR xn;

	dwNetadrToCommonAddr(*address, &xn, sizeof xn, nullptr);

	return va("%u.%u.%u.%u", xn.ip[0], xn.ip[1], xn.ip[2], xn.ip[3]);
}

__int64 hLiveSteam_FilterPersonaName(char* buffer, int size, char asciionly)
{
	Unhook(oLiveSteam_FilterPersonaName, hLiveSteam_FilterPersonaName);
	return 0;
}

char* hGetPersonaName(DWORD_PTR _this)
{
	if (spoofName[0] != 0)
	{
		if ((DWORD_PTR)_ReturnAddress() == pGetPersonaNameReturn)
		{
			Hook(oLiveSteam_FilterPersonaName, hLiveSteam_FilterPersonaName);
		}

		return spoofName;
	}

	return oGetPersonaName(_this);
}

const std::string GetTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	#pragma warning(suppress : 4996).
	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), "%X", &tstruct);

	return buf;
}

static bool is_user_in_game()
{
	return Live_IsUserInGame(0);
}

static bool local_client_is_in_game()
{
	return CL_IsLocalClientInGame(0);
}

static bool is_in_game()
{
	return Com_IsInGame();
}

static bool is_match_loaded()
{
	return (is_user_in_game() && local_client_is_in_game() && is_in_game());
}

std::string to_lower(std::string text)
{
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
	return text;
}

bool is_equal(const std::string& lhs, const std::string& rhs, const std::size_t count, const bool case_sensitive)
{
	auto left = lhs;
	auto right = rhs;

	if (count != std::string::npos)
	{
		if (lhs.size() > count)
			left.erase(count);

		if (rhs.size() > count)
			right.erase(count);
	}

	if (case_sensitive)
	{
		return left == right;
	}

	else
	{
		return to_lower(left) == to_lower(right);
	}
}

bool is_in_array(std::string cmp1, std::vector<std::string> cmp2)
{
	for (auto cmp : cmp2)
	{
		if (!strcmp(cmp1.data(), cmp.data()))
			return true;
	}
	return false;
}

const char* __fastcall hkCL_GetConfigString(std::int32_t configStringIndex)
{
	constexpr auto mspreload_command = "mspreload";

	if (configStringIndex == 3627)
	{
		if (auto config_string{ CL_GetConfigString(configStringIndex) }; is_equal(config_string, mspreload_command, std::strlen(mspreload_command), false))
		{
			CL_StoreConfigString(configStringIndex, "");

			ImGui::InsertNotification({ ImGuiToastType_Warning, 8000, "Loadside Attempt Blocked" });
		}
	}

	return CL_GetConfigString(configStringIndex);
}

__int64 hkdwInstantDispatchMessage(__int64 sender_id, unsigned int controllerIndex, __int64 msg, unsigned int messageSize)
{
	const auto message{ reinterpret_cast<const char*>(msg) };
	const auto message_size{ messageSize };

	instant_message::dispatch::handle_message(sender_id, message, message_size);

	std::srand(time(NULL));
	*(__int32*)((INT64)GetModuleHandleA(NULL) + 0x112F1A14) = rand();

	return 0;
}

LONG CALLBACK hkCL_ConnectionlessCMD(LPEXCEPTION_POINTERS ex)
{

	time_t now = time(0);
	#pragma warning(suppress : 4996)
	char* dt = ctime(&now);

	const char* message = (char*)ex->ContextRecord->Rdi;
	std::string sender = adr_to_string((netadr_t*)ex->ContextRecord->R15);

	if (is_in_array(message, legit_packets))
	{
		ex->ContextRecord->Rip += 3;
		ex->ContextRecord->Rdx = ex->ContextRecord->R12;
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	std::string str = std::string(message) + " Received from " + sender;

	if (notify)
	{
		ImGui::InsertNotification({ ImGuiToastType_OOB, 8000, str.data() });
	}
	

	std::ofstream myfile;
	myfile.open("lergware\\logs\\logs.txt""", std::ios_base::app);
	myfile << dt << message << " Received from " << sender << "\n";
	myfile.close();

	ex->ContextRecord->Rip = (dwProcessBase + 0x134CE00);

	return EXCEPTION_CONTINUE_EXECUTION;

}

void hkLobbyVM_OnDisconnect(LobbySession* session, __int64 XUID, LobbyDisconnectClient client)
{

	time_t now = time(0);
	#pragma warning(suppress : 4996)
	char* dt = ctime(&now);

	std::string kick = std::to_string(client);
	std::string sender = std::to_string(XUID);

	kick = kicks[client];

	if (notify)
	{
		ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "%s Attempt", kick});
	}

	std::ofstream myfile;
	myfile.open("lergware\\logs\\logs.txt""", std::ios_base::app);
	myfile << dt << kick << " Received From " << sender << "\n";
	myfile.close();

	return;
}

void Hooks::Initialize()
{
	oGetPersonaName = (tGetPersonaName)HookVMT(ISteamFriends, (DWORD_PTR)&hGetPersonaName, 0);
}

void main::hook::initializeHook() {

	Hooks hook;

	hook.Initialize();

	void handle_hooks();

	THREADENTRY32 te32;
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

	if (hThreadSnap)
	{
		te32.dwSize = sizeof(THREADENTRY32);

		if (!Thread32First(hThreadSnap, &te32))
		{
			CloseHandle(hThreadSnap);
		}
		else {
			do
			{
				if (te32.th32OwnerProcessID == GetCurrentProcessId() && te32.th32ThreadID != GetCurrentThreadId())
				{
					HANDLE hThread = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, 0, te32.th32ThreadID);
					if (hThread)
					{
						CONTEXT context;
						context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
						SuspendThread(hThread);

						if (GetThreadContext(hThread, &context))
						{
							context.Dr0 = (uintptr_t)dwInstantDispatchMessage;
							context.Dr1 = (uintptr_t)CL_ConnectionlessCMD;
							context.Dr2 = (uintptr_t)LobbyVM_OnDisconnect;
							context.Dr3 = (uintptr_t)0;
							context.Dr7 = (1 << 0) | (1 << 2) | (1 << 4) | (1 << 6);

							SetThreadContext(hThread, &context);
						}

						ResumeThread(hThread);
						CloseHandle(hThread);
					}
				}
			} while (Thread32Next(hThreadSnap, &te32));
			CloseHandle(hThreadSnap);
		}
	}
	SetUnhandledExceptionFilter(main::hook::hookHandler);
}

void on_frame()
{
	static bool enabled;

	if (is_match_loaded() && !enabled)
	{
		MH_CreateHook((void*)(dwProcessBase + 0x1321110), hkCL_GetConfigString, (void**)&CL_GetConfigString);
		MH_EnableHook((void*)(dwProcessBase + 0x1321110));

		enabled = true;
	}
	else if (!is_in_game() && enabled)
	{
		MH_RemoveHook((void*)(dwProcessBase + 0x1321110));
		MH_DisableHook((void*)(dwProcessBase + 0x1321110));

		enabled = false;
	}
}


LONG CALLBACK main::hook::hookHandler(LPEXCEPTION_POINTERS ex)
{
	if (ex->ExceptionRecord->ExceptionCode == STATUS_SINGLE_STEP)
	{

		if (ex->ContextRecord->Rip == (uintptr_t)dwInstantDispatchMessage)
		{
			ex->ContextRecord->Rip = (uintptr_t)hkdwInstantDispatchMessage;
		}
		else if (ex->ContextRecord->Rip == (uintptr_t)LobbyVM_OnDisconnect)
		{
			ex->ContextRecord->Rip = (uintptr_t)hkLobbyVM_OnDisconnect;
		}
		else if (ex->ContextRecord->Rip == (uintptr_t)CL_ConnectionlessCMD)
		{
			return hkCL_ConnectionlessCMD(ex);
		}

		return EXCEPTION_CONTINUE_EXECUTION;
	}

	time_t now = time(0);
	#pragma warning(suppress : 4996)
	char* dt = ctime(&now);

	std::ofstream myfile;
	myfile.open("lergware\\logs\\UnhandledExceptions.txt""", std::ios_base::app);
	myfile  << dt << "Exception at: " << ex->ContextRecord->Rip << "\n";
	myfile.close();

	return EXCEPTION_CONTINUE_SEARCH;
}