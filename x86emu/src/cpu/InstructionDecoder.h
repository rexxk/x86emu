#pragma once

#include "Prefix.h"
#include "Register.h"
#include "Segment.h"

#include <cstdint>
#include <vector>


class InstructionDecoder
{
public:
	struct DecoderResult
	{
		bool ValidCommand;
		std::string CommandLine;
	};

public:
	InstructionDecoder(std::vector<uint8_t>::iterator& byteIterator);

	DecoderResult GetResult() const { return m_DecoderResult; }

private:
	void FindPrefixes(std::vector<uint8_t>::iterator& byteIterator);

private:

	DecoderResult m_DecoderResult;

	std::vector<Prefix> m_Prefixes;

	Segment m_Segment;

	bool m_OperandSizeOverride = false;
	bool m_AddressSizeOverride = false;

	RegisterSize m_RegisterSize = RegisterSize::Bits8;


};