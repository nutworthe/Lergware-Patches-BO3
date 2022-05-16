#pragma once
#include "includes.h"
#include "common.h"
#include <cstdint>

extern bool initialized;
extern bool open;

namespace main {

	namespace hook {

		extern bool sent;
		extern int frame;
		void initializeHook();
		LONG CALLBACK hookHandler(EXCEPTION_POINTERS* ex);
	}
}

bool should_ignore_msg(UINT msg);

template <typename T>
static void set(void* place, T value)
{
	DWORD old_protect;
	VirtualProtect(place, sizeof(T), PAGE_EXECUTE_READWRITE, &old_protect);

	*static_cast<T*>(place) = value;

	VirtualProtect(place, sizeof(T), old_protect, &old_protect);
	FlushInstructionCache(GetCurrentProcess(), place, sizeof(T));
}

template <typename T>
static void set(const size_t place, T value)
{
	return set<T>(reinterpret_cast<void*>(place), value);
}
