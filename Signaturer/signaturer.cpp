#include "stdafx.h"
#include "signaturer.h"
#include "blockReader.h"
#include "blockWriter.h"
#include "threadPool.h"

typedef boost::crc_16_type crc;
const int signaturer::checksumSize = crc::bit_count / 8;
bool signaturer::bFail = false;

void signaturer::signFile(const std::string &in, const std::string &out, int byteBlockSize)
{
	bFail = false;

	blockReader reader(in, byteBlockSize);
	blockWriter writer(out, checksumSize, reader.count());
	{
		threadPool tp;

		for (int i = 0; i < !bFail && reader.count(); i++)
		{
			tp.queue(boost::bind(signBlock, reader.readAt(i), &writer, i));
		}
	}
}

void signaturer::signBlock(bytevect block, blockWriter *writer, int pos)
{
	try
	{
		crc crcComputer;

		crcComputer.process_block(block.data(), block.data() + block.size());

		auto checksum = crcComputer.checksum();
		char *pChecksum = reinterpret_cast<char *>(&checksum);

		writer->writeAt(pos, bytevect(pChecksum, pChecksum + checksumSize));
	}
	catch (const std::exception &ex)
	{
		bFail = true;
		std::cerr << ex.what() << std::endl;
	}
}