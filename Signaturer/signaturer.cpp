#include "stdafx.h"
#include "signaturer.h"
#include "blockReader.h"

namespace signaturer
{
	void signFile(const std::string &in, const std::string &out, int byteBlockSize)
	{
		blockReader reader(in, byteBlockSize);
		std::vector<char> block = reader.readNextBlock();
	}
}