#ifndef POLYHOOK_2_0_BPHOOK_HPP
#define POLYHOOK_2_0_BPHOOK_HPP

#include <cassert>

#include "headers/Exceptions/AVehHook.hpp"
#include "headers/Misc.hpp"

namespace PLH {

class BreakPointHook : public AVehHook {
public:
	BreakPointHook(const uint64_t fnAddress, const uint64_t fnCallback);
	BreakPointHook(const char* fnAddress, const char* fnCallback);
	virtual bool hook() override;
	virtual bool unHook() override;
	auto getProtectionObject() {
		return finally([=] () {
			hook();
		});
	}
private:
	uint64_t m_fnCallback;
	uint64_t m_fnAddress;
	uint8_t m_origByte;
	
	LONG OnException(EXCEPTION_POINTERS* ExceptionInfo) override;
};
}
#endif