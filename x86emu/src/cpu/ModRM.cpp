#include "modrm.h"
#include "Register.h"

#include <iostream>





ModRM::ModRM(uint8_t code)
{
	m_Mode = code >> 6;
	m_Register = (code & 0x38) >> 3;
	m_AddressingMode = code & 0x7;

}
