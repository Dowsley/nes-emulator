#include "bus.h"

Bus::Bus()
{
	// Clear ram contents just in case
	for (auto &i : ram) i = 0x00;

	cpu.ConnectBus(this);
}

Bus::~Bus()
{
}

void Bus::Write(uint16_t addr, uint8_t data)
{
	if (addr >= 0x0000 && addr <= 0xFFFF)
		ram[addr] = data;
}

uint8_t Bus::Read(uint16_t addr, bool readOnly) 
{
	if (addr >= 0x0000 && addr <= 0xFFFF)
		return ram[addr];
	return 0x00;
}
