#pragma once

enum class AddressingMode : uint8_t
{
	Absolute,
	AbsoluteX,
	AbsoluteY,
	Accumulator,
	Immediate,
	Implied,
	IndexedIndirect,
	Indirect,
	IndirectIndexed,
	Relative,
	ZeroPage,
	ZeroPageX,
	ZeroPageY
};

struct Instruction
{
	char name[4] = "XXX\0"; // Human readable operation code
	uint8_t operationCode = 0u; // The operation code that uses this operation
	AddressingMode mode = AddressingMode::Absolute; // How instructions accesses memory
	uint8_t size = 0u; // Size of the instruction in bytes
	uint8_t cycles = 0u; // Number of non conditional cycles taken by this instruction
	uint8_t pageCycles = 0u; // Number of extra cycles taken if instruction causes page change

	Instruction(char name[4], uint8_t opCode, AddressingMode mode, uint8_t size, uint8_t cycles, uint8_t pageCycles)
}

Instruction instructions[] =
{
	Instruction("BRK", 0, AddressingMode::Implied, 2, 7, 0);
};

"BRK",
	"ORA",
	"KIL",
	"SLO",
	"NOP",
	"ORA",
	"ASL",
	"SLO",
	"PHP",
	"ORA",
	"ASL",
	"ANC",
	"NOP",
	"ORA",
	"ASL",
	"SLO",
	"BPL",
	"ORA",
	"KIL",
	"SLO",
	"NOP",
	"ORA",
	"ASL",
	"SLO",
	"CLC",
	"ORA",
	"NOP",
	"SLO",
	"NOP",
	"ORA",
	"ASL",
	"SLO",
	"JSR",
	"AND",
	"KIL",
	"RLA",
	"BIT",
	"AND",
	"ROL",
	"RLA",
	"PLP",
	"AND",
	"ROL",
	"ANC", "BIT", "AND", "ROL", "RLA",
	"BMI", "AND", "KIL", "RLA", "NOP", "AND", "ROL", "RLA",
	"SEC", "AND", "NOP", "RLA", "NOP", "AND", "ROL", "RLA",
	"RTI", "EOR", "KIL", "SRE", "NOP", "EOR", "LSR", "SRE",
	"PHA", "EOR", "LSR", "ALR", "JMP", "EOR", "LSR", "SRE",
	"BVC", "EOR", "KIL", "SRE", "NOP", "EOR", "LSR", "SRE",
	"CLI", "EOR", "NOP", "SRE", "NOP", "EOR", "LSR", "SRE",
	"RTS", "ADC", "KIL", "RRA", "NOP", "ADC", "ROR", "RRA",
	"PLA", "ADC", "ROR", "ARR", "JMP", "ADC", "ROR", "RRA",
	"BVS", "ADC", "KIL", "RRA", "NOP", "ADC", "ROR", "RRA",
	"SEI", "ADC", "NOP", "RRA", "NOP", "ADC", "ROR", "RRA",
	"NOP", "STA", "NOP", "SAX", "STY", "STA", "STX", "SAX",
	"DEY", "NOP", "TXA", "XAA", "STY", "STA", "STX", "SAX",
	"BCC", "STA", "KIL", "AHX", "STY", "STA", "STX", "SAX",
	"TYA", "STA", "TXS", "TAS", "SHY", "STA", "SHX", "AHX",
	"LDY", "LDA", "LDX", "LAX", "LDY", "LDA", "LDX", "LAX",
	"TAY", "LDA", "TAX", "LAX", "LDY", "LDA", "LDX", "LAX",
	"BCS", "LDA", "KIL", "LAX", "LDY", "LDA", "LDX", "LAX",
	"CLV", "LDA", "TSX", "LAS", "LDY", "LDA", "LDX", "LAX",
	"CPY", "CMP", "NOP", "DCP", "CPY", "CMP", "DEC", "DCP",
	"INY", "CMP", "DEX", "AXS", "CPY", "CMP", "DEC", "DCP",
	"BNE", "CMP", "KIL", "DCP", "NOP", "CMP", "DEC", "DCP",
	"CLD", "CMP", "NOP", "DCP", "NOP", "CMP", "DEC", "DCP",
	"CPX", "SBC", "NOP", "ISC", "CPX", "SBC", "INC", "ISC",
	"INX", "SBC", "NOP", "SBC", "CPX", "SBC", "INC", "ISC",
	"BEQ", "SBC", "KIL", "ISC", "NOP", "SBC", "INC", "ISC",
	"SED", "SBC", "NOP", "ISC", "NOP", "SBC", "INC", "ISC",
