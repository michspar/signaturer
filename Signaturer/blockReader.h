#pragma once
class blockReader
{
	const int byteBlockSize_;
	boost::interprocess::file_mapping file_;
	const long long fileSize_;
	const int blockCount_;
	int currentBlock_;

public:
	blockReader(const string &path, int byteBlockSize);

	bytevect readNextBlock();
	void resetPosition();
	int count();
};

