#pragma once

#include <fstream>
#include <iostream>
#include <iomanip>

class DataSaver
{
public:
	DataSaver(const std::string& filePath);
	DataSaver(const std::string& filePath, bool enable_cout);
	~DataSaver();

public:
	/* No overloading in order to make like DataLoader class */
	void WriteString(std::string data);
	void WriteInt(int data);
	void WriteDouble(double data);
	void WriteChar(char data);
	void WriteSpace(int spaceCount = 1);
	void WriteEndl();

public:
	/* Methods to make "label: data\n" faster */
	void WriteStringLabelWithEndl(std::string label, std::string data);
	void WriteIntLabelWithEndl(std::string label, int data);
	void WriteDoubleLabelWithEndl(std::string label, double data);

public:
	/* Manipulate */
	void SetNextPrecision(int n);
	void SetNextW(int n);
	void SetNextRight();
	void SetNextLeft();

public:
	bool IsOpen() { return fileStream.is_open(); }

private:
	std::ofstream fileStream;

	bool is_cout_enabled = false; //If it is enabled, every call with this class will cout too
};

