#pragma once

#include <cstdint>


class ModRM
{
public:
	ModRM(uint8_t byte);

	const uint8_t Mode() const { return m_Mode; }
	const uint8_t Register() const { return m_Register; }
	const uint8_t AddressingMode() const { return m_AddressingMode; }

private:
	uint8_t m_Mode;
	uint8_t m_Register;
	uint8_t m_AddressingMode;
};
