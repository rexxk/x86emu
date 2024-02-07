#include "Register.h"


static std::unordered_map<RegisterSize, std::vector<RegisterType>> s_RegisterTable =
{
	{ RegisterSize::Bits8, { RegisterType::AL, RegisterType::CL, RegisterType::DL, RegisterType::BL,
							 RegisterType::AH, RegisterType::CH, RegisterType::DH, RegisterType::BH, } },
	{ RegisterSize::Bits16, { RegisterType::AX, RegisterType::CX, RegisterType::DX, RegisterType::BX,
							  RegisterType::SP, RegisterType::BP, RegisterType::SI, RegisterType::DI } },
	{ RegisterSize::Bits32, { RegisterType::EAX, RegisterType::ECX, RegisterType::EDX, RegisterType::EBX,
							  RegisterType::ESP, RegisterType::EBP, RegisterType::ESI, RegisterType::EDI } },
};


static std::vector<RegisterType> s_ControlRegisters =
{
	RegisterType::CR0, RegisterType::CR2, RegisterType::CR3, RegisterType::CR4,
};


static std::vector<RegisterType> s_SegmentRegisters =
{
	RegisterType::ES, RegisterType::CS, RegisterType::SS, RegisterType::DS, RegisterType::FS, RegisterType::GS,
};


Register::Register(RegisterSize size, uint8_t registerIndex, RegisterDomain domain)
	: m_Size(size)
{
	switch (domain)
	{
		case RegisterDomain::Register:
		{
			if (registerIndex < (uint8_t)s_RegisterTable[size].size())
				m_Type = s_RegisterTable[size].at(registerIndex);
			else
				m_Type = RegisterType::AX;

			break;
		}

		case RegisterDomain::Control:
		{
			if (registerIndex < (uint8_t)s_ControlRegisters.size())
				m_Type = s_ControlRegisters.at(registerIndex);
			else
				m_Type = RegisterType::CR0;

			break;
		}

		case RegisterDomain::Segment:
		{
			if (registerIndex < (uint8_t)s_SegmentRegisters.size())
				m_Type = s_SegmentRegisters.at(registerIndex);
			else
				m_Type = RegisterType::DS;

			break;
		}
	}

}

std::string Register::ToString()
{
	switch (m_Type)
	{
		case RegisterType::AL: return "AL";
		case RegisterType::CL: return "CL";
		case RegisterType::DL: return "DL";
		case RegisterType::BL: return "BL";
		case RegisterType::AH: return "AH";
		case RegisterType::CH: return "CH";
		case RegisterType::DH: return "DH";
		case RegisterType::BH: return "BH";
		case RegisterType::AX: return "AX";
		case RegisterType::CX: return "CX";
		case RegisterType::DX: return "DX";
		case RegisterType::BX: return "BX";
		case RegisterType::SP: return "SP";
		case RegisterType::BP: return "BP";
		case RegisterType::SI: return "SI";
		case RegisterType::DI: return "DI";
		case RegisterType::EAX: return "EAX";
		case RegisterType::ECX: return "ECX";
		case RegisterType::EDX: return "EDX";
		case RegisterType::EBX: return "EBX";
		case RegisterType::ESP: return "ESP";
		case RegisterType::EBP: return "EBP";
		case RegisterType::ESI: return "ESI";
		case RegisterType::EDI: return "EDI";
		case RegisterType::CR0: return "CR0";
		case RegisterType::CR2: return "CR2";
		case RegisterType::CR3: return "CR3";
		case RegisterType::CR4: return "CR4";
		case RegisterType::CS: return "CS";
		case RegisterType::DS: return "DS";
		case RegisterType::ES: return "ES";
		case RegisterType::FS: return "FS";
		case RegisterType::GS: return "GS";
		case RegisterType::SS: return "SS";
	}

	return "Unknown register size";
}
