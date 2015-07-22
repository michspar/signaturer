#include "stdafx.h"
#include "blockWriter.h"

using namespace boost::interprocess;

blockWriter::blockWriter(const string &path, int byteBlockSize, int blocksCount) :
	path_(path),
	blocks_(blocksCount)
{
}

blockWriter::~blockWriter()
{
	try
	{
		std::ofstream out(path_, std::ios::binary);

		for (auto block : blocks_)
			out.write(block.data(), block.size());
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void blockWriter::writeAt(int position, const bytevect &block)
{
	blocks_[position] = block;
}