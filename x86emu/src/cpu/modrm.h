#pragma once

#include "Register.h"

#include <cstdint>


class ModRM
{
public:
	ModRM(uint8_t byte);

	const uint8_t Mode() const { return m_Mode; }
	const uint8_t GetRegisterIndex() const { return m_RegisterIndex; }
	const uint8_t GetRMIndex() const { return m_RMIndex; }

private:
	uint8_t m_Mode;

	uint8_t m_RegisterIndex = 0;
	uint8_t m_RMIndex = 0;
};
