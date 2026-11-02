#include "CourseType.h"

CourseType::CourseType()
{
	this->courseName = "";
	this->courseCode = "";
	this->creditHours = 0;
	this->grade = 'Z';
}

CourseType::CourseType(std::string courseName, std::string courseCode, int creditHours, char grade)
{
	this->courseName = courseName;
	this->courseCode = courseCode;
	this->creditHours = creditHours;
	this->grade = grade;
}

bool CourseType::Export(DataSaver* dataSaver)
{
	if (!dataSaver || !dataSaver->IsOpen()) return false;

	dataSaver->SetNextW(12);
	dataSaver->SetNextLeft();
	dataSaver->WriteString(courseCode);

	dataSaver->SetNextW(15);
	dataSaver->SetNextLeft();
	dataSaver->WriteString(courseName);

	dataSaver->SetNextW(4);
	dataSaver->SetNextRight();
	dataSaver->WriteInt(creditHours);

	dataSaver->SetNextW(9);
	dataSaver->WriteChar(grade);

	return true;
}
