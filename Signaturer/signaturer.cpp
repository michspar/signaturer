#include "stdafx.h"
#include "signaturer.h"
#include "blockReader.h"
#include "blockWriter.h"

namespace signaturer
{
	void signFile(const std::string &in, const std::string &out, int byteBlockSize)
	{
		blockReader reader(in, byteBlockSize);
		boost::crc_16_type crcComputer;
		const int checksumSize = crcComputer.bit_count / 8;

		{
			std::ofstream out(out, std::ios_base::binary);
		}

		boost::filesystem::resize_file(out, reader.count() * checksumSize);

		blockWriter writer(out, checksumSize);

		for (int i = 0; i < reader.count(); i++)
		{
			bytevect block = reader.readNextBlock();

			crcComputer.process_block(block.data(), block.data() + block.size());
			
			auto checksum = crcComputer.checksum();
			char *pChecksum = reinterpret_cast<char *>(&checksum);

			writer.writeAt(i, bytevect(pChecksum, pChecksum + checksumSize));
			crcComputer.reset();
		}
	}
}