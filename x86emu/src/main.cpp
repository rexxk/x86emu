#include "cpu/modrm.h"
#include "cpu/Register.h"
#include "cpu/OpCode.h"

#include <vector>

#include <iostream>





int main()
{
	std::cout << "x86 emulator\n";

	std::vector<uint8_t> execStream = 
	{
		0x13, 0xCB,
		0x89, 0xCA,
		0xB9,
		0x90,
	};

	for (auto it = execStream.begin(); it != execStream.end(); it++)
	{
		uint8_t code = *(it);
		OpCode opCode(code);

		if (opCode.HasModRM())
		{
			ModRM modRM(*(++it));

			switch (modRM.Mode())
			{
			case 0:
				// [BX+SI]
				break;
			case 1:
				// [BX+SI]+displacement8
				break;
			case 2:
				// [BX+SI]+displacement16
				break;
			case 3:
				std::cout << "ModRM: " << std::hex << (uint16_t)modRM.Mode() << " " << Register16BitToString((Register16Bit)modRM.Register()) << " " << Register16BitToString((Register16Bit)modRM.AddressingMode()) << "\n";
				break;
			}
		}
	}

}
