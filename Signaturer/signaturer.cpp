#include "stdafx.h"
#include "signaturer.h"
#include "blockReader.h"
#include "blockWriter.h"

const int signaturer::checksumSize = boost::crc_16_type::bit_count / 8;

void signaturer::signFile(const std::string &in, const std::string &out, int byteBlockSize)
{
	blockReader reader(in, byteBlockSize);

	{
		std::ofstream out(out, std::ios_base::binary);
	}

	boost::filesystem::resize_file(out, reader.count() * checksumSize);

	blockWriter writer(out, checksumSize);

	for (int i = 0; i < reader.count(); i++)
	{
		signBlock(writer, i, reader.readNextBlock());
	}
}

void signaturer::signBlock(blockWriter &writer, int i, bytevect block)
{
	boost::crc_16_type crcComputer;
	crcComputer.process_block(block.data(), block.data() + block.size());

	auto checksum = crcComputer.checksum();
	char *pChecksum = reinterpret_cast<char *>(&checksum);

	writer.writeAt(i, bytevect(pChecksum, pChecksum + checksumSize));
}