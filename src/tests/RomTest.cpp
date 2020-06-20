#include "RomTest.h"

#include <iostream>

#include "files/NesRomFile.h"
#include "hardware/ConsoleType.h"

namespace tests
{
	static void test1()
	{
		NesRomFile rom("rom/cpu_dummy_reads.nes");
		std::cout << "Format String: " << (rom.hasCorrectFormatString() ? "yes" : "no") << std::endl;
		std::cout << "Vertical Mirroring: " << (rom.hasVerticalMirroring() ? "yes" : "no") << std::endl;
		std::cout << "Persistent Memory: " << (rom.hasPersistentMemory() ? "yes" : "no") << std::endl;
		std::cout << "Trainer: " << (rom.hasTrainer() ? "yes" : "no") << std::endl;
		std::cout << "Ignore Mirroring: " << (rom.hasIgnoreMirroring() ? "yes" : "no") << std::endl;
		std::cout << "Mapper Number: " << std::hex << int(rom.getMapperNumber()) << std::dec << std::endl;
		std::cout << "iNesVersion2: " << (rom.isNesVersionTwo() ? "yes" : "no") << std::endl;
		std::cout << "Console Type: " << enumToString(rom.getConsoleType())  << std::endl;
	}

	void romTest()
	{
		std::cout << "Performing ROM file loading tests" << std::endl;
		test1();
		std::cout << "ROM file tests concluded" << std::endl;
	}
}
