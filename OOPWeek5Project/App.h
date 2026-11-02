#pragma once

#include "StudentType.h"
#include "DataLoader.h"
#include "DataSaver.h"

class App
{
public:
	App();
	~App();

	bool Run();

	bool InitStudents();
	bool DoCalculationsOfStudents();
	bool ExportStudents();

private:
	/* Helpers */
	std::string RemoveUnderscores(std::string& str);
	
private:
	int numberOfStudents;
	int tuitionPerCredit;

	StudentType** students; // An array to store students

	DataLoader* dataLoader; // Pointer to file loader
	DataSaver* dataSaver;	// Pointer to file saver

private:
	int exportWidth; //The width value of export list, will be used by title and separators
};

