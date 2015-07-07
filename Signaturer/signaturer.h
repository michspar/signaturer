#pragma once
class signaturer
{
public:
	signaturer(int kbBlockSize);
	void signFile(std::string in, std::string out);
};

