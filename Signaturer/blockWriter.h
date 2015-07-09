#pragma once
class blockWriter
{
	const int byteBlockSize_;
	boost::interprocess::file_mapping file_;
	const long long fileSize_;
	const int blockCount_;
	std::vector<bool> writtenBlocks_;

public:
	blockWriter(const blockWriter &) = delete;
	blockWriter(const string &path, int byteBlockSize);
	
	void writeAt(long long position, const bytevect &block);
};

