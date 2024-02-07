#include "Segment.h"



Segment::Segment()
	: m_Type(SegmentType::CS)
{

}

void Segment::Override(PrefixType overridePrefix)
{
	switch (overridePrefix)
	{
		case PrefixType::CSOverride: m_Type = SegmentType::CS; return;
		case PrefixType::DSOverride: m_Type = SegmentType::DS; return;
		case PrefixType::ESOverride: m_Type = SegmentType::ES; return;
		case PrefixType::FSOverride: m_Type = SegmentType::FS; return;
		case PrefixType::GSOverride: m_Type = SegmentType::GS; return;
		case PrefixType::SSOverride: m_Type = SegmentType::SS; return;
	}
}


std::string Segment::ToString()
{
	switch (m_Type)
	{
		case SegmentType::CS: return "CS";
		case SegmentType::DS: return "DS";
		case SegmentType::ES: return "ES";
		case SegmentType::FS: return "FS";
		case SegmentType::GS: return "GS";
		case SegmentType::SS: return "SS";
	}

	return "unknown";
}
