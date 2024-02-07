#pragma once

#include "Register.h"

#include <cstdint>
#include <string>


enum class EffectiveAddressType
{
	BXpSI,
	BXpDI,
	BPpSI,
	BPpDI,
	SI,
	DI,
	disp16,
	BX,

	BXpSIpdisp8,
	BXpDIpdisp8,
	BPpSIpdisp8,
	BPpDIpdisp8,
	SIpdisp8,
	DIpdisp8,
	BPpdisp8,
	BXpdisp8,

	BXpSIpdisp16,
	BXpDIpdisp16,
	BPpSIpdisp16,
	BPpDIpdisp16,
	SIpdisp16,
	DIpdisp16,
	BPpdisp16,
	BXpdisp16,
};


class EffectiveAddress
{
public:
	EffectiveAddress(uint8_t mode, uint8_t rmValue);

	std::string ToString();

	const EffectiveAddressType Type() const { return m_Type; }

private:
	EffectiveAddressType m_Type = EffectiveAddressType::SI;

};

