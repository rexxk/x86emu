#include "Register.h"




std::string Register8BitToString(Register8Bit reg)
{
	switch (reg)
	{
	case Register8Bit::AL: return "AL";
	case Register8Bit::CL: return "CL";
	case Register8Bit::DL: return "DL";
	case Register8Bit::BL: return "BL";
	case Register8Bit::AH: return "AH";
	case Register8Bit::CH: return "CH";
	case Register8Bit::DH: return "DH";
	case Register8Bit::BH: return "BH";
	}

	return "--";
}

std::string Register16BitToString(Register16Bit reg)
{
	switch (reg)
	{
	case Register16Bit::AX: return "AX";
	case Register16Bit::CX: return "CX";
	case Register16Bit::DX: return "DX";
	case Register16Bit::BX: return "BX";
	case Register16Bit::SP: return "SP";
	case Register16Bit::BP: return "BP";
	case Register16Bit::SI: return "SI";
	case Register16Bit::DI: return "DI";
	}

	return "--";
}

std::string Register32BitToString(Register32Bit reg)
{
	switch (reg)
	{
	case Register32Bit::EAX: return "EAX";
	case Register32Bit::ECX: return "ECX";
	case Register32Bit::EDX: return "EDX";
	case Register32Bit::EBX: return "EBX";
	case Register32Bit::ESP: return "ESP";
	case Register32Bit::EBP: return "EBP";
	case Register32Bit::ESI: return "ESI";
	case Register32Bit::EDI: return "EDI";
	}

	return "--";
}

