#include "Memory.h"

#include <iostream>


Memory::Memory()
{

}

void Memory::Add(uint64_t startAddress, uint64_t size)
{
	MemoryBlockSpecification blockSpecification = {};
	blockSpecification.StartAddress = startAddress;
	blockSpecification.Size = size;

	CheckOverlap(blockSpecification);

	blockSpecification.Data.resize(blockSpecification.Size);

	m_Blocks.push_back(blockSpecification);

}

void Memory::Add(uint64_t startAddress, const std::vector<uint8_t>& data)
{
	MemoryBlockSpecification blockSpecification = {};
	blockSpecification.StartAddress = startAddress;
	blockSpecification.Size = (uint64_t)data.size();

	CheckOverlap(blockSpecification);

	blockSpecification.Data.resize(blockSpecification.Size);
	std::memcpy(blockSpecification.Data.data(), data.data(), blockSpecification.Size);

	m_Blocks.push_back(blockSpecification);
}

void Memory::CheckOverlap(MemoryBlockSpecification& specification)
{
	for (auto& blockSpec : m_Blocks)
	{
		if (specification.StartAddress > blockSpec.StartAddress && specification.StartAddress < (blockSpec.StartAddress + blockSpec.Size))
		{
			specification.StartAddress = blockSpec.StartAddress + blockSpec.Size;
		}
			
		if ((specification.StartAddress + specification.Size) < (blockSpec.StartAddress + blockSpec.Size))
		{
			specification.Size = blockSpec.StartAddress - specification.StartAddress;
		}
	}
}

void Memory::PrintMemoryMap()
{
	std::cout << "Memory map (" << (uint32_t)m_Blocks.size() << " entries): \n";
	
	for (auto& blockSpec : m_Blocks)
	{
		std::cout << " " << std::hex << blockSpec.StartAddress << " : " << blockSpec.Size << std::dec << "\n";
	}

	std::cout << "\n";
}
