#include "Prefix.h"

#include <unordered_map>

#include <iostream>



static std::unordered_map<uint8_t, std::vector<PrefixType>> s_PrefixVector =
{
	// Group 1
	{ 0xF0, { PrefixType::Lock } },
	{ 0xF2, { PrefixType::REPNE_REPNZ } },
	{ 0xF3, { PrefixType::REP_REPE_REPZ } },

	// Group 2 (segment overrides)
	{ 0x2E, { PrefixType::CSOverride, PrefixType::BranchNotTaken } },
	{ 0x36, { PrefixType::SSOverride } },
	{ 0x3E, { PrefixType::DSOverride, PrefixType::BranchTaken } },
	{ 0x26, { PrefixType::ESOverride } },
	{ 0x64, { PrefixType::FSOverride } },
	{ 0x65, { PrefixType::GSOverride } },
	// Group 3
	{ 0x66, { PrefixType::OperandSizeOverride } },
	// Group 4
	{ 0x67, { PrefixType::AddressSizeOverride } },
};


std::string PrefixTypeToString(PrefixType type)
{
	switch (type)
	{
		case PrefixType::None: return "none";
		case PrefixType::Lock: return "Lock";
		case PrefixType::REPNE_REPNZ: return "REPNE/REPNZ";
		case PrefixType::REP_REPE_REPZ: return "REP or REPE/REPZ";
		case PrefixType::CSOverride: return "CS override";
		case PrefixType::DSOverride: return "DS override";
		case PrefixType::ESOverride: return "ES override";
		case PrefixType::FSOverride: return "FS override";
		case PrefixType::GSOverride: return "GS override";
		case PrefixType::SSOverride: return "SS override";
		case PrefixType::BranchTaken: return "Branch taken";
		case PrefixType::BranchNotTaken: return "Branch not taken";
		case PrefixType::AddressSizeOverride: return "Address size override";
		case PrefixType::OperandSizeOverride: return "Operand size override";
	}

	return "Not a valid prefix";
}


Prefix::Prefix(uint8_t code)
{
	for (auto& prefix : s_PrefixVector)
	{
		if (code == prefix.first)
		{
			m_Type = prefix.second.front();

			std::cout << "Prefix found: " << PrefixTypeToString(m_Type) << "\n";

			return;
		}
	}
}
