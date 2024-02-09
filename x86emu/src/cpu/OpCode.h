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
	ImmediateToRegOrMem,
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

	bool IsValid() const { return m_Valid; }

	bool HasNoFlags() const { return m_NoFlags; }
	bool HasModRM() const { return m_HasModRM; }
	bool WValue() const { return m_WValue; }
	bool SValue() const { return m_SValue; }

	bool IsImmediate() const { return m_HasImmediate; }
	bool IsImmediateToRegOrMem() const { return m_IsImmediateToRegOrMem; }

	bool HasAltEncoding() const { return m_HasAltEncoding; }

	bool UseSegmentRegister() const { return m_UseSegmentRegister; }

	void SetName(uint8_t num);
	const std::string Name() const { return m_CodeName; }

private:

	std::string m_CodeName = "";

	bool	m_Valid = false;

	bool	m_HasModRM = false;
	bool	m_HasImmediate = false;
	bool	m_HasAltEncoding = false;
	bool	m_HasW = false;
	bool	m_HasSignExtend = false;

	bool	m_WValue = false;
	bool	m_SValue = false;

	bool	m_UseSegmentRegister = false;

	bool	m_NoFlags = false;

	bool	m_IsImmediateToRegOrMem = false;
};
