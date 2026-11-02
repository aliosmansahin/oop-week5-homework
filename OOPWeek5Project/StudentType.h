#pragma once

#include <iostream>

#include "CourseType.h"
#include "DataLoader.h"
#include "DataSaver.h"

class StudentType
{
public:
	StudentType();
	StudentType(std::string studentName, int studentID, bool isTuitionPaid, int numberOfCourses);
	~StudentType();

public:
	bool InitCourses(DataLoader* dataLoader);
	bool DoCalculations(int tuitionPerCredits);
	bool Export(DataSaver* dataSaver);
	bool ExportCourses(DataSaver* dataSaver);

public:
	int GetTotalCredits();
	int GetTotalTuition(int tuitionPerCredits);
	double CalculateGPA();

private:
	bool SortCoursesByCourseCode(); //No need to public this

private:
	std::string studentName;
	int studentID;
	bool isTuitionPaid; // true is paid, false is unpaid
	int numberOfCourses;
	
	CourseType** courses; // An array to store course list of student

private:
	//Calculated values by DoCalculations
	int totalTuition;
	double gpa;
};

