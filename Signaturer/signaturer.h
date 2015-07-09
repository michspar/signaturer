#pragma once
class blockWriter;

class signaturer
{
	static void signBlock(blockWriter &writer, int i, bytevect block);
	static const int checksumSize;
	static boost::basic_thread_pool pool;

public:
	static void signFile(const std::string &in, const std::string &out, int byteBlockSize);
};