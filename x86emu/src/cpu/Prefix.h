#pragma once

#include <cstdint>


enum class PrefixType
{
	None,

	Lock,
	REPNE_REPNZ,
	REP_REPE_REPZ,

	CSOverride,
	SSOverride,
	DSOverride,
	ESOverride,
	FSOverride,
	GSOverride,

	BranchNotTaken,
	BranchTaken,

	OperandSizeOverride,

	AddressSizeOverride,
};


class Prefix
{
public:
	Prefix(uint8_t code);

	const PrefixType Type() const { return m_Type; }

private:
	PrefixType m_Type = PrefixType::None;
};
