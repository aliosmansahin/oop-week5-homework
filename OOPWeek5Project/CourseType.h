#pragma once

#include <iostream>

#include "DataSaver.h"

class CourseType
{
public:
	CourseType();
	CourseType(std::string courseName, std::string courseCode, int creditHours, char grade);
	~CourseType() = default; //No need to implement

public:
	bool Export(DataSaver* dataSaver);

public:
	int GetCreditHours() { return creditHours; }
	std::string GetCourseCode() { return courseCode; }
	char GetGrade() { return grade; }

private:
	std::string courseName;
	std::string courseCode;
	int creditHours;
	char grade;
};

