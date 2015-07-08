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

void blockWriter::writeAt(int i, const bytevect &block)
{
	if (writtenBlocks_[i])
		throw std::exception("block can be written only once");

	auto offset = i * byteBlockSize_;
	auto regionSize = min_value(int(fileSize_ - offset), byteBlockSize_);

	if (block.size() != regionSize)
		throw std::exception("invalid block size");

	mapped_region memoryRegion(file_, read_write, offset, regionSize);
	auto begin = static_cast<char *>(memoryRegion.get_address());

	std::copy(block.begin(), block.end(), begin);

	writtenBlocks_[i] = true;
}