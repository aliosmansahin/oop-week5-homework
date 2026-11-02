#include "DataSaver.h"

DataSaver::DataSaver(const std::string& filePath)
{
	fileStream.open(filePath);

	this->is_cout_enabled = false;
}

DataSaver::DataSaver(const std::string& filePath, bool enable_cout)
{
	fileStream.open(filePath);

	this->is_cout_enabled = enable_cout;
}

DataSaver::~DataSaver()
{
	if (IsOpen())
		fileStream.close();
}

void DataSaver::WriteString(std::string data)
{
	if (!IsOpen()) return;

	fileStream << data;

	if (is_cout_enabled) std::cout << data;
}

void DataSaver::WriteInt(int data)
{
	if (!IsOpen()) return;

	fileStream << data;

	if (is_cout_enabled) std::cout << data;
}

void DataSaver::WriteDouble(double data)
{
	if (!IsOpen()) return;

	fileStream << data;

	if (is_cout_enabled) std::cout << data;
}

void DataSaver::WriteChar(char data)
{
	if (!IsOpen()) return;

	fileStream << data;

	if (is_cout_enabled) std::cout << data;
}

void DataSaver::WriteSpace(int spaceCount)
{
	if (!IsOpen()) return;

	if (spaceCount < 1) return;

	for (int i = 0; i < spaceCount; ++i) {
		fileStream << " ";
		
		if(is_cout_enabled) std::cout << " ";
	}
}

void DataSaver::WriteEndl()
{
	if (!IsOpen()) return;
	
	fileStream << std::endl;

	if (is_cout_enabled) std::cout << std::endl;
}

void DataSaver::WriteStringLabelWithEndl(std::string label, std::string data)
{
	if (!IsOpen()) return;

	WriteString(label);
	WriteString(": ");
	WriteString(data);
	WriteEndl();
}

void DataSaver::WriteIntLabelWithEndl(std::string label, int data)
{
	if (!IsOpen()) return;

	WriteString(label);
	WriteString(": ");
	WriteInt(data);
	WriteEndl();
}

void DataSaver::WriteDoubleLabelWithEndl(std::string label, double data)
{
	if (!IsOpen()) return;

	WriteString(label);
	WriteString(": ");
	WriteDouble(data);
	WriteEndl();
}

void DataSaver::SetNextPrecision(int n)
{
	if (!IsOpen()) return;

	fileStream << std::setprecision(n);
	if (is_cout_enabled) std::cout << std::setprecision(n);
}

void DataSaver::SetNextW(int n)
{
	if (!IsOpen()) return;

	fileStream << std::setw(n);
	if (is_cout_enabled) std::cout << std::setw(n);
}

void DataSaver::SetNextRight()
{
	if (!IsOpen()) return;

	fileStream << std::right;
	if (is_cout_enabled) std::cout << std::right;
}

void DataSaver::SetNextLeft()
{
	if (!IsOpen()) return;

	fileStream << std::left;
	if (is_cout_enabled) std::cout << std::left;
}
