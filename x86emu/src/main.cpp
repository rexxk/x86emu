#include "cpu/modrm.h"
#include "cpu/Register.h"
#include "cpu/OpCode.h"
#include "cpu/Prefix.h"
#include "cpu/Segment.h"
#include "cpu/EffectiveAddress.h"

#include <vector>
#include <unordered_map>

#include <iostream>





int main()
{
	std::cout << "x86 emulator\n";


//	std::vector<uint8_t> execStream =
//	{
//		0x13, 0xCB,
//		0x89, 0xCA,
//		0xB9,
//		0x90,
//		0x3e, 0x66, 0x67, 0x89, 0x1e,
//		0x26, 0x89, 0x05,
//		0x3e, 0x89, 0x1c,
//		0x3e, 0x89, 0x54, 0x0c,
//		0x64, 0x89, 0x10,
//		0x64, 0x66, 0x67, 0x89, 0x90, 0x00, 0x01,
//		0x64, 0x89, 0x90, 0x00, 0x01,
//	};

//	std::vector<uint8_t> execStream =
//	{
//		0xb8, 0x00, 0x00, 0x8e, 0xc8, 0x8e, 0xd8, 0x8e, 0xc0, 0xb8, 0x00, 0x7c, 0x8e, 0xd0, 0xbc, 0xff, 0x00,
//	};

	std::vector<uint8_t> execStream =
	{
		0x88, 0xd8, 0x89, 0xd8, 0x66, 0x89, 0xd8, 0x88, 0xcc, 0x90,
	};


	for (auto it = execStream.begin(); it != execStream.end(); it++)
	{
		uint8_t code = *(it);

		std::vector<Prefix> prefixes;

		while (true)
		{
			Prefix prefix(code);

			if (prefix.Type() == PrefixType::None)
				break;

			prefixes.push_back(prefix);

			code = *(++it);
		}

		Segment segment;
		bool operandSizeOverride = false;
		bool addressSizeOverride = false;

		for (auto& prefix : prefixes)
		{
			switch (prefix.Type())
			{
				case PrefixType::CSOverride: segment.Override(PrefixType::CSOverride); break;
				case PrefixType::DSOverride: segment.Override(PrefixType::DSOverride); break;
				case PrefixType::ESOverride: segment.Override(PrefixType::ESOverride); break;
				case PrefixType::FSOverride: segment.Override(PrefixType::FSOverride); break;
				case PrefixType::GSOverride: segment.Override(PrefixType::GSOverride); break;
				case PrefixType::SSOverride: segment.Override(PrefixType::SSOverride); break;

				case PrefixType::OperandSizeOverride: operandSizeOverride = true; break;
				case PrefixType::AddressSizeOverride: addressSizeOverride = true; break;
			}
		}

		OpCode opCode(code);

		RegisterSize registerSize = RegisterSize::Bits8;

		if (opCode.WValue())
			registerSize = RegisterSize::Bits16;

		if (operandSizeOverride && registerSize == RegisterSize::Bits8)
			registerSize = RegisterSize::Bits16;
		else if (operandSizeOverride && registerSize == RegisterSize::Bits16)
			registerSize = RegisterSize::Bits32;

		if (opCode.IsImmediate() && opCode.HasAltEncoding())
		{
			uint8_t valueLow = 0;
			uint8_t valueHigh = 0;

			uint16_t value = 0;

			if (opCode.WValue() == true)
			{
				valueLow = *(++it);
				valueHigh = *(++it);

				value = (valueHigh << 8) + valueLow;

				Register reg(registerSize, code & 0x7);

				std::cout << opCode.Name() << " " << reg.ToString() << ", " << std::hex << value << std::dec << "\n";
			}
			else
			{
				valueLow = *(++it);

				value = valueLow;

				Register reg(registerSize, code & 0x7);

				std::cout << opCode.Name() << " " << reg.ToString() << ", " << std::hex << value << std::dec << "\n";
			}
		}

		if (opCode.HasModRM())
		{
			ModRM modRM(*(++it));

			Register sourceRegister;
			Register destinationRegister;

			if (opCode.UseSegmentRegister())
			{
				registerSize = RegisterSize::Bits16;
				sourceRegister = Register(registerSize, modRM.GetRMIndex());
				destinationRegister = Register(registerSize, modRM.GetRegisterIndex(), RegisterDomain::Segment);
			}
			else
			{
				sourceRegister = Register(registerSize, modRM.GetRegisterIndex());
				destinationRegister = Register(registerSize, modRM.GetRMIndex());
			}

			EffectiveAddress effectiveAddress(modRM.Mode(), modRM.GetRMIndex());

			switch (modRM.Mode())
			{
				case 0:
				{

					// [BX+SI]
					std::cout << opCode.Name() << " [" << segment.ToString() << ":" << effectiveAddress.ToString() << "], " << sourceRegister.ToString() << "\n";
//					std::cout << "ModRM: [seg:reg], data = [" << segment.ToString() << ":" << effectiveAddress.ToString() << "], " << destinationRegister.ToString() << "\n";
					break;
				}
				case 1:
				{
					// [BX+SI]+displacement8
					uint8_t sib = *(++it);

					std::cout << opCode.Name() << " [" << segment.ToString() << ":" << effectiveAddress.ToString() << "+" << (uint16_t)sib << "], " << sourceRegister.ToString() << "\n";
//					std::cout << "ModRM: [seg:reg]+displacement8, data = [" << segment.ToString() << ":" << effectiveAddress.ToString() << "+" << (uint16_t)sib << "], " << destinationRegister.ToString() << "\n";

					break;
				}
				case 2:
				{
					uint8_t sibLow = *(++it);
					uint8_t sibHigh = *(++it);
					// [BX+SI]+displacement16
					std::cout << opCode.Name() << " [" << segment.ToString() << ":" << effectiveAddress.ToString() << "+" << (uint16_t)((sibHigh << 8) + sibLow) << "], " << sourceRegister.ToString() << "\n";
					break;
				}

				case 3:
				{
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

}
