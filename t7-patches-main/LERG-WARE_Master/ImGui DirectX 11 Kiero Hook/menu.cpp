#include "menu.h"

using namespace std;


vector<string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream. 
	string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}

namespace menu
{
	bool is_open()
	{
		return open;
	}

	void draw()
	{
		rgbstyle();

		if (is_open())
		{
			*(int*)((DWORD64)GetModuleHandleA(NULL) + 0x17E71335) = 0;
			ImGui::Begin("lergware", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
			{
				if (ImGui::BeginTabBar("Main", ImGuiTabBarFlags_NoTooltip))
				{

					if (ImGui::BeginTabItem("Tools"))
					{

						ImGui::Dummy(ImVec2(0.0f, 2.0f));

						static auto join_input = ""s;

						ImGui::Dummy(ImVec2(0.0f, 3.0f));

						ImGui::InputTextWithHint("##JOIN", "XUID", &join_input);
						ImGui::SameLine();

						if (ImGui::Button("Join##XUID"))
						{
							LobbyVM_JoinEvent(0, std::stoull(join_input), JoinType::JOIN_TYPE_PARTY);
						}

						ImGui::Dummy(ImVec2(0.0f, 3.0f));

						ImGui::Separator();

						static auto cbuf_input = ""s;

						ImGui::Dummy(ImVec2(0.0f, 3.0f));

						ImGui::InputTextWithHint("##CBUF", "CBUF", &cbuf_input);
						ImGui::SameLine();

						if (ImGui::Button("Send##CBUF"))
						{
							Cbuf_AddText(0, cbuf_input.data());
						}

						static auto single_input = ""s;

						ImGui::Dummy(ImVec2(0.0f, 3.0f));

						ImGui::InputTextWithHint("##SINGLE", "SINGLE", &single_input);
						ImGui::SameLine();

						if (ImGui::Button("Send##SINGLE"))
						{
							Cmd_ExecuteSingleCommand(0, 0, single_input.data(), false);
						}

						static auto reliable_input = ""s;

						ImGui::Dummy(ImVec2(0.0f, 3.0f));

						ImGui::InputTextWithHint("##RELIABLE", "RELIABLE", &reliable_input);

						ImGui::SameLine();

						if (ImGui::Button("Send##RELIABLE"))
						{
							CL_AddReliableCommand(0, reliable_input.data());
						}

						ImGui::Dummy(ImVec2(0.0f, 3.0f));

						static auto dvar_input = ""s;

						ImGui::InputTextWithHint("##DVAR", "DVAR", &dvar_input);

						ImGui::SameLine();

						if (ImGui::Button("Send##DVAR"))
						{
							vector<string> sep = split(dvar_input, ' ');

							if (strlen(sep[1].c_str()))
								Dvar_SetFromString(sep[0].c_str(), sep[1].c_str(), true);
						}

						ImGui::Dummy(ImVec2(0.0f, 3.0f));

						ImGui::Separator();

						ImGui::Dummy(ImVec2(0.0f, 3.0f));

						{
							void CBUF(int al, char* a2);
						}

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Misc"))
					{

						ImGui::Dummy(ImVec2(0.0f, 2.0f));

						ImGui::Checkbox("Notify", &notify);

						ImGui::SameLine();

						ImGui::Checkbox("Friends Only", &friendsonly);

						ImGui::Separator();

						static auto nameBuffer = ""s;

						ImGui::Dummy(ImVec2(0.0f, 3.0f));

						ImGui::InputTextWithHint("##NAME", "NAME", &nameBuffer);
						ImGui::SameLine();

						if (ImGui::Button("Set##NAME"))
						{
							strncpy_s(spoofName, sizeof(spoofName), nameBuffer.data(), -1);
							RenamePreGame(spoofName);
						}

						static auto clan_input = ""s;

						ImGui::Dummy(ImVec2(0.0f, 3.0f));

						ImGui::InputTextWithHint("##CLAN", "CLAN", &clan_input);
						ImGui::SameLine();

						if (ImGui::Button("Set##CLAN"))
						{
							LiveStats_SetClanTagText(0, clan_input.data());
						}

						ImGui::Dummy(ImVec2(0.0f, 3.0f));

						ImGui::Separator();

						ImGui::Dummy(ImVec2(0.0f, 3.0f));

						ImGui::EndTabItem();

					}

					ImGui::EndTabBar();
				}
				ImGui::End();
			}
		}

		else
		{
			*(int*)((DWORD64)GetModuleHandleA(NULL) + 0x17E71335) = 1;
		}
	}
}