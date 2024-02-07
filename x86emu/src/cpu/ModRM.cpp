#include "modrm.h"

#include <iostream>





ModRM::ModRM(uint8_t code)
{
	m_Mode = code >> 6;
	m_RegisterIndex = (code & 0x38) >> 3;
	m_RMIndex = code & 0x7;
}
