#pragma once
class blockWriter;
class blockReader;

class signaturer
{
	static void signBlock(bytevect block, blockWriter *writer, int i);
	static const int checksumSize;
	static bool bFail;

public:
	static void signFile(const std::string &in, const std::string &out, int byteBlockSize);
};