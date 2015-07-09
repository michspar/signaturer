#include "stdafx.h"
#include "blockReader.h"

using namespace boost::interprocess;

blockReader::blockReader(const string &path, int byteBlockSize): 
	byteBlockSize_(byteBlockSize), 
	file_(path.c_str(), read_only), 
	fileSize_(boost::filesystem::file_size(path)), 
	blockCount_(int(fileSize_ / byteBlockSize) + (fileSize_ % byteBlockSize ? 1 : 0))
{	
	resetPosition();
}

bytevect blockReader::readNextBlock()
{
	auto currentBlockOffset = currentBlock_ * byteBlockSize_;

	if (currentBlockOffset > fileSize_)
		return bytevect();

	auto regionSize = min_value(fileSize_ - currentBlockOffset, (long long)byteBlockSize_);
	mapped_region memoryRegion(file_, read_only, currentBlockOffset, regionSize);
	char *begin = static_cast<char *>(memoryRegion.get_address());
	char *end = begin + memoryRegion.get_size();

	currentBlock_++;

	return bytevect(begin, end);
}

void blockReader::resetPosition()
{
	currentBlock_ = 0;
}

int blockReader::count()
{
	return blockCount_;
}