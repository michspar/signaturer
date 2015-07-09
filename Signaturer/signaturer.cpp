#include "stdafx.h"
#include "signaturer.h"
#include "blockReader.h"
#include "blockWriter.h"
#include "threadPool.h"

const int signaturer::checksumSize = boost::crc_16_type::bit_count / 8;

void signaturer::signFile(const std::string &in, const std::string &out, int byteBlockSize)
{
	blockReader reader(in, byteBlockSize);

	{
		std::ofstream out(out, std::ios_base::binary);
	}

	boost::filesystem::resize_file(out, reader.count() * checksumSize);

	blockWriter writer(out, checksumSize);
	threadPool tp(boost::thread::hardware_concurrency());

	for (int i = 0; i < reader.count(); i++)
	{
		tp.queue(boost::bind(signBlock, &writer, i, &reader));
	}
}

void signaturer::signBlock(blockWriter *writer, int i, blockReader *reader)
{
	boost::crc_16_type crcComputer;
	auto block = reader->readAt(i);

	crcComputer.process_block(block.data(), block.data() + block.size());

	auto checksum = crcComputer.checksum();
	char *pChecksum = reinterpret_cast<char *>(&checksum);

	writer->writeAt(i, bytevect(pChecksum, pChecksum + checksumSize));
}