#include "OpCode.h"

#include <iostream>
#include <unordered_map>



static std::unordered_map<uint8_t, OpCode::OpCodeSpecification> s_OpCodeDefinitions =
{

	{ { 0b10000000 }, { "imm", OpCodeGeneration::x86_8088, { OpCodeBitFlag::w, OpCodeBitFlag::ModRM, OpCodeBitFlag::ImmediateToRegOrMem, OpCodeBitFlag::Immediate, OpCodeBitFlag::s }}},

	// ADD
	{ { 0b00000000 }, { "ADD", OpCodeGeneration::x86_8088, { OpCodeBitFlag::w, OpCodeBitFlag::ModRM }}},
	{ { 0b00000010 }, { "ADD", OpCodeGeneration::x86_8088, { OpCodeBitFlag::w, OpCodeBitFlag::ModRM }}},
	{ { 0b00000100 }, { "ADD", OpCodeGeneration::x86_8088, { OpCodeBitFlag::w, OpCodeBitFlag::Immediate }}},
	// CLC
	{ { 0b11111000 }, { "CLC", OpCodeGeneration::x86_8088, { OpCodeBitFlag::NoFlags }}},
	// CLD
	{ { 0b11111100 }, { "CLD", OpCodeGeneration::x86_8088, { OpCodeBitFlag::NoFlags }}},
	// CLI
	{ { 0b11111010 }, { "CLI", OpCodeGeneration::x86_8088, { OpCodeBitFlag::NoFlags }}},
	// MOV
	{ { 0b10001000 }, { "MOV", OpCodeGeneration::x86_8088, { OpCodeBitFlag::w, OpCodeBitFlag::ModRM }}},
	{ { 0b10001010 }, { "MOV", OpCodeGeneration::x86_8088, { OpCodeBitFlag::w, OpCodeBitFlag::ModRM }}},
	{ { 0b11000110 }, { "MOV", OpCodeGeneration::x86_8088, { OpCodeBitFlag::w, OpCodeBitFlag::Immediate }}},
	{ { 0b10110000 }, { "MOV", OpCodeGeneration::x86_8088, { OpCodeBitFlag::w, OpCodeBitFlag::Immediate, OpCodeBitFlag::AltEncoding }}},
	{ { 0b10100000 }, { "MOV", OpCodeGeneration::x86_8088, { OpCodeBitFlag::w, OpCodeBitFlag::Displacement }}},
	// MOV SEG
	{ { 0b10001110 }, { "MOV", OpCodeGeneration::x86_8088, { OpCodeBitFlag::ModRM, OpCodeBitFlag::sreg2 }}},
	{ { 0b10001100 }, { "MOV", OpCodeGeneration::x86_8088, { OpCodeBitFlag::ModRM, OpCodeBitFlag::sreg2 }}},
	// NOP
	{ { 0b10010000 }, { "NOP", OpCodeGeneration::x86_8088, { OpCodeBitFlag::NoFlags }}},
	// STC
	{ { 0b11111001 }, { "STC", OpCodeGeneration::x86_8088, { OpCodeBitFlag::NoFlags }}},
	// STD
	{ { 0b11111101 }, { "STD", OpCodeGeneration::x86_8088, { OpCodeBitFlag::NoFlags }}},
	// STI
	{ { 0b11111011 }, { "STI", OpCodeGeneration::x86_8088, { OpCodeBitFlag::NoFlags }}},
	// XOR
	{ { 0b00110000 }, { "XOR", OpCodeGeneration::x86_8088, { OpCodeBitFlag::w, OpCodeBitFlag::ModRM }}},
	{ { 0b00110010 }, { "XOR", OpCodeGeneration::x86_8088, { OpCodeBitFlag::w, OpCodeBitFlag::ModRM }}},
	{ { 0b00110100 }, { "XOR", OpCodeGeneration::x86_8088, { OpCodeBitFlag::w, OpCodeBitFlag::Immediate }}},

};

static std::unordered_map<uint8_t, std::string> s_ImmediateOpCodeNames =
{
	// ADD
	{ 0b000, "ADD" },
	// OR
	{ 0b001, "OR" },
	// ADC
	{ 0b010, "ADC" },
	// SBB
	{ 0b011, "SBB" },
	// AND
	{ 0b100, "AND" },
	// SUB
	{ 0b101, "SUB" },
	// XOR
	{ 0b110, "XOR" },
	// CMP
	{ 0b111, "CMP" },
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
			bitFlags = def.second.Bits;
			m_CodeName = def.second.Name;

			break;
		}
	}

	if (m_CodeName.empty())
	{
		for (auto& def : s_OpCodeDefinitions)
		{
			if ((code & 0xFC) == def.first)
			{
				bitFlags = def.second.Bits;
				m_CodeName = def.second.Name;

				break;
			}
		}
	}

	if (m_CodeName.empty())
	{
		for (auto& def : s_OpCodeDefinitions)
		{

			if ((code & 0xF0) == def.first)
			{
				bitFlags = def.second.Bits;
				m_CodeName = def.second.Name;

				break;
			}
		}
	}

	if (bitFlags.size() == 0)
	{
		std::cout << "No opcode found for value: " << std::hex << (uint16_t)code << std::dec << "\n";
		return;
	}

	m_Valid = true;

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
			case OpCodeBitFlag::ImmediateToRegOrMem: m_IsImmediateToRegOrMem = true; break;
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

	if (m_HasSignExtend)
	{
		m_SValue = code & 0x10;
	}

}

void OpCode::SetName(uint8_t num)
{
	m_CodeName = s_ImmediateOpCodeNames[num];
}
