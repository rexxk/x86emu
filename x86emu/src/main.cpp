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

/*
	std::vector<uint8_t> execStream =
	{
		0x13, 0xCB,
		0x89, 0xCA,
		0xB9,
		0x90,
		0x3e, 0x66, 0x67, 0x89, 0x1e,
		0x26, 0x89, 0x05,
		0x3e, 0x89, 0x1c,
		0x3e, 0x89, 0x54, 0x0c,
		0x64, 0x89, 0x10,
		0x64, 0x66, 0x67, 0x89, 0x90, 0x00, 0x01,
		0x64, 0x89, 0x90, 0x00, 0x01,
	};
*/
	std::vector<uint8_t> execStream =
	{
		0xb8, 0x00, 0x00, 0x8e, 0xc8, 0x8e, 0xd8, 0x8e, 0xc0, 0xb8, 0x00, 0x7c, 0x8e, 0xd0, 0xbc, 0xff, 0x00,
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

		RegisterDomain domain = RegisterDomain::Register;

		if (opCode.UseSegmentRegister())
			domain = RegisterDomain::Segment;

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


				Register reg(RegisterSize::Bits16, code & 0x7, domain);

				std::cout << opCode.Name() << " " << reg.ToString() << ", " << std::hex << value << std::dec << "\n";
			}
			else
			{
				valueLow = *(++it);

				value = valueLow;

				Register reg(RegisterSize::Bits8, code & 0x7, domain);

				std::cout << opCode.Name() << " " << reg.ToString() << ", " << std::hex << value << std::dec << "\n";
			}
		}

		if (opCode.HasModRM())
		{
			ModRM modRM(*(++it));

			Register sourceRegister((operandSizeOverride ? RegisterSize::Bits32 : RegisterSize::Bits16), modRM.GetRMIndex());
			Register destinationRegister((addressSizeOverride ? RegisterSize::Bits32 : RegisterSize::Bits16), modRM.GetRegisterIndex(), domain);

			EffectiveAddress effectiveAddress(modRM.Mode(), modRM.GetRMIndex());

			switch (modRM.Mode())
			{
				case 0:
				{

					// [BX+SI]
					std::cout << opCode.Name() << " [" << segment.ToString() << ":" << effectiveAddress.ToString() << "], " << destinationRegister.ToString() << "\n";
//					std::cout << "ModRM: [seg:reg], data = [" << segment.ToString() << ":" << effectiveAddress.ToString() << "], " << destinationRegister.ToString() << "\n";
					break;
				}
				case 1:
				{
					// [BX+SI]+displacement8
					uint8_t sib = *(++it);

					std::cout << opCode.Name() << " [" << segment.ToString() << ":" << effectiveAddress.ToString() << "+" << (uint16_t)sib << "], " << destinationRegister.ToString() << "\n";
//					std::cout << "ModRM: [seg:reg]+displacement8, data = [" << segment.ToString() << ":" << effectiveAddress.ToString() << "+" << (uint16_t)sib << "], " << destinationRegister.ToString() << "\n";

					break;
				}
				case 2:
				{
					uint8_t sibLow = *(++it);
					uint8_t sibHigh = *(++it);
					// [BX+SI]+displacement16
					std::cout << opCode.Name() << " [" << segment.ToString() << ":" << effectiveAddress.ToString() << "+" << (uint16_t)((sibHigh << 8) + sibLow) << "], " << destinationRegister.ToString() << "\n";
					break;
				}

				case 3:
				{
					std::cout << opCode.Name() << " " << destinationRegister.ToString() << ", " << sourceRegister.ToString() << "\n";
					break;
				}
			}
		}
	}

}
