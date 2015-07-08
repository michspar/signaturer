#pragma once
class blockReader
{
	int byteBlockSize_, currentBlock_;
	const long long fileSize_;
	boost::interprocess::file_mapping file_;

public:
	blockReader(const string &path, int byteBlockSize);
	std::vector<char> readNextBlock();
	void resetPosition();
};

