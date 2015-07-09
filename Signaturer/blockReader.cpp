#include "stdafx.h"
#include "blockReader.h"

using namespace boost::interprocess;

blockReader::blockReader(const string &path, int byteBlockSize): 
	byteBlockSize_(byteBlockSize), 
	file_(path.c_str(), read_only), 
	fileSize_(boost::filesystem::file_size(path)), 
	blockCount_(int(fileSize_ / byteBlockSize) + (fileSize_ % byteBlockSize ? 1 : 0))
{	
}

bytevect blockReader::readAt(long long n)
{
	auto blockOffset = n * byteBlockSize_;

	if (n < 0 || blockOffset > fileSize_)
		throw std::exception("invalid block number");

	auto regionSize = min_value(fileSize_ - blockOffset, (long long)byteBlockSize_);
	mapped_region memoryRegion(file_, read_only, blockOffset, regionSize);
	char *begin = static_cast<char *>(memoryRegion.get_address());
	char *end = begin + memoryRegion.get_size();

	return bytevect(begin, end);
}

int blockReader::count()
{
	return blockCount_;
}