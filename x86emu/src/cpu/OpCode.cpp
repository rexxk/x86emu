#include "OpCode.h"

#include <iostream>
#include <unordered_map>


static std::unordered_map<uint8_t, std::vector<OpCodeBitFlag>> s_OpCodeDefinitions =
{
	// MOV
	{ { 0b10001000 }, { { OpCodeBitFlag::w, OpCodeBitFlag::ModRM }}},
	{ { 0b10001010 }, { { OpCodeBitFlag::w, OpCodeBitFlag::ModRM }}},
	{ { 0b11000110 }, { { OpCodeBitFlag::w, OpCodeBitFlag::Immediate }}},
	{ { 0b10110000 }, { { OpCodeBitFlag::w, OpCodeBitFlag::Immediate, OpCodeBitFlag::AltEncoding }}},
	{ { 0b10100000 }, { { OpCodeBitFlag::w, OpCodeBitFlag::Displacement }}},
	{ { 0b10010000 }, { { OpCodeBitFlag::NoFlags } } },
};




OpCode::OpCode(uint8_t code)
{

	std::cout << "OpCode: " << std::hex << (uint16_t)code << std::dec << "\n";

	std::vector<OpCodeBitFlag> bitFlags;

	for (auto& def : s_OpCodeDefinitions)
	{
		// Check for 7-bit and then 6-bit and lastly 4-bit hits
		if ((code & 0xFE) == def.first)
		{
			bitFlags = def.second;
			break;
		}

		if ((code & 0xFC) == def.first)
		{
			bitFlags = def.second;
			break;
		}

		if ((code & 0xF0) == def.first)
		{
			bitFlags = def.second;
			break;
		}

	}

	if (bitFlags.size() == 0)
	{
		std::cout << "No opcode found for value: " << std::hex << (uint16_t)code << std::dec << "\n";
	}

	for (auto& flag : bitFlags)
	{
		switch (flag)
		{
			case OpCodeBitFlag::w: m_HasW = true; break;
			case OpCodeBitFlag::ModRM: m_HasModRM = true; break;
			case OpCodeBitFlag::Immediate: m_HasImmediate = true; break;
			case OpCodeBitFlag::AltEncoding: m_HasAltEncoding = true; break;
		}
	}

	if (m_HasW)
	{
		if (m_HasAltEncoding)
		{
			m_WValue = code & 0x80;
		}
		else
		{
			m_WValue = code & 0x1;
		}
	}

}
