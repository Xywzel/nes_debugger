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
	Instruction("BRK", 0x00, AddressingMode::Implied,   2, 7, 0);
	Instruction("ADC", 0x69, AddressingMode::Immediate, 2, 2, 0);
	Instruction("ADC", 0x65, AddressingMode::ZeroPage,  2, 3, 0);
	Instruction("ADC", 0x75, AddressingMode::ZeroPageX, 2, 4, 0);
	Instruction("ADC", 0x6D, AddressingMode::Absolute,  3, 4, 0);
	Instruction("ADC", 0x7D, AddressingMode::AbsoluteX, 3, 4, 1);
	Instruction("ADC", 0x79, AddressingMode::AbsoluteY, 3, 4, 1);
	Instruction("ADC", 0x61, AddressingMode::IndirectX, 2, 6, 0);
	Instruction("ADC", 0x71, AddressingMode::IndirectY, 2, 5, 1);

	Instruction("AND", 0x29, AddressingMode::Immediate, 2, 2, 0);
	Instruction("AND", 0x25, AddressingMode::ZeroPage,  2, 3, 0);
	Instruction("AND", 0x35, AddressingMode::ZeroPageX, 2, 4, 0);
	Instruction("AND", 0x2D, AddressingMode::Absolute,  3, 4, 0);
	Instruction("AND", 0x3D, AddressingMode::AbsoluteX, 3, 4, 1);
	Instruction("AND", 0x39, AddressingMode::AbsoluteY, 3, 4, 1);
	Instruction("AND", 0x21, AddressingMode::IndirectX, 2, 6, 0);
	Instruction("AND", 0x31, AddressingMode::IndirectY, 2, 5, 1);

	Instruction("ASL", 0x0A, AddressingMode::Accumulator, 1, 2, 0);
	Instruction("ASL", 0x06, AddressingMode::ZeroPage,    2, 5, 0);
	Instruction("ASL", 0x16, AddressingMode::ZeroPageX,   2, 6, 0);
	Instruction("ASL", 0x0E, AddressingMode::Absolute,    3, 6, 0);
	Instruction("ASL", 0x1E, AddressingMode::AbsoluteX,   3, 7, 0);

	Instruction("BCC", 0x90, AddressingMode::Relative, 2, 2, 2)
};

