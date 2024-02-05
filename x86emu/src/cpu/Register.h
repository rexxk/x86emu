#pragma once

#include <cstdint>
#include <string>


enum class Register8Bit
{
	AL = 0,
	CL,
	DL,
	BL,
	AH,
	CH,
	DH,
	BH,
};

enum class Register16Bit
{
	AX = 0,
	CX,
	DX,
	BX,
	SP,
	BP,
	SI,
	DI,
};

enum class Register32Bit
{
	EAX = 0,
	ECX,
	EDX,
	EBX,
	ESP,
	EBP,
	ESI,
	EDI,
};

enum class SegmentRegister2
{
	ES = 0,
	CS,
	SS,
	DS,
};

enum class SegmentRegister3
{
	ES = 0,
	CS,
	SS,
	DS,
	FS,
	GS,
};

enum class SpecialPurposeRegister
{
	CR0 = 0,
	CR2 = 2,
	CR3,
	CR4,
};


std::string Register8BitToString(Register8Bit reg);
std::string Register16BitToString(Register16Bit reg);
std::string Register32BitToString(Register32Bit reg);
