#pragma once

#include <cstdint>
#include <string>

#include <unordered_map>
#include <vector>

enum class RegisterType
{
	AL, BL, CL, DL, AH, BH, CH, DH,
	AX, BX, CX, DX, SP, BP, SI, DI,
	EAX, EBX, ECX, EDX, ESP, EBP, ESI, EDI,
	CR0, CR2, CR3, CR4,
	CS, DS, ES, FS, GS, SS,
};

enum class RegisterSize
{
	Bits8,
	Bits16,
	Bits32,
};

enum class RegisterDomain
{
	Register,
	Control,
	Segment,
};


class Register
{
public:
	Register() = default;
	Register(RegisterSize size, uint8_t registerIndex, RegisterDomain domain = RegisterDomain::Register);

	std::string ToString();

	const RegisterType Type() const { return m_Type; }
	const RegisterSize Size() const { return m_Size; }

private:
	RegisterSize m_Size = RegisterSize::Bits16;
	RegisterType m_Type = RegisterType::AX;

};
