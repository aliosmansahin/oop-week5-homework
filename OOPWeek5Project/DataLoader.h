#pragma once

#include <fstream>
#include <string>

class DataLoader
{
public:
	DataLoader(const std::string& filePath);
	~DataLoader();

public:
	std::string ReadString();
	int ReadInt();
	char ReadChar();

public:
	bool IsOpen() { return fileStream.is_open(); }
	bool IsEndOfFile() { return fileStream.eof(); }

private:
	std::ifstream fileStream;
};

