#pragma once

#include "Prefix.h"

#include <string>

enum class SegmentType
{
	CS = 0,
	DS,
	ES,
	FS,
	GS,
	SS,
};


class Segment
{
public:
	Segment();

	void Override(PrefixType overridePrefix);

	const SegmentType Type() const { return m_Type; }

	std::string ToString();

private:
	SegmentType m_Type;
};
