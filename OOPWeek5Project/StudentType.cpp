#include "StudentType.h"

StudentType::StudentType()
{
	this->studentName = "";
	this->studentID = 0;
	this->isTuitionPaid = false;
	this->numberOfCourses = 0;
	this->courses = nullptr;
	this->gpa = -1.0f;
	this->totalTuition = -1;
}

StudentType::StudentType(std::string studentName, int studentID, bool isTuitionPaid, int numberOfCourses)
{
	this->studentName = studentName;
	this->studentID = studentID;
	this->isTuitionPaid = isTuitionPaid;
	this->numberOfCourses = numberOfCourses;
	this->courses = nullptr;
	this->gpa = -1.0f;
	this->totalTuition = -1;
}

StudentType::~StudentType()
{
	if (courses)
	{
		for (int i = 0; i < numberOfCourses; ++i) {
			if (courses[i]) {
				delete courses[i];
				courses[i] = nullptr;
			}
		}

		delete[] courses;
		courses = nullptr;
	}
}

bool StudentType::InitCourses(DataLoader* dataLoader)
{
	if (!dataLoader || !dataLoader->IsOpen())
		return false;

	/* Initialize courses array */
	courses = new CourseType* [numberOfCourses];

	if (!courses)
		return false;

	for (int i = 0; i < numberOfCourses; ++i) {
		/* Get data of course from file */
		std::string courseName = dataLoader->ReadString();
		
		std::string courseCode = dataLoader->ReadString();

		int creditHours = dataLoader->ReadInt();

		char grade = dataLoader->ReadChar();

		courses[i] = new CourseType(courseName, courseCode, creditHours, grade);

		if (!courses[i]) return false;
	}

	if (!SortCoursesByCourseCode()) return false;

	return true;
}

bool StudentType::DoCalculations(int tuitionPerCredits)
{
	if (isTuitionPaid) {
		gpa = CalculateGPA();

		if (gpa == -1.0) return false;
	}
	else {
		totalTuition = GetTotalTuition(tuitionPerCredits);

		if (totalTuition == -1) return false;
	}

	return true;
}

bool StudentType::Export(DataSaver* dataSaver)
{
	if (!dataSaver || !dataSaver->IsOpen()) return false;

	dataSaver->WriteStringLabelWithEndl("Student Name", studentName);
	dataSaver->WriteIntLabelWithEndl("Student ID", studentID);
	dataSaver->WriteIntLabelWithEndl("Number of courses enrolled", numberOfCourses);
	dataSaver->WriteEndl();

	if (isTuitionPaid) {
		if (!ExportCourses(dataSaver)) return false;

		dataSaver->WriteEndl();

		dataSaver->WriteIntLabelWithEndl("Total number of credits", GetTotalCredits());
		dataSaver->SetNextPrecision(3);
		dataSaver->WriteDoubleLabelWithEndl("Mid-Semester GPA", gpa);
	}
	else {
		dataSaver->WriteString("Grades are withheld due to unpaid tuition.");
		dataSaver->WriteEndl();
		dataSaver->WriteIntLabelWithEndl("Total number of credits", GetTotalCredits());
		dataSaver->WriteIntLabelWithEndl("Outstanding tuition", totalTuition);
	}

	return true;
}

bool StudentType::ExportCourses(DataSaver* dataSaver)
{
	if (!dataSaver || !dataSaver->IsOpen()) return false;

	/* Titles */
	dataSaver->WriteString("Course No");
	dataSaver->WriteSpace(3);

	dataSaver->WriteString("Course Name");
	dataSaver->WriteSpace(4);

	dataSaver->WriteString("Credits");
	dataSaver->WriteSpace(3);

	dataSaver->WriteString("Grade");
	dataSaver->WriteEndl();

	if (!courses)
		return false;

	for (int i = 0; i < numberOfCourses; ++i) {
		if (!courses[i] || !courses[i]->Export(dataSaver)) return false;

		dataSaver->WriteEndl();
	}

	return true;
}

int StudentType::GetTotalCredits()
{
	if (!courses)
		return -1;

	int totalCredits = 0;

	for (int i = 0; i < numberOfCourses; ++i) {
		if (!courses[i]) return -1;

		totalCredits += courses[i]->GetCreditHours();
	}

	return totalCredits;
}

int StudentType::GetTotalTuition(int tuitionPerCredits)
{
	int totalCredits = GetTotalCredits();
	if (totalCredits == -1) return -1;

	return totalCredits * tuitionPerCredits;
}

double StudentType::CalculateGPA()
{
	if (!courses)
		return -1.0;

	int totalPoints = 0;

	for (int i = 0; i < numberOfCourses; ++i) {
		if (!courses[i]) return -1.0;

		int credits = courses[i]->GetCreditHours();

		char grade = courses[i]->GetGrade();

		int gradePoints = -1;

		switch (grade) {
		case 'A':
			gradePoints = 4;
			break;
		case 'B':
			gradePoints = 3;
			break;
		case 'C':
			gradePoints = 2;
			break;
		case 'D':
			gradePoints = 1;
			break;
		case 'F':
			gradePoints = 0;
			break;
		}

		if (gradePoints == -1) return -1.0;

		int creditPoints = credits * gradePoints;

		totalPoints += creditPoints;
	}

	int totalCredits = GetTotalCredits();
	if (totalCredits == -1) return -1.0;

	double gpa = static_cast<double>(totalPoints) / totalCredits;

	return gpa;
}

bool StudentType::SortCoursesByCourseCode()
{
	if (!courses) return false;

	bool swapDone = false;

	do {
		swapDone = false;
		for (int i = 0; i < numberOfCourses - 1; ++i) {
			CourseType* currentCourse = courses[i];
			CourseType* nextCourse = courses[i + 1];

			if (!currentCourse || !nextCourse) return false;

			if (currentCourse->GetCourseCode() > nextCourse->GetCourseCode()) {
				// Swap pointers
				courses[i] = nextCourse;
				courses[i + 1] = currentCourse;

				swapDone = true;
			}
		}
	} while (swapDone);

	return true;
}