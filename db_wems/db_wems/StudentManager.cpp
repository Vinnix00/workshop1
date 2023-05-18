#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Student.h"
#include "StudentManager.h"
#include <conio.h>


constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;

bool StudentManager::login(Student* student)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Student WHERE Student_ID = ?");
	ps->setString(1, student->studentID);
	ResultSet* rs = ps->executeQuery();
	if (!(rs->next()))
	{
		system("CLS");
		cout << "ID is wrong, please insert again" << endl;
		system("pause");
		return false;
	}
	else
	{
		delete rs;
		delete ps;
		ps = dbConn.prepareStatement("SELECT * FROM student WHERE Student_ID = ? AND Student_Password = ?");
		ps->setString(1, student->studentID);
		ps->setString(2, student->password);
		rs = ps->executeQuery();
		if (!(rs->next())) {
			system("CLS");
			cout << "Password is wrong, please insert again " << endl;
			system("pause");
			return false;
		}
		delete rs;
		delete ps;
	}
	return true;
}





