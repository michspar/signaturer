#include "stdafx.h"
#include "blockWriter.h"

using namespace boost::interprocess;

blockWriter::blockWriter(const string &path, int byteBlockSize):
	byteBlockSize_(byteBlockSize),
	file_(path.c_str(), read_write),
	fileSize_(boost::filesystem::file_size(path)),
	blockCount_(int(fileSize_ / byteBlockSize) + (fileSize_ % byteBlockSize ? 1 : 0)),
	writtenBlocks_(blockCount_)
{
}

void blockWriter::writeAt(long long position, const bytevect &block)
{
	if (writtenBlocks_[position])
		throw std::exception("block can be written only once");

	auto offset = position * byteBlockSize_;
	auto regionSize = min_value(fileSize_ - offset, (long long)byteBlockSize_);

	if (block.size() != regionSize)
		throw std::exception("invalid block size");

	mapped_region memoryRegion(file_, read_write, offset, regionSize);
	auto begin = static_cast<char *>(memoryRegion.get_address());

	std::copy(block.begin(), block.end(), begin);

	writtenBlocks_[position] = true;
}