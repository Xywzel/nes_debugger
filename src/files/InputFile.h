#pragma once

#include <stdint.h>
#include <string>
#include <vector>

class InputFile
{
	public:
		InputFile(std::string name);
		~InputFile();

		// Returns false if the file failed to load,
		// or last stream operation requested more data than was left
		bool isGood();

		// If not enough data is left, returns false,
		// the target is not changed
		// In pointer versions, user needs to make sure there is enough room in target
		bool read(uint8_t* target, size_t length);
		// In vector versions, vectors length is used, set it first
		bool read(std::vector<uint8_t>& target);

		// Stream functions don't change target if there is not enough data to read
		// asked data type, good flag is set to false, and position will be over the end
		InputFile& operator>> (int8_t& target);
		InputFile& operator>> (uint8_t& target);
		InputFile& operator>> (int16_t& target);
		InputFile& operator>> (uint16_t& target);
		InputFile& operator>> (int32_t& target);
		InputFile& operator>> (uint32_t& target);
		InputFile& operator>> (int64_t& target);
		InputFile& operator>> (uint64_t& target);

	private:
		std::vector<char> data;
		size_t position = 0;
		bool good = false;
};
