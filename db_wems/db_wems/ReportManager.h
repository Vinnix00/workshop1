#include "Report.h"
#include "Student.h"
#ifndef REPORTMANAGER_H
#define REPORTMANAGER_H

class ReportManager
{
public:

	void reportGenerate();
	int studentRegisterWebinar(Report* report);
	int searchStudent(int lastStudentID);
	Report* selectReportNO(int no);
	Report* selectStudent(string studentID);



};

#endif 
