#include "EffectiveAddress.h"



EffectiveAddress::EffectiveAddress(uint8_t mode, uint8_t rmValue)
{
	switch (mode)
	{
		case 0:
		{
			switch (rmValue)
			{
				case 0: m_Type = EffectiveAddressType::BXpSI; break;
				case 1: m_Type = EffectiveAddressType::BXpDI; break;
				case 2: m_Type = EffectiveAddressType::BPpSI; break;
				case 3: m_Type = EffectiveAddressType::BPpDI; break;
				case 4: m_Type = EffectiveAddressType::SI; break;
				case 5: m_Type = EffectiveAddressType::DI; break;
				case 6: m_Type = EffectiveAddressType::disp16; break;
				case 7: m_Type = EffectiveAddressType::BX; break;
			}

			break;
		}

		case 1:
		{
			switch (rmValue)
			{
				case 0: m_Type = EffectiveAddressType::BXpSIpdisp8; break;
				case 1: m_Type = EffectiveAddressType::BXpDIpdisp8; break;
				case 2: m_Type = EffectiveAddressType::BPpSIpdisp8; break;
				case 3: m_Type = EffectiveAddressType::BPpDIpdisp8; break;
				case 4: m_Type = EffectiveAddressType::SIpdisp8; break;
				case 5: m_Type = EffectiveAddressType::DIpdisp8; break;
				case 6: m_Type = EffectiveAddressType::BPpdisp8; break;
				case 7: m_Type = EffectiveAddressType::BXpdisp8; break;
			}

			break;
		}

		case 2:
		{
			switch (rmValue)
			{
				case 0: m_Type = EffectiveAddressType::BXpSIpdisp16; break;
				case 1: m_Type = EffectiveAddressType::BXpDIpdisp16; break;
				case 2: m_Type = EffectiveAddressType::BPpSIpdisp16; break;
				case 3: m_Type = EffectiveAddressType::BPpDIpdisp16; break;
				case 4: m_Type = EffectiveAddressType::SIpdisp16; break;
				case 5: m_Type = EffectiveAddressType::DIpdisp16; break;
				case 6: m_Type = EffectiveAddressType::BPpdisp16; break;
				case 7: m_Type = EffectiveAddressType::BXpdisp16; break;
			}

			break;
		}
	}
}


std::string EffectiveAddress::ToString()
{
	switch (m_Type)
	{
		case EffectiveAddressType::BXpSI: return "BX+SI";
		case EffectiveAddressType::BXpDI: return "BX+DI";
		case EffectiveAddressType::BPpSI: return "BP+SI";
		case EffectiveAddressType::BPpDI: return "BP+DI";
		case EffectiveAddressType::SI: return "SI";
		case EffectiveAddressType::DI: return "DI";
		case EffectiveAddressType::disp16: "disp16";
		case EffectiveAddressType::BX: return "BX";
		case EffectiveAddressType::BXpSIpdisp8: return "BX+SI";
		case EffectiveAddressType::BXpDIpdisp8: return "BX+DI";
		case EffectiveAddressType::BPpSIpdisp8: return "BP+SI";
		case EffectiveAddressType::BPpDIpdisp8: return "BP+DI";
		case EffectiveAddressType::SIpdisp8: return "SI";
		case EffectiveAddressType::DIpdisp8: return "DI";
		case EffectiveAddressType::BPpdisp8: return "BP";
		case EffectiveAddressType::BXpdisp8: return "BX";
		case EffectiveAddressType::BXpSIpdisp16: return "BX+SI";
		case EffectiveAddressType::BXpDIpdisp16: return "BX+DI";
		case EffectiveAddressType::BPpSIpdisp16: return "BP+SI";
		case EffectiveAddressType::BPpDIpdisp16: return "BP+DI";
		case EffectiveAddressType::SIpdisp16: return "SI";
		case EffectiveAddressType::DIpdisp16: return "DI";
		case EffectiveAddressType::BPpdisp16: return "BP";
		case EffectiveAddressType::BXpdisp16: return "BX";
	}

	return "unknown mode";
}
