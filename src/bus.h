#pragma once

#include <cstdint>
#include <array>

#include "CPU6502.h"

class Bus
{
	public:
		Bus();
		~Bus();

		CPU6502 cpu;
		std::array<uint8_t, 64 * 1024> ram;

		void Write(uint16_t addr, uint8_t data);
		uint8_t Read(uint16_t addr, bool readOnly = false); 
};
