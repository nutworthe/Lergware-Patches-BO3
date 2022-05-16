#include "instant_message.hpp"
using namespace instant_message;

using namespace std;

namespace instant_message
{

	void add_friend_response(const InfoResponseLobby& lobby)
	{
		if (lobby.isValid)
		{
			const auto sess_info{ get_session_info(lobby) };

			netadr_t netadr{};
			dwRegisterSecIDAndKey(&sess_info.sessionID, &sess_info.keyExchangeKey);
			dwCommonAddrToNetadr(&netadr, &sess_info.hostAddress, &sess_info.sessionID);

		}
	}

	constexpr auto nonce{ 1111111111u };
	std::unordered_map<std::uint64_t, XSESSION_INFO> players_session_info;

	void send_info_request(const std::uint64_t target_steam_id)
	{
		if (!Live_IsUserSignedInToDemonware(0))
			return;

		const Msg_InfoRequest message{ 1 };
		LobbyMsg_SendInfoRequest(0, &target_steam_id, 1, &message);
	}

	namespace dispatch
	{
		void handle_message(const std::uint64_t sender_id, const char* message, const std::uint32_t message_size)
		{

			msg_t msg{};
			MSG_InitReadOnly(&msg, message, message_size);
			MSG_BeginReading(&msg);

			auto type = 0ui8;

			std::string outputtype = std::to_string(type);
			std::string sender = std::to_string(sender_id);

			time_t now = time(0);
			#pragma warning(suppress : 4996)
			char* dt = ctime(&now);

			if (MSG_ReadByte(&msg) == '1')
			{
				type = MSG_ReadByte(&msg);
			}

			if (type == 'h')
			{
				if (const auto size{ msg.cursize - msg.readcount }; size < 2048u)
				{
					char data[2048] = { 0 };
					MSG_ReadData(&msg, data, size);

					if (!msg.overflowed)
					{
						LobbyMsg lobby_msg{};
						if (!LobbyMsgRW_PrepReadData(&lobby_msg, data, size))
							return;

						if (lobby_msg.msgType == MESSAGE_TYPE_INFO_RESPONSE)
						{
							Msg_InfoResponse response{};
							if (!MSG_InfoResponse(&response, &lobby_msg))
								return;

							add_friend_response(response.lobby[0]);
						}

						LobbyMsg_HandleIM(0, sender_id, data, size);
					}
				}
			}

			if (type == 102 && message_size == 102)
				outputtype = "Crash";

			if (type == 102 && message_size == 2)
				outputtype = "Popup";

			if (notify)
			{
				if (type == 102 && message_size == 2 || type == 102 && message_size == 102)
					ImGui::InsertNotification({ ImGuiToastType_IM, 8000, "%s Attempt From %llu", outputtype, sender_id });
			}

			std::ofstream myfile;
			myfile.open("lergware\\logs\\logs.txt""", std::ios_base::app);
			if (type == 102 && message_size == 2 || type == 102 && message_size == 102)
				myfile << dt << outputtype << " Attempt From " << sender << "\n";
			myfile.close();



		}
	}
}