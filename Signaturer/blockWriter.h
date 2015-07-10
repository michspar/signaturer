#pragma once
class blockWriter
{
	const int byteBlockSize_;
	const long long fileSize_;
	string path_;
	std::vector<bytevect> blocks_;

public:
	blockWriter(const blockWriter &) = delete;
	blockWriter(const string &path, int byteBlockSize, int blocksCount);
	~blockWriter();
	
	void writeAt(long long position, const bytevect &block);
};

