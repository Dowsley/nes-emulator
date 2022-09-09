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

/* Fetches data from address
After any opcode except "Implied" - for it does not need it.
It is used by opcode functions.
*/
uint8_t CPU6502::Fetch()
{
	if (!(lookup[opcode].addrmode == &CPU6502::IMP))
		fetched = _read(addrAbs);
	return fetched;
}

/* Reconfigures the CPU into a known state.
Efectively an interrupt.
*/
void CPU6502::Reset()
{
	a = 0;
	x = 0;
	y = 0;
	stkp = 0xFD;
	status = 0x00 | U;

	// Hardcoded location in the hardware to read the address.
	// This location holds data that the programmer will store.
	// So it's a sort of mutual agreement.
	addrAbs = 0xFFFC; 
	uint16_t lo = _read(addrAbs + 0);
	uint16_t hi = _read(addrAbs + 1);

	pc = (hi << 8) | lo;

	addrRel = 0x0000;
	addrAbs = 0x0000;
	fetched = 0x00;
	
	cyclesLeft = 8; // Hardcoded by choice. Resets take time.
}

/* Writes data to the stack.
Will be ignored if the disable interrupt bit is active.
*/
void CPU6502::InterruptRequest()
{
	if (_getFlag(I) == 0)
	{
		// Two writes in the stack because its 16 bits
		_write(0x0100 + stkp, (pc << 8) & 0x00FF);
		stkp--;
		_write(0x0100 + stkp, pc & 0x00FF);
		stkp--;

		// Bits to indicate that an interrupt has occured
		_setFlag(B, 0);
		_setFlag(U, 1);
		_setFlag(I, 1);
		// Status register to the stack as well
		_write(0x0100 + stkp, status);
		stkp--;

		// Hardcoded location in the hardware to read the address.
		// This location holds data that the programmer will store.
		// So it's a sort of mutual agreement.
		addrAbs = 0xFFFE;
		
		uint16_t lo = _read(addrAbs + 0);
		uint16_t hi = _read(addrAbs + 1);

		pc = (hi << 8) | lo;

		cyclesLeft = 7; // Hardcoded by choice. Resets take time.
	}
}

/* Writes data to the stack.
Except it can't be stopped.
Will be ignored if the disable interrupt bit is active.
*/
void CPU6502::NMInterruptRequest()
{
	// Two writes in the stack because its 16 bits
	_write(0x0100 + stkp, (pc << 8) & 0x00FF);
	stkp--;
	_write(0x0100 + stkp, pc & 0x00FF);
	stkp--;

	// Bits to indicate that an interrupt has occured
	_setFlag(B, 0);
	_setFlag(U, 1);
	_setFlag(I, 1);
	// Status register to the stack as well
	_write(0x0100 + stkp, status);
	stkp--;

	// Hardcoded location in the hardware to read the address.
	// This location holds data that the programmer will store.
	// So it's a sort of mutual agreement.
	addrAbs = 0xFFFA;
	
	uint16_t lo = _read(addrAbs + 0);
	uint16_t hi = _read(addrAbs + 1);

	pc = (hi << 8) | lo;

	cyclesLeft = 7; // Hardcoded by choice. Resets take time.
}


/* ----------------------------------------- *
               "Addressing Modes"
        What is the source of the data
	      used in this instruction? 

In this context, they setup and populate
the address that the operation will be performed upon.

Their return indicates if the whole instruction is candidate for an additional cycle.
Note 1: Indexing is good to traverse contiguous blocks of memory, such as arrays.
Note 2: The notation is little endian.

http://www.emulator101.com/6502-addressing-modes.html
https://wiki.cdot.senecacollege.ca/wiki/6502_Addressing_Modes
* ---------------------------------------- */


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
the CPU does not have to spend an additional cycle to Fetch high byte.
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
         "INSTRUCTIONS" OR "OPCODES"
        
		In this emulator an OPCODE is
	   essentially an instruction, that
	  will execute after the addrmode does.

It will perform the necessary operations upon the
address that was set up and populated by the address
mode function that executed shortly before.

Their return indicates if the whole instruction is candidate for an additional cycle.

Main source: http://archive.6502.org/datasheets/rockwell_r65c00_microprocessors.pdf
Also refer to:
https://www.pagetable.com/c64ref/6502/?tab=2
https://wiki.cdot.senecacollege.ca/wiki/6502_Instructions_-_Introduction
 * ---------------------------------------- */


/**********/
/*  LOAD  */
/**********/

/*
// "Load The Accumulator" or "Load Accumulator with Memory"
Operation: A = M
Flags Out: N, Z
*/
uint8_t CPU6502::LDA()
{
	Fetch();
	a = fetched;
	_setFlag(Z, a == 0x00);
	_setFlag(N, a & 0x80);
	return 1;
}

/* Load The X Register" or "Load Index Register X From Memory"
Operation:    X = M
Flags Out:   N, Z
*/
uint8_t CPU6502::LDX()
{
	Fetch();
	x = fetched;
	_setFlag(Z, x == 0x00);
	_setFlag(N, x & 0x80);
	return 1;
}

/* "Load The Y Register" or "Load Index Register Y From Memory"
Operation:    Y = M
Flags Out:   N, Z
*/
uint8_t CPU6502::LDY()
{
	Fetch();
	y = fetched;
	_setFlag(Z, y == 0x00);
	_setFlag(N, y & 0x80);
	return 1;
}

/* "Store Accumulator at Address" or "Store Accumulator in Memory"
Operation:    M = A
*/
uint8_t CPU6502::STA()
{
	_write(addrAbs, a);
	return 0;
}

/* Store X Register at Address" or "Store Index Register X In Memory"
Operation:    M = X
*/
uint8_t CPU6502::STX()
{
	_write(addrAbs, x);
	return 0;
}

/* "Store Y Register at Address" or "Store Index Register X In Memory"
// Operation:    M = Y
*/
uint8_t CPU6502::STY()
{
	_write(addrAbs, y);
	return 0;
}


/**********/
/*  TRANS  */
/**********/

/* "Transfer Accumulator to X Register" 
Operation:    X = A
Flags Out:   N, Z
*/
uint8_t CPU6502::TAX()
{
	x = a;
	_setFlag(Z, x == 0x00);
	_setFlag(N, x & 0x80);
	return 0;
}


/* "Transfer Accumulator to Y Register"
Operation:    Y = A
Flags Out:   N, Z
*/
uint8_t CPU6502::TAY()
{
	y = a;
	_setFlag(Z, y == 0x00);
	_setFlag(N, y & 0x80);
	return 0;
}


/* "Transfer Stack Pointer to X Register"
Operation:    X = stack pointer
Flags Out:   N, Z
*/
uint8_t CPU6502::TSX()
{
	x = stkp;
	_setFlag(Z, x == 0x00);
	_setFlag(N, x & 0x80);
	return 0;
}


/* "Transfer X Register to Accumulator"
Operation:    A = X
Flags Out:   N, Z
*/
uint8_t CPU6502::TXA()
{
	a = x;
	_setFlag(Z, a == 0x00);
	_setFlag(N, a & 0x80);
	return 0;
}


/* "Transfer X Register to Stack Pointer"
Operation:    stack pointer = X
*/
uint8_t CPU6502::TXS()
{
	stkp = x;
	return 0;
}


/* "Transfer Y Register to Accumulator"
Operation:    A = Y
Flags Out:   N, Z
*/
uint8_t CPU6502::TYA()
{
	a = y;
	_setFlag(Z, a == 0x00);
	_setFlag(N, a & 0x80);
	return 0;
}


/***********/
/*  ARITH  */
/***********/

/* "ADDITION" or "Add Memory to Accumulator with Carry"
Operation: A + M + C → A, C
NOTE: On the MOS 6502, in decimal mode, the N, V and Z flags are not consistent with the decimal result.
*/
uint8_t CPU6502::ADC()
{
	Fetch();

	// Use 16 bits to store the possible result of overflow on bit 8 (9th bit)
	tmp = (uint16_t)a + (uint16_t)fetched + (uint16_t)_getFlag(C);
	_setFlag(C, tmp > 255);
	_setFlag(Z, (tmp & 0x00FF) == 0);
	_setFlag(N, tmp & 0x80); // Most significant bit

	// The overflow flag follows a logic deduction described by javidx9.
	// Refer to the file in path `docs/adc_overflow_condition.png` 
	_setFlag(V, (~((uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^ (uint16_t)tmp)) & 0x0080);
	
	// Load the result into the accumulator: It's 8-bit
	a = tmp & 0x00FF;
	
	// Candidate for extra cycle.
	return 1;
}

/* "SUBTRACTION" or "Subtract Memory from Accumulator with Borrow"
Operation: A - M - ~C → A
NOTE: On the MOS 6502, in decimal mode, the N, V and Z flags are not consistent with the decimal result.
*/
uint8_t CPU6502::SBC()
{
	Fetch();

	// It's just like ADC, except the fetched value (bottom 8 bits, remember) needs to be inverted to be negative.
	uint16_t value = ((uint16_t)fetched ^ 0x00FF); 

	// Use 16 bits to store the possible result of overflow on bit 8 (9th bit)
	tmp = (uint16_t)a + value + (uint16_t)_getFlag(C);
	_setFlag(C, tmp > 255);
	_setFlag(Z, (tmp & 0x00FF) == 0);
	_setFlag(N, tmp & 0x80); // Most significant bit

	// The overflow flag follows an adaptation of the logic deduction described by javidx9.
	// Refer to the file in path `docs/adc_overflow_condition.png` 
	_setFlag(V, ((uint16_t)a ^ tmp) & (value ^ tmp) & 0x0080);
	
	// Load the result into the accumulator: It's 8-bit
	a = tmp & 0x00FF;
	
	// Candidate for extra cycle.
	return 1;
}


/* "Compare Accumulator"
Operation:    C <- A >= M      Z <- (A - M) == 0
Flags Out:   N, C, Z
*/
uint8_t CPU6502::CMP()
{
	Fetch();
	tmp = (uint16_t)a - (uint16_t)fetched;
	_setFlag(C, a >= fetched);
	_setFlag(Z, (tmp & 0x00FF) == 0x0000);
	_setFlag(N, tmp & 0x0080);
	return 1;
}


/* "Compare X Register"
Operation:    C <- X >= M      Z <- (X - M) == 0
Flags Out:   N, C, Z
*/
uint8_t CPU6502::CPX()
{
	Fetch();
	tmp = (uint16_t)x - (uint16_t)fetched;
	_setFlag(C, x >= fetched);
	_setFlag(Z, (tmp & 0x00FF) == 0x0000);
	_setFlag(N, tmp & 0x0080);
	return 0;
}


/* "Compare Y Register"
Operation:    C <- Y >= M      Z <- (Y - M) == 0
Flags Out:   N, C, Z
*/
uint8_t CPU6502::CPY()
{
	Fetch();
	tmp = (uint16_t)y - (uint16_t)fetched;
	_setFlag(C, y >= fetched);
	_setFlag(Z, (tmp & 0x00FF) == 0x0000);
	_setFlag(N, tmp & 0x0080);
	return 0;
}


/***********/
/*   INC   */
/***********/


/* "Decrement Value at Memory Location"
Operation:    M = M - 1
Flags Out:   N, Z
*/
uint8_t CPU6502::DEC()
{
	Fetch();
	tmp = fetched - 1;
	_write(addrAbs, tmp & 0x00FF);
	_setFlag(Z, (tmp & 0x00FF) == 0x0000);
	_setFlag(N, tmp & 0x0080);
	return 0;
}


/* "Decrement X Register"
Operation:    X = X - 1
Flags Out:   N, Z
*/
uint8_t CPU6502::DEX()
{
	x--;
	_setFlag(Z, x == 0x00);
	_setFlag(N, x & 0x80);
	return 0;
}


/* "Decrement Y Register"
Operation:    Y = Y - 1
Flags Out:   N, Z
*/
uint8_t CPU6502::DEY()
{
	y--;
	_setFlag(Z, y == 0x00);
	_setFlag(N, y & 0x80);
	return 0;
}


/* "Increment Value at Memory Location"
Operation:    M = M + 1
Flags Out:   N, Z
*/
uint8_t CPU6502::INC()
{
	Fetch();
	tmp = fetched + 1;
	_write(addrAbs, tmp & 0x00FF);
	_setFlag(Z, (tmp & 0x00FF) == 0x0000);
	_setFlag(N, tmp & 0x0080);
	return 0;
}


/* "Increment X Register"
Operation:    X = X + 1
Flags Out:   N, Z
*/
uint8_t CPU6502::INX()
{
	x++;
	_setFlag(Z, x == 0x00);
	_setFlag(N, x & 0x80);
	return 0;
}


/* "Increment Y Register"
Operation:    Y = Y + 1
Flags Out:   N, Z
*/
uint8_t CPU6502::INY()
{
	y++;
	_setFlag(Z, y == 0x00);
	_setFlag(N, y & 0x80);
	return 0;
}


/***********/
/*  LOGIC  */
/***********/

/* "AND"
Operation: A ∧ M → A
Flags Out: N, Z

Tranfers the accumulator and memory to the adder which performs
a bit-by-bit AND operation and stores the result back in the accumulator.
- affects the accumulator;
- sets the zero flag if the result in the accumulator is 0
	- otherwise resets the zero flag;
- sets the negative flag if the result in the accumulator has bit 7 on,
	- otherwise resets the negative flag.
*/
uint8_t CPU6502::AND()
{
	Fetch();
	a = a & fetched;
	_setFlag(Z, a == 0x00);
	_setFlag(N, a & 0x80); // Remember, bit 7 is the sign
	return 1;
}

/* "Test Bits in Memory with Accumulator"
Operation: A ∧ M, M7 → N, M6 → V
Flags Out: N, Z, V

Performs an AND between a memory location and the accumulator
but does not store the result of the AND into the accumulator.
*/
uint8_t CPU6502::BIT()
{
	Fetch();
	tmp = a & fetched;
	_setFlag(Z, (tmp & 0x00FF) == 0x00);
	_setFlag(N, fetched & (1 << 7));
	_setFlag(V, fetched & (1 << 6));
	return 0;
}

/* "Bitwise Logic XOR"
Operation:    A = A xor M
Flags Out:   N, Z
*/
uint8_t CPU6502::EOR()
{
	Fetch();
	a = a ^ fetched;	
	_setFlag(Z, a == 0x00);
	_setFlag(N, a & 0x80);
	return 1;
}

/* "Bitwise Logic OR"
Operation:    A = A | M
Flags Out:   N, Z
*/
uint8_t CPU6502::ORA()
{
	Fetch();
	a = a | fetched;
	_setFlag(Z, a == 0x00);
	_setFlag(N, a & 0x80);
	return 1;
}

/*************/
/*  CONTROL  */
/*************/

/* "Return From Interrupt"
Operation: P↑ PC↑

By virtue of the interrupt having stored this data before executing
the instruction and the fact that the RTI reinitializes the 
microprocessor to the same state as when it was interrupted, the 
combination of interrupt plus RTI allows truly reentrant coding.
*/
uint8_t CPU6502::RTI()
{
	stkp++;
	status = _read(0x0100 + stkp);
	status &= ~B; // Clear that bit
	status &= ~U; // Idem

	stkp++;
	pc = (uint16_t)_read(0x0100 + stkp);
	stkp++;
	pc |= (uint16_t)_read(0x0100 + stkp) << 8;
	return 0;
}


/* "Break"
Operation:    Program Sourced Interrupt
*/
uint8_t CPU6502::BRK()
{
	pc++;
	
	_setFlag(I, 1);
	_write(0x0100 + stkp, (pc >> 8) & 0x00FF);
	stkp--;
	_write(0x0100 + stkp, pc & 0x00FF);
	stkp--;

	_setFlag(B, 1);
	_write(0x0100 + stkp, status);
	stkp--;
	_setFlag(B, 0);

	pc = (uint16_t)_read(0xFFFE) | ((uint16_t)_read(0xFFFF) << 8);
	return 0;
}


/* "Jump To Location"
Operation:    pc = address
*/
uint8_t CPU6502::JMP()
{
	pc = addrAbs;
	return 0;
}


/* "Jump To Sub-Routine"
Operation:    Push current pc to stack, pc = address
*/
uint8_t CPU6502::JSR()
{
	pc--;

	_write(0x0100 + stkp, (pc >> 8) & 0x00FF);
	stkp--;
	_write(0x0100 + stkp, pc & 0x00FF);
	stkp--;

	pc = addrAbs;
	return 0;
}


/* "Return From Subroutme"
Operation: PC↑, PC + 1 → PC
*/
uint8_t CPU6502::RTS()
{
	stkp++;
	pc = (uint16_t)_read(0x0100 + stkp);
	stkp++;
	pc |= (uint16_t)_read(0x0100 + stkp) << 8;
	
	pc++;
	return 0;
}


/***********/
/*  STACK  */
/***********/
// The hardcoded base location in the MOS 6502 is 0x0100

/* "Push Accumulator On Stack"
Operation: A↓
*/
uint8_t CPU6502::PHA()
{
	_write(0x0100 + stkp, a);
	stkp--;
	return 0;
}


/* "Pull Accumulator From Stack"
Operation: A↑
*/
uint8_t CPU6502::PLA()
{
	stkp++;
	a = _read(0x0100 + stkp);
	_setFlag(Z, a == 0x00);
	_setFlag(N, a & 0x80);
	return 0;
}


/* "Push Status Register to Stack"
Operation: status -> stack
NOTE: Break flag is set to 1 before push
*/
uint8_t CPU6502::PHP()
{
	_write(0x0100 + stkp, status | B | U);
	_setFlag(B, 0);
	_setFlag(U, 0);
	stkp--;
	return 0;
}


/* "Pop Status Register off Stack"
Operation:    Status <- stack
*/
uint8_t CPU6502::PLP()
{
	stkp++;
	status = _read(0x0100 + stkp);
	_setFlag(U, 1);
	return 0;
}


/************/
/*  SHIFT  */
/************/

/* "Arithmetic Shift Left"
Operation:    A = C <- (A << 1) <- 0
Flags Out:   N, Z, C
*/
uint8_t CPU6502::ASL()
{
	Fetch();
	tmp = (uint16_t)fetched << 1;
	_setFlag(C, (tmp & 0xFF00) > 0);
	_setFlag(Z, (tmp & 0x00FF) == 0x00);
	_setFlag(N, tmp & 0x80);
	if (lookup[opcode].addrmode == &CPU6502::IMP)
		a = tmp & 0x00FF;
	else
		_write(addrAbs, tmp & 0x00FF);
	return 0;
}

/* "Logical Shift Right"
Operation:  0 → /M7...M0/ → C
Flags Out:   N, Z, C
*/
uint8_t CPU6502::LSR()
{
	Fetch();
	_setFlag(C, fetched & 0x0001);
	tmp = fetched >> 1;	
	_setFlag(Z, (tmp & 0x00FF) == 0x0000);
	_setFlag(N, tmp & 0x0080);
	if (lookup[opcode].addrmode == &CPU6502::IMP)
		a = tmp & 0x00FF;
	else
		_write(addrAbs, tmp & 0x00FF);
	return 0;
}

/* "Rotate Left"
Operation: C ← /M7...M0/ ← C
Flags Out:   N, Z, C
*/
uint8_t CPU6502::ROL()
{
	Fetch();
	tmp = (uint16_t)(fetched << 1) | _getFlag(C);
	_setFlag(C, tmp & 0xFF00);
	_setFlag(Z, (tmp & 0x00FF) == 0x0000);
	_setFlag(N, tmp & 0x0080);
	if (lookup[opcode].addrmode == &CPU6502::IMP)
		a = tmp & 0x00FF;
	else
		_write(addrAbs, tmp & 0x00FF);
	return 0;
}

/* "Rotate Right"
Operation: C → /M7...M0/ → C
Flags Out:   N, Z, C
*/
uint8_t CPU6502::ROR()
{
	Fetch();
	tmp = (uint16_t)(_getFlag(C) << 7) | (fetched >> 1);
	_setFlag(C, fetched & 0x01);
	_setFlag(Z, (tmp & 0x00FF) == 0x00);
	_setFlag(N, tmp & 0x0080);
	if (lookup[opcode].addrmode == &CPU6502::IMP)
		a = tmp & 0x00FF;
	else
		_write(addrAbs, tmp & 0x00FF);
	return 0;
}


/************/
/*  BRANCH  */
/************/
// They usually alter the number of cycles left directly.
// If their branching condition is met an extra cycle will be needed.
// A further cycle penalty occurs if the branch needs to cross a page boundary.

/* "Branch on Carry Set"
Operation: if C == 1 -> pc = address
*/
uint8_t CPU6502::BCS()
{
	if (_getFlag(C) == 1)
	{
		cyclesLeft++;
		addrAbs = pc + addrRel; // used as a tmporary for checking

		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) // Does it want to cross a page boundary?
			cyclesLeft++;
		pc = addrAbs;
	}
	return 0;
}

/* "Branch on Carry Clear"
Operation: if C == 0 -> pc = address
*/
uint8_t CPU6502::BCC()
{
	if (_getFlag(C) == 0)
	{
		cyclesLeft++;
		addrAbs = pc + addrRel; // used as a tmporary for checking

		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) // Does it want to cross a page boundary?
			cyclesLeft++;
		pc = addrAbs;
	}
	return 0;
}

/* "Branch if Equal" or "Branch on Result Zero"
Operation: if Z == 1 -> pc = address
*/
uint8_t CPU6502::BEQ()
{
	if (_getFlag(Z) == 1)
	{
		cyclesLeft++;
		addrAbs = pc + addrRel; // used as a tmporary for checking

		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) // Does it want to cross a page boundary?
			cyclesLeft++;
		pc = addrAbs;
	}
	return 0;
}

/* "Branch if Negative" or "Branch on Result Minus"
Operation: if N == 1 -> pc = address
*/
uint8_t CPU6502::BMI()
{
	if (_getFlag(N) == 1)
	{
		cyclesLeft++;
		addrAbs = pc + addrRel; // used as a tmporary for checking

		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) // Does it want to cross a page boundary?
			cyclesLeft++;
		pc = addrAbs;
	}
	return 0;
}

/* "Branch if Not Equal" or "Branch on Result Not Zero"
Operation: if Z == 0 -> pc = address
*/
uint8_t CPU6502::BNE()
{
	if (_getFlag(Z) == 0)
	{
		cyclesLeft++;
		addrAbs = pc + addrRel; // used as a tmporary for checking

		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) // Does it want to cross a page boundary?
			cyclesLeft++;
		pc = addrAbs;
	}
	return 0;
}

/* "Branch if Positive" or "Branch on Result Plus"
Operation: if N == 0 -> pc = address
*/
uint8_t CPU6502::BPL()
{
	if (_getFlag(N) == 0)
	{
		cyclesLeft++;
		addrAbs = pc + addrRel; // used as a tmporary for checking

		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) // Does it want to cross a page boundary?
			cyclesLeft++;
		pc = addrAbs;
	}
	return 0;
}

/* "Branch on Overflow Clear"
Operation: if V == 0 -> pc = address
*/
uint8_t CPU6502::BVC()
{
	if (_getFlag(V) == 0)
	{
		cyclesLeft++;
		addrAbs = pc + addrRel; // used as a tmporary for checking

		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) // Does it want to cross a page boundary?
			cyclesLeft++;
		pc = addrAbs;
	}
	return 0;
}

/* "Branch on Overflow Set"
Operation: if V == 1 -> pc = address
*/
uint8_t CPU6502::BVS()
{
	if (_getFlag(V) == 1)
	{
		cyclesLeft++;
		addrAbs = pc + addrRel; // used as a tmporary for checking

		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) // Does it want to cross a page boundary?
			cyclesLeft++;
		pc = addrAbs;
	}
	return 0;
}

/***********/
/*  FLAGS  */
/***********/
// Manipulating (setting and clearing)
// various condition flags.

/* "Clear Carry Flag"
Operation: if V == 10 → C -> pc = address
Operation: 0 → C
Should normally precede an ADC loop. 
Also useful when used with a R0L instruction to clear a bit in memory.
*/
uint8_t CPU6502::CLC()
{
	_setFlag(C, false);
	return 0;
}

/* "Clear Decimal Mode"
Operation: 0 → D
This allows all subsequent ADC and SBC instructions to operate as simple operations.
NOTE: On the MOS 6502, the value of the decimal mode flag is indeterminate after a RESET.

TODO: Review the word "allow" on the statements above
*/
uint8_t CPU6502::CLD()
{
	_setFlag(D, false);
	return 0;
}

/* "Clear Interrupt Disable"
Operation: 0 → I
This allows the microprocessor to receive interrupts.
*/
uint8_t CPU6502::CLI()
{
	_setFlag(I, false);
	return 0;
}

/* "Clear Overflow Flag"
Operation: 0 → V
Is used in conjunction with the set overflow pin
which can change the state of the overflow flag with an external signal.
*/
uint8_t CPU6502::CLV()
{
	_setFlag(V, false);
	return 0;
}

/* "Set Carry Flag"
Operation: 1 → C
Should normally precede a SBC loop.
Also useful when used with a ROL instruction to initialize a bit in memory to a 1.
*/
uint8_t CPU6502::SEC()
{
	_setFlag(C, true);
	return 0;
}


/* "Set Decimal Mode"
Operation: 1 → D
This makes all subsequent ADC and SBC instructions
operate as a decimal arithmetic operation.
*/
uint8_t CPU6502::SED()
{
	_setFlag(D, true);
	return 0;
}

/* "Set Interrupt Disable"
Operation: 1 → I

It is used to mask interrupt requests during
system reset operations and during interrupt commands.
*/
uint8_t CPU6502::SEI()
{
	_setFlag(I, true);
	return 0;
}


/******************************/
/*  THE OTHERS, THE BANISHED  */
/******************************/

/* This function captures illegal opcodes */
uint8_t CPU6502::XXX()
{
	return 0;
}

/* Operation: No operation */
uint8_t CPU6502::NOP()
{
	// Sadly not all NOPs are equal, Ive added a few here
	// based on https://wiki.nesdev.com/w/index.php/CPU_unofficial_opcodes
	// and will add more based on game compatibility, and ultimately
	// I'd like to cover all illegal opcodes too
	switch (opcode) 
	{
		case 0x1C:
		case 0x3C:
		case 0x5C:
		case 0x7C:
		case 0xDC:
		case 0xFC:
			return 1;
			break;
	}
	return 0;
}

/* ----------------------------------------- *
                    Others
 * ---------------------------------------- */

// Indicates the current instruction has completed by returning true. This is
// a utility function to enable "step-by-step" execution, without manually 
// clocking every cycle
bool CPU6502::Complete()
{
	return cyclesLeft == 0;
}

// A setter for the bus pointer
void CPU6502::ConnectBus(Bus *n)
{
	bus = n;
}

// AUTHOR: javidx9
// This is the disassembly function. Its workings are not required for emulation.
// It is merely a convenience function to turn the binary instruction code into
// human readable form. Its included as part of the emulator because it can take
// advantage of many of the CPUs internal operations to do this.
std::map<uint16_t, std::string> CPU6502::disassemble(uint16_t start, uint16_t stop)
{
	uint32_t addr = start;
	uint8_t value = 0x00, lo = 0x00, hi = 0x00;
	std::map<uint16_t, std::string> mapLines;
	uint16_t line_addr = 0;

	// A convenient utility to convert variables into
	// hex strings because "modern C++"'s method with 
	// streams is atrocious
	auto hex = [](uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	// Starting at the specified address we read an instruction
	// byte, which in turn yields information from the lookup table
	// as to how many additional bytes we need to read and what the
	// addressing mode is. I need this info to assemble human readable
	// syntax, which is different depending upon the addressing mode

	// As the instruction is decoded, a std::string is assembled
	// with the readable output
	while (addr <= (uint32_t)stop)
	{
		line_addr = addr;

		// Prefix line with instruction address
		std::string sInst = "$" + hex(addr, 4) + ": ";

		// Read instruction, and get its readable name
		uint8_t opcode = bus->Read(addr, true); addr++;
		sInst += lookup[opcode].name + " ";

		// Get oprands from desired locations, and form the
		// instruction based upon its addressing mode. These
		// routines mimmick the actual Fetch routine of the
		// 6502 in order to get accurate data as part of the
		// instruction
		if (lookup[opcode].addrmode == &CPU6502::IMP)
		{
			sInst += " {IMP}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::IMM)
		{
			value = bus->Read(addr, true); addr++;
			sInst += "#$" + hex(value, 2) + " {IMM}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::ZP0)
		{
			lo = bus->Read(addr, true); addr++;
			hi = 0x00;												
			sInst += "$" + hex(lo, 2) + " {ZP0}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::ZPX)
		{
			lo = bus->Read(addr, true); addr++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", X {ZPX}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::ZPY)
		{
			lo = bus->Read(addr, true); addr++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", Y {ZPY}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::IZX)
		{
			lo = bus->Read(addr, true); addr++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + ", X) {IZX}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::IZY)
		{
			lo = bus->Read(addr, true); addr++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + "), Y {IZY}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::ABS)
		{
			lo = bus->Read(addr, true); addr++;
			hi = bus->Read(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + " {ABS}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::ABX)
		{
			lo = bus->Read(addr, true); addr++;
			hi = bus->Read(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", X {ABX}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::ABY)
		{
			lo = bus->Read(addr, true); addr++;
			hi = bus->Read(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", Y {ABY}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::IND)
		{
			lo = bus->Read(addr, true); addr++;
			hi = bus->Read(addr, true); addr++;
			sInst += "($" + hex((uint16_t)(hi << 8) | lo, 4) + ") {IND}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::REL)
		{
			value = bus->Read(addr, true); addr++;
			sInst += "$" + hex(value, 2) + " [$" + hex(addr + value, 4) + "] {REL}";
		}

		// Add the formed string to a std::map, using the instruction's
		// address as the key. This makes it convenient to look for later
		// as the instructions are variable in length, so a straight up
		// incremental index is not sufficient.
		mapLines[line_addr] = sInst;
	}

	return mapLines;
}
