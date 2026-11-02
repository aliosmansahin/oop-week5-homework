#include "DataLoader.h"

DataLoader::DataLoader(const std::string& filePath)
{
	fileStream.open(filePath);
}

DataLoader::~DataLoader()
{
	if(IsOpen())
		fileStream.close();
}

std::string DataLoader::ReadString()
{
	if (!IsOpen())
		return "";

	if (IsEndOfFile())
		return "";

	std::string line;

	fileStream >> line;

	return line;
}

int DataLoader::ReadInt()
{
	if (!IsOpen())
		return -1;

	if (IsEndOfFile())
		return -1;

	int line;

	fileStream >> line;

	return line;
}

char DataLoader::ReadChar()
{
	if (!IsOpen())
		return ' ';

	if (IsEndOfFile())
		return ' ';

	char line;

	fileStream >> line;

	return line;
}