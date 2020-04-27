#include "RomTest.h"

#include <iostream>

#include "files/NesRomFile.h"

namespace tests
{
	static void test1()
	{
		NesRomFile rom("rom/cpu_dummy_reads.nes");
	}

	void romTest()
	{
		std::cout << "Performing ROM file loading tests" << std::endl;
		test1();
		std::cout << "ROM file tests concluded" << std::endl;
	}
}
