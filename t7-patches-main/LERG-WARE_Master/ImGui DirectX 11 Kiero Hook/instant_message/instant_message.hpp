#pragma once
#include "../includes.h"

namespace instant_message
{

	void send_info_request(const std::uint64_t target_steam_id);

	namespace dispatch
	{
		void handle_message(const std::uint64_t sender_id, const char* message, const std::uint32_t message_size);
	}
}