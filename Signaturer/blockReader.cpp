#include "stdafx.h"
#include "blockReader.h"

using namespace boost::interprocess;

blockReader::blockReader(const string &path, int byteBlockSize)
	: byteBlockSize_(byteBlockSize), file_(path.c_str(), read_only), fileSize_(boost::filesystem::file_size(path))
{	
	resetPosition();
}

std::vector<char> blockReader::readNextBlock()
{
	auto currentBlockOffset = currentBlock_ * byteBlockSize_;

	if (currentBlockOffset > fileSize_)
		return std::vector<char>();

	int regionSize = min_value(fileSize_ - currentBlockOffset, (long long)byteBlockSize_);
	mapped_region memoryRegion(file_, read_only, 0, regionSize);
	char *begin = static_cast<char *>(memoryRegion.get_address()) + currentBlockOffset;
	char *end = begin + memoryRegion.get_size();

	currentBlock_++;

	return std::vector<char>(begin, end);
}

void blockReader::resetPosition()
{
	currentBlock_ = 0;
}