#include "App.h"

App::App()
{
	students = nullptr;
	numberOfStudents = 0;
	tuitionPerCredit = 0;
	dataLoader = new DataLoader("input.txt");
	dataSaver = new DataSaver("output.txt", true);
	exportWidth = 42;
}

App::~App()
{
	if (dataLoader) {
		delete dataLoader;
		dataLoader = nullptr;
	}
	if (dataSaver)
	{
		delete dataSaver;
		dataSaver = nullptr;
	}
	if (students)
	{
		for (int i = 0; i < numberOfStudents; ++i) {
			if (students[i]) {
				delete students[i];
				students[i] = nullptr;
			}
		}

		delete[] students;
		students = nullptr;
	}
}

bool App::Run()
{
	/*
		Check if the loader opens the file correctly,
		Terminates if it fails
	*/
	if (!dataLoader->IsOpen()) {
		std::cerr << "File could not open for reading" << std::endl;
		return false;
	}
	if (!dataSaver->IsOpen()) {
		std::cerr << "File could not open for saving" << std::endl;
		return false;
	}

	/* First, get number of students and tuition per credit */
	numberOfStudents = dataLoader->ReadInt();
	if (numberOfStudents == -1) {
		std::cerr << "Number of students = -1: Quiting!" << std::endl;
		return false;
	}

	tuitionPerCredit = dataLoader->ReadInt();
	if (tuitionPerCredit == -1) {
		std::cerr << "Tuition per credit = -1: Quiting!" << std::endl;
		return false;
	}

	/* Then, initialize (load) students, do some calculations (like gpa...), and export results */
	if (!InitStudents()) {
		std::cerr << "Students could not be initialized" << std::endl;
		return false;
	}

	if (!DoCalculationsOfStudents()) {
		std::cerr << "Calculations could not be done" << std::endl;
		return false;
	}

	if (!ExportStudents()) {
		std::cerr << "Could not export students" << std::endl;
		return false;
	}

	return true;
}

bool App::InitStudents()
{	
	/* Initialize students array */
	students = new StudentType * [numberOfStudents];

	if (!students)
		return false;

	for (int i = 0; i < numberOfStudents; ++i) {
		/* Get data of student from file */
		std::string fullNameWithUnderscores = dataLoader->ReadString();
		std::string fullName = RemoveUnderscores(fullNameWithUnderscores);

		int studentId = dataLoader->ReadInt();

		char tuitionStatusInChar = dataLoader->ReadChar();
		bool isTuitionPaid = tuitionStatusInChar == 'Y' ? true : false;

		int numberOfCourses = dataLoader->ReadInt();

		students[i] = new StudentType(fullName, studentId, isTuitionPaid, numberOfCourses);

		if (!students[i] || !students[i]->InitCourses(dataLoader))
			return false;
	}

	return true;
}

bool App::DoCalculationsOfStudents()
{
	if (!students)
		return false;

	for (int i = 0; i < numberOfStudents; ++i) {
		/* Do calculation of all students (like gpa...)*/
		if(!students[i] || !students[i]->DoCalculations(tuitionPerCredit)) return false;
	}

	return true;
}

bool App::ExportStudents()
{
	if (!students)
		return false;

	/* To draw title */
	std::string title = "STUDENTS";
	int titleLength = static_cast<int>(title.length());

	int strCountBeforeTitle = exportWidth / 2 - titleLength / 2;
	int strCountAfterTitle = exportWidth - strCountBeforeTitle - titleLength;

	for (int i = 0; i < strCountBeforeTitle; ++i)
		dataSaver->WriteString("=");
	dataSaver->WriteString(title);
	for (int i = 0; i < strCountAfterTitle; ++i)
		dataSaver->WriteString("=");
	dataSaver->WriteEndl();

	for (int i = 0; i < numberOfStudents; ++i) {
		/* Write all data of all students */
		if (!students[i] || !students[i]->Export(dataSaver)) return false;

		if (i != numberOfStudents - 1) {
			for(int i = 0; i < exportWidth; ++i) // To draw separator
				dataSaver->WriteString("-");
				
			dataSaver->WriteEndl();
		}
	}

	return true;
}

std::string App::RemoveUnderscores(std::string& str)
{
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == '_')
			str[i] = ' ';
	}

	return str;
}
