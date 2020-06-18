#include "InputFile.h"

#include <stdint.h>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>

InputFile::InputFile(std::string name)
{
	// Open file in binary mode with carret at the end
	std::ifstream file(name.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	if (! file.is_open())
		return;

	size_t fileSize = file.tellg(); // Get file size, in bytes
	// TODO: Not portable on text files
	// For extra safety, should use filesystem::file_size
	file.seekg(0, std::ios::beg); // Return to start of the file
	data.resize(fileSize); // Prepare the target vector
	file.read(&data[0], data.size()); // Copy to the vector

	// Set reading position and good flag
	position = 0;
	good = true;
}

InputFile::~InputFile()
{
	// vector auto-cleans, so nothing to do here
}

bool InputFile::isGood()
{
	return good && position < data.size();
}

bool InputFile::read(uint8_t* target, size_t length)
{
	if(position + length > data.size())
		return false;

	std::memcpy(target, &data[position], length);
	position += length;

	return true;
}

bool InputFile::read(std::vector<uint8_t>& target)
{
	if(position + target.size() > data.size())
		return false;

	std::memcpy(target.data(), &data[position], target.size());
	position += target.size();

	return true;
}

InputFile& InputFile::operator>> (int8_t& target)
{
	if(position + sizeof(target) <= data.size())
		std::memcpy(&target, &data[position], sizeof(target));
	position += sizeof(data);
	return (*this);
}

InputFile& InputFile::operator>> (uint8_t& target)
{
	if(position + sizeof(target) <= data.size())
		std::memcpy(&target, &data[position], sizeof(target));
	position += sizeof(data);
	return (*this);
}

InputFile& InputFile::operator>> (int16_t& target)
{
	if(position + sizeof(target) <= data.size())
		std::memcpy(&target, &data[position], sizeof(target));
	position += sizeof(data);
	return (*this);
}

InputFile& InputFile::operator>> (uint16_t& target)
{
	if(position + sizeof(target) <= data.size())
		std::memcpy(&target, &data[position], sizeof(target));
	position += sizeof(data);
	return (*this);
}

InputFile& InputFile::operator>> (int32_t& target)
{
	if(position + sizeof(target) <= data.size())
		std::memcpy(&target, &data[position], sizeof(target));
	position += sizeof(data);
	return (*this);
}

InputFile& InputFile::operator>> (uint32_t& target)
{
	if(position + sizeof(target) <= data.size())
		std::memcpy(&target, &data[position], sizeof(target));
	position += sizeof(data);
	return (*this);
}

InputFile& InputFile::operator>> (int64_t& target)
{
	if(position + sizeof(target) <= data.size())
		std::memcpy(&target, &data[position], sizeof(target));
	position += sizeof(data);
	return (*this);
}

InputFile& InputFile::operator>> (uint64_t& target)
{
	if(position + sizeof(target) <= data.size())
		std::memcpy(&target, &data[position], sizeof(target));
	position += sizeof(data);
	return (*this);
}

