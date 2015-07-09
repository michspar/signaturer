#pragma once
class blockWriter;
class blockReader;

class signaturer
{
	static void signBlock(blockWriter *writer, int i, blockReader *reader);
	static const int checksumSize;

public:
	static void signFile(const std::string &in, const std::string &out, int byteBlockSize);
};