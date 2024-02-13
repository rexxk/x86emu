#pragma once

#include <cstdint>
#include <vector>


class Memory
{
public:
	struct MemoryBlockSpecification
	{
		uint64_t StartAddress;
		uint64_t Size;

		std::vector<uint8_t> Data;
	};

public:
	Memory();

	void Add(uint64_t startAddress, uint64_t size);
	void Add(uint64_t startAddress, const std::vector<uint8_t>& data);

	void PrintMemoryMap();

private:
	void CheckOverlap(MemoryBlockSpecification& specification);

private:
	std::vector<MemoryBlockSpecification> m_Blocks;
};
