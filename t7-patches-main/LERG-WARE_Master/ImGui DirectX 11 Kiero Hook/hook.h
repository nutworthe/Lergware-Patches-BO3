#pragma once
#include "includes.h"

void on_frame();

std::string va(const char* fmt, ...);
std::string adr_to_string(const netadr_t* address);

namespace hook {
	extern bool sent;
	extern int frame;
	void intitalize();
	void SetHardwareBreakpoint(DWORD_PTR address, int reg);
	LONG CALLBACK hookHandler(EXCEPTION_POINTERS* ex);
}

class Hooks
{
public:
	void Initialize();
} extern hooks;


