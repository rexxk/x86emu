#include "OpCode.h"

#include <iostream>
#include <unordered_map>


static std::unordered_map<uint8_t, std::vector<OpCodeBitFlag>> s_OpCodeDefinitions =
{
	// ADD
	{ { 0b00000000 }, { { OpCodeBitFlag::w, OpCodeBitFlag::ModRM }}},
	{ { 0b00000010 }, { { OpCodeBitFlag::w, OpCodeBitFlag::ModRM }}},
	{ { 0b10000000 }, { { OpCodeBitFlag::w, OpCodeBitFlag::ModRM, OpCodeBitFlag::Immediate, OpCodeBitFlag::s }}},
	{ { 0b00000100 }, { { OpCodeBitFlag::w, OpCodeBitFlag::Immediate }}},


	// CLC
	{ { 0b11111000 }, { { OpCodeBitFlag::NoFlags }}},
	// CLD
	{ { 0b11111100 }, { { OpCodeBitFlag::NoFlags }}},
	// CLI
	{ { 0b11111010 }, { { OpCodeBitFlag::NoFlags }}},
	// MOV
	{ { 0b10001000 }, { { OpCodeBitFlag::w, OpCodeBitFlag::ModRM }}},
	{ { 0b10001010 }, { { OpCodeBitFlag::w, OpCodeBitFlag::ModRM }}},
	{ { 0b11000110 }, { { OpCodeBitFlag::w, OpCodeBitFlag::Immediate }}},
	{ { 0b10110000 }, { { OpCodeBitFlag::w, OpCodeBitFlag::Immediate, OpCodeBitFlag::AltEncoding }}},
	{ { 0b10100000 }, { { OpCodeBitFlag::w, OpCodeBitFlag::Displacement }}},
	// MOV SEG
	{ { 0b10001110 }, { { OpCodeBitFlag::ModRM, OpCodeBitFlag::sreg2 }}},
	{ { 0b10001100 }, { { OpCodeBitFlag::ModRM, OpCodeBitFlag::sreg2 }}},
	// NOP
	{ { 0b10010000 }, { { OpCodeBitFlag::NoFlags }}},
	// STC
	{ { 0b11111001 }, { { OpCodeBitFlag::NoFlags }}},
	// STD
	{ { 0b11111101 }, { { OpCodeBitFlag::NoFlags }}},
	// STI
	{ { 0b11111011 }, { { OpCodeBitFlag::NoFlags }}},
};


static std::unordered_map<uint8_t, std::string> s_OpCodeNameMap =
{
	// ADD
	{ 0b00000000, "ADD" },
	{ 0b00000010, "ADD" },
	{ 0b10000000, "ADD" },
	{ 0b00000100, "ADD" },
	// CLC
	{ 0b11111000, "CLC" },
	// CLD
	{ 0b11111100, "CLD" },
	// CLI
	{ 0b11111010, "CLI" },
	// MOV
	{ 0b10001000, "MOV" },
	{ 0b10001010, "MOV" },
	{ 0b11000110, "MOV" },
	{ 0b10110000, "MOV" },
	{ 0b10100000, "MOV" },
	// MOV SEG
	{ 0b10001110, "MOV" },
	{ 0b10001100, "MOV" },
	// NOP
	{ 0b10010000, "NOP" },
	// STC
	{ 0b11111001, "STC" },
	// STD
	{ 0b11111101, "STD" },
	// STI
	{ 0b11111011, "STI" },
};




OpCode::OpCode(uint8_t code)
{

//	std::cout << "OpCode: " << std::hex << (uint16_t)code << std::dec << "\n";

	std::vector<OpCodeBitFlag> bitFlags;


	for (auto& def : s_OpCodeDefinitions)
	{
		// Check for 7-bit and then 6-bit and lastly 4-bit hits
		if ((code & 0xFE) == def.first)
		{
			bitFlags = def.second;
			m_CodeName = s_OpCodeNameMap[code & 0xFE];

			break;
		}

		if ((code & 0xFC) == def.first)
		{
			bitFlags = def.second;
			m_CodeName = s_OpCodeNameMap[code & 0xFC];

			break;
		}

		if ((code & 0xF0) == def.first)
		{
			bitFlags = def.second;
			m_CodeName = s_OpCodeNameMap[code & 0xF0];

			break;
		}

	}

	if (bitFlags.size() == 0)
	{
		std::cout << "No opcode found for value: " << std::hex << (uint16_t)code << std::dec << "\n";
		return;
	}

	for (auto& flag : bitFlags)
	{
		switch (flag)
		{
			case OpCodeBitFlag::w: m_HasW = true; break;
			case OpCodeBitFlag::ModRM: m_HasModRM = true; break;
			case OpCodeBitFlag::Immediate: m_HasImmediate = true; break;
			case OpCodeBitFlag::AltEncoding: m_HasAltEncoding = true; break;
			case OpCodeBitFlag::sreg2: m_UseSegmentRegister = true; break;
			case OpCodeBitFlag::NoFlags: m_NoFlags = true; break;
			case OpCodeBitFlag::s: m_HasSignExtend = true; break;
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
