#pragma once
class blockWriter
{
	string path_;
	std::vector<bytevect> blocks_;

public:
	blockWriter(const blockWriter &) = delete;
	blockWriter(const string &path, int byteBlockSize, int blocksCount);
	~blockWriter();
	
	void writeAt(int position, const bytevect &block);
};

