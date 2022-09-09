#include "CPU6502.h"
#include "bus.h"
#include <stdint.h>


/* ----------------------------------------- *
	       Constructor && Destructor 
 * ---------------------------------------- */
CPU6502::CPU6502()
{
	using a = CPU6502;
	lookup = 
	{
		{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	};
}
CPU6502::~CPU6502()
{}


/* ----------------------------------------- *
                CPU Essentials
 * ---------------------------------------- */

// Read 8 bits of data from 16-bit memory address in bus
uint8_t CPU6502::_read(uint16_t addr)
{
	return bus->Read(addr, false);	
}

// Write 8 bits of data in bus at location of the the supplied 16-bit memory address
void CPU6502::_write(uint16_t addr, uint8_t data)
{
	bus->Write(addr, data);
}


/* ----------------------------------------- *
                Flag functions
 * ---------------------------------------- */

// Returns the value of a specific bit of the status register
uint8_t CPU6502::_getFlag(FLAGS6502 f)
{
	return ((status & f) > 0) ? 1 : 0;
}

// Sets or clears a specific bit of the status register
void CPU6502::_setFlag(FLAGS6502 f, bool v)
{
	if (v)
		status |= f;
	else
		status &= ~f;
}


/* ----------------------------------------- *
              Action Mechanisms
 * ---------------------------------------- */
// Executes one cycle of the clock
/* Currently, each instruction is executed all at once 
during a single clock cycle. That's not how a 6502 works. */
void CPU6502::TickClock()
{
	// TODO Make emulation clock accurate
	if (cyclesLeft == 0)
	{
		opcode = _read(pc);
		pc++;

		cyclesLeft = lookup[opcode].cycles;

		uint8_t needs_extra_cycle1 = (this->*lookup[opcode].addrmode)();
		uint8_t needs_extra_cycle2 = (this->*lookup[opcode].operate)();
		
		cyclesLeft += (needs_extra_cycle1 & needs_extra_cycle2);
	}
	cyclesLeft--;
}


/* ----------------------------------------- *
               "Addressing Modes"
        What is the source of the data
	      used in this instruction? 

http://www.emulator101.com/6502-addressing-modes.html
https://wiki.cdot.senecacollege.ca/wiki/6502_Addressing_Modes
* ---------------------------------------- */

// Note 1: Indexing is good to traverse contiguous blocks of memory, such as arrays.
// Note 2: The notation is little endian.

/* "IMPLIED"
The data is implied by the operation.
i.e. No data as part of the instruction.
But it MAY be operating on the accumulator.
*/
uint8_t CPU6502::IMP()
{
	fetched = a;
	return 0;
}

/* "IMMEDIATE"
The data is supplied as part of the instruction i.e. the next byte.
Data is taken from the byte following the opcode i.e. the next byte
*/
uint8_t CPU6502::IMM()
{
	addrAbs = pc;
	pc++;
	return 0;
}

/* "ZERO PAGE" 
An 8-bit address is provided within the zero page.
This is like an absolute address, but since the argument is only one byte,
the CPU does not have to spend an additional cycle to fetch high byte.
*/
uint8_t CPU6502::ZP0()
{
	addrAbs = _read(pc);
	pc++;
	addrAbs &= 0x00FF; // Set page to zero and set high bytes to the offset
	return 0;
}

/* "ZERO PAGE INDEXED (X)" 
An 8-bit address is provided, to which the X register is added
(without carry - if the addition overflows, the address wraps around within the zero page).
*/
uint8_t CPU6502::ZPX()
{
	addrAbs = (_read(pc) + x);
	pc++;
	addrAbs &= 0x00FF; // Set page to zero and set high bytes to the offset
	return 0;
}

/* "ZERO PAGE INDEXED (Y)" 
An 8-bit address is provided, to which the Y register is added
(without carry - if the addition overflows, the address wraps around within the zero page).
*/
uint8_t CPU6502::ZPY()
{
	addrAbs = (_read(pc) + y);
	pc++;
	addrAbs &= 0x00FF; // Set page to zero and set high bytes to the offset
	return 0;
}

/* "ABSOLUTE" 
Data is accessed using 16-bit address specified as a constant
In the total 3 bytes, the full address is specified in the next 2 bytes.
*/
uint8_t CPU6502::ABS()
{
	uint16_t lo = _read(pc); // Read low byte
	pc++;
	uint16_t hi = _read(pc); // Read hi byte
	pc++;

	addrAbs = (hi << 8) | lo; // Push them to a two byte space
	return 0;
}

/* "ABSOLUTE INDEXED (X)" 
Data is accessed using 16-bit address specified as a constant
to which the value of the X register is added (with carry).
In the total 3 bytes, the full address is specified in the next 2 bytes.
If overflow from lo byte to hi byte happens, an additional cycle will be needed.
*/
uint8_t CPU6502::ABX()
{
	uint16_t lo = _read(pc); // Read low byte
	pc++;
	uint16_t hi = _read(pc); // Read hi byte
	pc++;

	addrAbs = (hi << 8) | lo; // Push them to a two byte space
	addrAbs += x; // The low byte beyond the page boundary (overflow)

	// See if the hi byte has changed.
	// Because if it has, it means the low byte carried a bit to the high byte
	// And thus, the processor may need an additional cycle
	if ((addrAbs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

/* "ABSOLUTE INDEXED (X)" 
Data is accessed using 16-bit address specified as a constant
to which the value of the Y register is added (with carry).
In the total 3 bytes, the full address is specified in the next 2 bytes.
If overflow from lo byte to hi byte happens, an additional cycle will be needed.
*/
uint8_t CPU6502::ABY()
{
	uint16_t lo = _read(pc); // Read low byte
	pc++;
	uint16_t hi = _read(pc); // Read hi byte
	pc++;

	addrAbs = (hi << 8) | lo; // Push them to a two byte space
	addrAbs += y; // The low byte beyond the page boundary (overflow)

	// See if the hi byte has changed.
	// Because if it has, it means the low byte carried a bit to the high byte
	// And thus, the processor may need an additional cycle
	if ((addrAbs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

/* "INDIRECT ADDRESSING"
The 6502 way of using pointers.
The 16-bit address of the pointer is given in the two bytes following the opcode.
This implementation simulates a real hardware bug.
*/
uint8_t CPU6502::IND()
{
	uint16_t ptr_lo = _read(pc); // Read low byte
	pc++;
	uint16_t ptr_hi = _read(pc); // Read hi byte
	pc++;

	uint16_t ptr = (ptr_hi << 8) | ptr_lo; // Push them to a two byte space

	/* START INTENDED BUG: Page boundary hardware bug
	Explanation: An indirect JMP (xxFF) will fail because the MSB will be fetched from address xx00 instead of page xx+1.
	Read more at:
	- https://atariwiki.org/wiki/Wiki.jsp?page=6502%20bugs
	- https://en.wikipedia.org/wiki/MOS_Technology_6502
	- https://www.liquisearch.com/mos_technology_6502/bugs_and_quirks
	*/
	if (ptr_lo == 0x00FF) 
	{

		addrAbs = (_read(ptr & 0xFF00) << 8) | _read(ptr + 0); // Read actual address and perform same as above
	}
	else // Behave normally
	{
		addrAbs = (_read(ptr + 1) << 8) | _read(ptr + 0); // Read actual address and perform same as above
	}
	/* END INTENDED BUG */

	return 0;
}		

/* "INDIRECT (ZERO-PAGE) INDEXED (X)"
An 8-bit zero-page address and the X register are added,
without carry (if the addition overflows, the address wraps around within page 0).
The resulting address is used as a pointer to the data being accessed.
Note that, effectively, this makes the X register an index into a list of pointers.
Also note that pointers are two bytes long, so the X register should be an even number when accessing a list of pointers
(otherwise you'll get half of one pointer and half of another).
*/
uint8_t CPU6502::IZX()
{
	uint16_t t = _read(pc);
	pc++;

	uint16_t lo = _read((uint16_t) (t + (uint16_t)x) & 0x00FF);
	uint16_t hi = _read((uint16_t) (t + (uint16_t)x + 1) & 0x00FF);
	
	addrAbs = (hi << 8) | lo; // Push them to a two byte space

	return 0;
}	

/* "INDIRECT (ZERO-PAGE) INDEXED (Y)"
An 8-bit address identifies a pointer.
The value of the Y register is added to the address contained in the pointer.
Effectively, the pointer is the base address and the Y register is an index past that base address.
*/
uint8_t CPU6502::IZY()
{
	uint16_t t = _read(pc);
	pc++;

	uint16_t lo = _read(t & 0x00FF);
	uint16_t hi = _read((t + 1) & 0x00FF);
	
	addrAbs = (hi << 8) | lo; // Push them to a two byte space
	addrAbs += y;

	if ((addrAbs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

/* "RELATIVE"
An 8-bit (2-byte) signed offset is provided.
This value is added to the program counter (PC) to find the effective address.
*/
uint8_t CPU6502::REL()
{
	addrRel = _read(pc);
	pc++;

	/* Check bit 7 of the byte i.e. its sign
	If it is one, the high byte of the relative address will be all ones.
	This is to ensure the arithmetics of adding relative address works out later on.
	*/
	if (addrRel & 0x80) 
		addrRel |= 0xFF00;
	return 0;
}


/* ----------------------------------------- *
                    Others
 * ---------------------------------------- */

// A setter for the bus pointer
void CPU6502::ConnectBus(Bus *n)
{
	bus = n;
}
