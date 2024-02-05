#pragma once

#include "modrm.h"


enum class OpCodeBitFlag
{
	NoFlags,

	reg,
	w,
	s,
	sreg2,
	sreg3,
	eee,
	tttn,
	d,

	ModRM,
	SIB,
	Immediate,
	Displacement,

	AltEncoding,
};


enum class ConditionTestField
{
	Overflow = 0,
	NoOverflow,
	BelowAndNotAboveOrEqual,
	NotBelowAndAboveOrEqual,
	EqualAndZero,
	NotEqualAndNotZero,
	BelowOrEqualAndNotAbove,
	NotBelowOrEqualAndAbove,
	Sign,
	NotSign,
	ParityAndParityEven,
	NotParityAndParityOdd,
	LessThanAndNotGreaterThanOrEqualTo,
	NotLessThanAndGreaterThanOrEqualTo,
	LessThanOrEqualToAndNotGreaterThan,
	NotLessThanOrEqualToAndGreaterThan,
};


class OpCode
{
public:
	OpCode(uint8_t code);

	bool HasModRM() const { return m_HasModRM; }
	bool WValue() const { return m_WValue; }

private:
	bool	m_HasModRM = false;
	bool	m_HasImmediate = false;
	bool	m_HasAltEncoding = false;
	bool	m_HasW = false;

	bool	m_WValue = false;
};
