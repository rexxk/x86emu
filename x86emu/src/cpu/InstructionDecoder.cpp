#include "InstructionDecoder.h"

#include "modrm.h"
#include "Register.h"
#include "OpCode.h"
#include "Prefix.h"
#include "Segment.h"
#include "EffectiveAddress.h"

#include <iostream>


InstructionDecoder::InstructionDecoder(std::vector<uint8_t>::iterator& byteIterator)
{
	FindPrefixes(byteIterator);

	OpCode opCode(*(byteIterator));

	if (opCode.WValue())
		m_RegisterSize = RegisterSize::Bits16;

	if (m_OperandSizeOverride && m_RegisterSize == RegisterSize::Bits8)
		m_RegisterSize = RegisterSize::Bits16;
	else if (m_OperandSizeOverride && m_RegisterSize == RegisterSize::Bits16)
		m_RegisterSize = RegisterSize::Bits32;

	if (opCode.IsImmediate() && opCode.HasAltEncoding())
	{
		uint8_t valueLow = 0;
		uint8_t valueHigh = 0;

		uint16_t value = 0;

		if (opCode.WValue() == true)
		{
			valueLow = *(++byteIterator);
			valueHigh = *(++byteIterator);

			value = (valueHigh << 8) + valueLow;

			Register reg(m_RegisterSize, *(byteIterator) & 0x7);

			std::cout << opCode.Name() << " " << reg.ToString() << ", " << std::hex << (uint16_t)value << std::dec << "\n";
		}
		else
		{
			valueLow = *(++byteIterator);

			value = valueLow;

			Register reg(m_RegisterSize, *(byteIterator) & 0x7);

			std::cout << opCode.Name() << " " << reg.ToString() << ", " << std::hex << (uint16_t)value << std::dec << "\n";
		}
	}

	if (opCode.HasModRM())
	{
		ModRM modRM(*(++byteIterator));

		if (opCode.IsImmediateToRegOrMem())
		{
			opCode.SetName(modRM.GetRegisterIndex());
		}

		Register sourceRegister;
		Register destinationRegister;

		if (opCode.UseSegmentRegister())
		{
			m_RegisterSize = RegisterSize::Bits16;
			sourceRegister = Register(m_RegisterSize, modRM.GetRMIndex());
			destinationRegister = Register(m_RegisterSize, modRM.GetRegisterIndex(), RegisterDomain::Segment);
		}
		else
		{
			sourceRegister = Register(m_RegisterSize, modRM.GetRegisterIndex());
			destinationRegister = Register(m_RegisterSize, modRM.GetRMIndex());
		}

		EffectiveAddress effectiveAddress(modRM.Mode(), modRM.GetRMIndex());

		uint8_t immediateData = 0;

		if (opCode.IsImmediate())
		{
			immediateData = *(++byteIterator);
		}

		switch (modRM.Mode())
		{
		case 0:
		{
			// [BX+SI]
			if (opCode.IsImmediate() && modRM.GetRegisterIndex() == 0)
				std::cout << opCode.Name() << " [" << m_Segment.ToString() << ":" << effectiveAddress.ToString() << "], " << (uint16_t)immediateData << "\n";
			else
				std::cout << opCode.Name() << " [" << m_Segment.ToString() << ":" << effectiveAddress.ToString() << "], " << sourceRegister.ToString() << "\n";
			break;
		}
		case 1:
		{
			// [BX+SI]+displacement8
			uint8_t sib = *(++byteIterator);

			std::cout << opCode.Name() << " [" << m_Segment.ToString() << ":" << effectiveAddress.ToString() << "+" << (uint16_t)sib << "], " << sourceRegister.ToString() << "\n";
			break;
		}
		case 2:
		{
			uint8_t sibLow = *(++byteIterator);
			uint8_t sibHigh = *(++byteIterator);
			// [BX+SI]+displacement16
			std::cout << opCode.Name() << " [" << m_Segment.ToString() << ":" << effectiveAddress.ToString() << "+" << (uint16_t)((sibHigh << 8) + sibLow) << "], " << sourceRegister.ToString() << "\n";
			break;
		}

		case 3:
		{
			if (opCode.IsImmediate() && modRM.GetRegisterIndex() == 0)
				std::cout << opCode.Name() << " " << destinationRegister.ToString() << ", " << (uint16_t)immediateData << "\n";
			else
				std::cout << opCode.Name() << " " << destinationRegister.ToString() << ", " << sourceRegister.ToString() << "\n";

			break;
		}
		}
	}

	if (opCode.HasNoFlags())
	{
		std::cout << opCode.Name() << "\n";
	}
}


void InstructionDecoder::FindPrefixes(std::vector<uint8_t>::iterator& byteIterator)
{
	while (true)
	{
		Prefix prefix(*(byteIterator));

		if (prefix.Type() == PrefixType::None)
			break;

		m_Prefixes.push_back(prefix);

		byteIterator++;
	}

	for (auto& prefix : m_Prefixes)
	{
		switch (prefix.Type())
		{
			case PrefixType::CSOverride: m_Segment.Override(PrefixType::CSOverride); break;
			case PrefixType::DSOverride: m_Segment.Override(PrefixType::DSOverride); break;
			case PrefixType::ESOverride: m_Segment.Override(PrefixType::ESOverride); break;
			case PrefixType::FSOverride: m_Segment.Override(PrefixType::FSOverride); break;
			case PrefixType::GSOverride: m_Segment.Override(PrefixType::GSOverride); break;
			case PrefixType::SSOverride: m_Segment.Override(PrefixType::SSOverride); break;

			case PrefixType::OperandSizeOverride: m_OperandSizeOverride = true; break;
			case PrefixType::AddressSizeOverride: m_AddressSizeOverride = true; break;
		}
	}

}
