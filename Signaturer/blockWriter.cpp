#include "stdafx.h"
#include "blockWriter.h"

using namespace boost::interprocess;

blockWriter::blockWriter(const string &path, int byteBlockSize, int blocksCount) :
	byteBlockSize_(byteBlockSize),
	path_(path),
	fileSize_(boost::filesystem::file_size(path)),
	blocks_(int(fileSize_ / byteBlockSize) + (fileSize_ % byteBlockSize ? 1 : 0))
{
}

blockWriter::~blockWriter()
{
	std::ofstream out(path_, std::ios::binary);

	for (auto block : blocks_)
		out.write(block.data(), block.size());
}

void blockWriter::writeAt(long long position, const bytevect &block)
{
	blocks_[position] = block;
}