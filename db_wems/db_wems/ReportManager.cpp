#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Report.h"
#include "ReportManager.h"
#include "Student.h"
#include <conio.h>


constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;

void ReportManager::reportGenerate()
{
	system("cls");
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM report");



	ResultSet* rs = ps->executeQuery();
	cout << "REPORT ID: R2021-001" << endl;
	cout << "Webinar ID: 2021-001\t\tWebinar Title: AI In The Future" << endl;
	cout << "\n\n" <<"NO" << setw(10) << "Student ID" << setw(20) << "Student Name" <<" "<< setw(20) << "Student Phone Number " << endl;
	cout << "===================================================================" << endl << endl;
	while (rs->next())
	{
		cout << "" << rs->getString(1) << setw(10) << rs->getString(2) << setw(20) << rs->getString(3) << setw(19) << rs->getString(4) << endl;

	}
	cout << "\n===================================================================" << endl << endl;
}

int ReportManager::studentRegisterWebinar(Report* report)
{
	system("cls");
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO report VALUES (?, ?, ?, ?)");

	ps->setInt(1, report->NO);
	ps->setString(2, report->studentID);
	ps->setString(3, report->sName);
	ps->setString(4, report->sPhoneNo);


	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int ReportManager::searchStudent(int lastStudentID) {

	Report* report = new Report();
	DatabaseConnection dbConn;
	PreparedStatement* ps;
	ResultSet* rs;

	bool check = true;
	int y = 1;
	int c = 0;
	int NO = 0;
	string name = "";
	vector <string> arrow;
	for (int i = 0; i <= lastStudentID; i++) {
		arrow.push_back("  ");
	}
	if (lastStudentID != 0) {
		arrow[1] = "-> ";
	}



	system("cls");
	cout << "\t\t\t\t\t\tType Name to Search" << endl;
	cout << "\t\t\t\t\t\tNAME : " << name << endl << endl;
	cout << "\n\n" << setw(8) << "Student ID" << setw(40) << "Student Name" << setw(20) << "Student Telephone No " << endl;
	cout << "===================================================================" << endl << endl;

	for (int i = 1; i <= lastStudentID; i++) {
		ps = dbConn.prepareStatement("SELECT NO FROM Report WHERE S_Name LIKE ? AND NO = ?");
		ps->setString(1, "%" + name + "%");
		ps->setInt(2, i);
		rs = ps->executeQuery();

		if (rs->next())
		{
			report = selectReportNO(rs->getInt(1));
			cout << arrow[i] << report->studentID << setw(40) << report->sName << setw(19) << report->sPhoneNo << endl;
		}


	}
	cout << "===================================================================" << endl << endl;


	while (check)
	{

		c = 0;



		switch ((c = _getch())) {
		case KEY_UP:
			if (y > 1) {
				arrow[y] = "  ";
				int j = y;
				j--;
				bool c = true;
				while (c) {
					ps = dbConn.prepareStatement("SELECT NO FROM report WHERE S_Name LIKE ? AND NO = ?");
					ps->setString(1, "%" + name + "%");
					ps->setInt(2, j);
					rs = ps->executeQuery();
					if (rs->next()) {
						y = j;
						c = false;
					}
					if (j == 1) {
						c = false;
					}
					else {
						j--;
					}



				}
				arrow[y] = "-> ";
			}
			break;
		case KEY_DOWN:
			if (y < lastStudentID) {
				arrow[y] = "  ";
				int j = y;
				j++;
				bool c = true;
				while (c) {
					ps = dbConn.prepareStatement("SELECT NO FROM report WHERE S_Name LIKE ? AND NO = ?");
					ps->setString(1, "%" + name + "%");
					ps->setInt(2, j);
					rs = ps->executeQuery();
					if (rs->next()) {
						y = j;
						c = false;
					}
					if (j == lastStudentID) {
						c = false;
					}
					else {
						j++;
					}



				}
				arrow[y] = "-> ";
			}
			break;
		case '\r':
			check = false;
			return y;
		case '\b':
			if (name.size() >= 1) {
				name.pop_back();
				ps = dbConn.prepareStatement("SELECT MIN(NO) FROM report WHERE S_Name LIKE ?");
				ps->setString(1, "%" + name + "%");

				rs = ps->executeQuery();
				if (rs->next()) {
					arrow[y] = "  ";
					y = rs->getInt(1);
					arrow[y] = "-> ";
				}
			}
			break;
		default:
			if (c >= 'a' && c <= 'z' || (c >= 'A' && c <= 'Z' || c == ' ' || c == '.' || c == '/')) {
				name += c;

				ps = dbConn.prepareStatement("SELECT MIN(NO) FROM report WHERE S_Name LIKE ?");
				ps->setString(1, "%" + name + "%");

				rs = ps->executeQuery();
				if (rs->next()) {
					arrow[y] = "  ";
					y = rs->getInt(1);
					arrow[y] = "-> ";
				}

			}
			break;
		}

		if (c == '0') { return 0; }

		if (check) {




			system("cls");
			cout << "\t\t\t\t\t\tType Name to Search" << endl;
			cout << "\t\t\t\t\t\tNAME : " << name << endl << endl;
			cout << "\n\n" << setw(8) << "Student ID" << setw(40) << "Student Name" << setw(20) << "Student Telephone No " << endl;
			cout << "===================================================================" << endl << endl;

			for (int i = 1; i <= lastStudentID; i++) {
				ps = dbConn.prepareStatement("SELECT NO FROM report WHERE S_Name LIKE ? AND NO = ?");
				ps->setString(1, "%" + name + "%");
				ps->setInt(2, i);
				rs = ps->executeQuery();

				if (rs->next())
				{
					report = selectReportNO(rs->getInt(1));
					cout << arrow[i] << report->studentID << setw(40) << report->sName << setw(19) << report->sPhoneNo << endl;
				}


			}
			cout << "===================================================================" << endl << endl;
		}
	}

	return 1;
}

Report* ReportManager::selectStudent(string studentID)
{
	Report* report = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM report WHERE Student_ID = ?");

	ps->setString(1, studentID);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		report = new Report();

		report->studentID = rs->getString(2);
		report->sName = rs->getString(3);
		report->sPhoneNo = rs->getString(4);
		delete rs;
		delete ps;
		return report;
	}
	else
	{
		delete rs;
		delete ps;
		return 0;
	}
}

Report* ReportManager::selectReportNO(int no) {
	Report* report = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM report WHERE NO = ?");

	ps->setInt(1, no);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		report = new Report();

		report->studentID = rs->getString(2);
		report->sName = rs->getString(3);
		report->sPhoneNo = rs->getString(4);
		delete rs;
		delete ps;
		return report;
	}
	else
	{
		delete rs;
		delete ps;
		return 0;
	}
}