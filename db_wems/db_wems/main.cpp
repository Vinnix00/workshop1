#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <mysql/jdbc.h>
#include <string>
#include <conio.h>
#include<iomanip>
#include<Windows.h>
#include <vector>
#include <thread>
#include <chrono>
#include<stdlib.h>
#include <stdio.h>      
#include <time.h>  

using namespace sql;
using namespace std;

#include "Committee.h"
#include "CommitteeManager.h"
#include "DatabaseConnection.h"
#include "Webinar.h"
#include "WebinarManager.h"
#include "Student.h"
#include "StudentManager.h"
#include "Report.h"
#include "ReportManager.h"

constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;

//for loop purpose
char input() {
	char a;
	if (_kbhit()) {
		a = _getch();
		return a;
	}
}

//Print date and time
void timeDate() {
	time_t timetoday;
	time(&timetoday);
	cout << asctime(localtime(&timetoday)) << endl;

}

//Welcome Interface
void welcome()
{
	cout << "\t\t\t************************************************************************" << endl;
	cout << "\t\t\t*                                                                      *" << endl;
	cout << "\t\t\t*                                                                      *" << endl;
	cout << "\t\t\t*                           WELCOME TO                                 *" << endl;
	cout << "\t\t\t*                                                                      *" << endl;
	cout << "\t\t\t*                 WEBINAR EVENT MANAGEMENT SYSTEM                      *" << endl;
	cout << "\t\t\t*                                                                      *" << endl;
	cout << "\t\t\t*                                                                      *" << endl;
	cout << "\t\t\t************************************************************************" << endl;
	system("pause");
	system("cls");
}

//Committee
int lastCommitteeID()
{
	
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select MAX(NO) from committee");

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		if (rs->getInt(1) == NULL)
		{
			return 0;
		}
		return rs->getInt(1);
	}

}

bool committeeLogin()
{

	system("CLS");
	CommitteeManager Manager;
	Committee* login = new Committee;

	bool check = true;
	while (check) {

		system("CLS");

		cout << endl << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t 			LOGIN COMMITTEE			 " << endl;
		cout << "\t\t\t							" << endl;
		cout << "\t\t\t			Committee ID : ";


		getline(cin, login->committeeID);
		while (login->committeeID == "") {
			getline(cin, login->committeeID);
		}
		system("cls");
		cout << endl << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t 			LOGIN COMMITTEE			 " << endl;
		cout << "\t\t\t							" << endl;
		cout << "\t\t\t			Committee ID : " << login->committeeID << endl;
		cout << "\t\t\t			Password  : ";

		string pass;
		int i = 0;
		char a;
		for (i = 0;;) {
			a = _getch();
			if (a >= 'a' && a <= 'z' || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9')) {

				pass += a;
				++i;
				cout << "*";

			}
			if (a == '\b' && i >= 1) {
				cout << "\b \b";
				--i;
			}
			if (a == '\r') {
				break;
			}

		}


		login->password = pass;
		if (login->password == "0") {
			return "0";
		}

		if (Manager.login(login))
		{
			check = false;
			system("cls");
			cout << "Login success" << endl;
			
		}
		else
		{
			check = true;
			cout << "Login fail" << endl;
		}
	}


}

void showAllCommittee()
{
	system("cls");
	CommitteeManager committee;

	committee.showAllCommittee();
	cout << endl << endl;
	system("pause");
	system("cls");
}

void committeeRegister()
{
	system("cls");

	string ID = "C0002";
	string lastID = to_string(lastCommitteeID() + 1);
	int k = 0;
	for (int i = 0; i < ID.size(); i++) {
		if (i > (ID.size() - 1) - lastID.size()) {
			ID[i] = lastID[k++];
		}
	}

	Committee* newcommittee = new Committee();

	newcommittee->NO = lastCommitteeID() + 1;
	newcommittee->committeeID = ID;

ANAME:

	system("cls");
	cout << "\t\t\t\t\t Maximun character is 30" << endl;
	cout << "\t\t\t\t\t Input 0 to return" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  COMMITTEE REGISTER			" << endl;
	cout << "\t\t\t 	Name			: ";

	newcommittee->NO = lastCommitteeID() + 1;
	newcommittee->committeeID = ID;


	getline(cin, newcommittee->name);
	if (newcommittee->name == "0") {
		return;
	}
	if (newcommittee->name.size() > 30) {
		cout << "\t\t\t\t\t MAX CHARACTER IS 30" << endl;
		system("pause");
		goto ANAME;
	}
	else if (newcommittee->name.size() == 0) {
		cout << "\t\t\t\t\t PLEASE INSERT SOMETHING" << endl;
		system("pause");
		goto ANAME;
	}


APASSWORD:
	system("cls");
	cout << "\t\t\t\t\t Make sure to remember your password" << endl;
	cout << "\t\t\t\t\t Input 0 to return" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  COMMITTEE REGISTER			" << endl;
	cout << "\t\t\t 	Name			: " << newcommittee->name << endl;
	cout << "\t\t\t 	Password		: ";

	getline(cin, newcommittee->password);
	if (newcommittee->password == "0") {
		return;
	}

	system("cls");
	cout << "\t\t\t\t\t Type again your password" << endl << endl;

	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  COMMITTEE REGISTER			" << endl;
	cout << "\t\t\t 	Name			: " << newcommittee->name << endl;
	cout << "\t\t\t 	Password		: " << "***..." << endl;

	cout << "\n\n\t\t\tConfirm Password : ";

	string cpass;
	getline(cin, cpass);
	if (cpass != newcommittee->password) {
		system("cls");
		cout << "\t\t\t\t\t !!!!!!!" << endl << endl;

		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t 			  COMMITTEE REGISTER			" << endl;
		cout << "\t\t\t 	Name			: " << newcommittee->name << endl;
		cout << "\t\t\t 	Password		: " << "***..." << endl;

		cout << "\n\n\t\t\tConfirm Password : ***..." << endl;
		cout << "\n\t\t\t\tPASSWORD IS NOT SAME" << endl;
		system("pause");
		goto APASSWORD;

	}

ANOTEL:
	system("cls");
	cout << "\t\t\t\t\t Insert a valid phone number" << endl;
	cout << "\t\t\t\t\t Input 0 to return" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  COMMITTEE REGISTER			" << endl;
	cout << "\t\t\t 	Name			: " << newcommittee->name << endl;
	cout << "\t\t\t 	Password		: " << "***..." << endl;
	cout << "\t\t\t 	Phone No		: ";

	bool check = false;
	getline(cin, newcommittee->phoneNo);
	if (newcommittee->phoneNo == "0") {
		return;
	}
	if (isdigit(newcommittee->phoneNo[0]) && newcommittee->phoneNo[0] == '0') {
		int intphoneNo = stoi(newcommittee->phoneNo);
		newcommittee->phoneNo = "0" + to_string(intphoneNo);
	}
	else { check = true; }
	if (newcommittee->phoneNo.size() != 10 || check) {
		cout << "\t\t\t\t\t INVALID TELEPHONE NUMBER" << endl;
		cout << "\t\t\t\t\t MUST BE DIGIT" << endl;
		system("pause");
		goto ANOTEL;
	}


	CommitteeManager committeeManage;
	int status = committeeManage.insertCommittee(newcommittee);

	if (status != 0)
		cout << "\n\n\t\t\tSuccessfully added a new committee with no ID = " << ID << endl << endl;
	else
		cout << "\n\n\t\t\tUnable to add a new committee." << endl;
	delete newcommittee;
	system("pause");

}

void updateCommittee()
{
	system("cls");
START:
	system("CLS");
	bool stay = false;

	CommitteeManager manage;
	Committee* committee;
	int y = 1;
	int c = 0;

	int z = manage.searchCommittee(lastCommitteeID());

	if (z == 0) {
		return;
	}

AGAIN:

	committee = manage.selectCommitteeNO(z);
	system("cls");
	cout << "\t\t\t\tChoose Data to Update.Press 0 to return" << endl << endl;
	cout << endl;
	cout << "\t==============================================================================================" << endl << endl;
	cout << "\t\t\t\t->Name			: " << committee->name << endl;
	cout << "\t\t\t\t  Password		: ***...." << endl;
	cout << "\t\t\t\t  Phone No	    : " << committee->phoneNo << endl;
	cout << "\n\t==============================================================================================" << endl << endl;

	y = 0;
	bool check = true;
	while (check) {
		c = 0;

		switch ((c = _getch())) {
		case KEY_UP:

			y--;

			break;
		case KEY_DOWN:

			y++;

			break;
		case '\r':
			check = false;
		default:
			// not arrow
			break;
		}
		if (c == '0') {
			goto START;
		}
		if (y < 0) {
			y = 0;

		}
		if (y > 2) {
			y = 2;

		}
		if (y == 0) {
			system("cls");
			cout << "\t\t\t\tChoose Data to Update.Press 0 to return" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t->Name			: " << committee->name << endl;
			cout << "\t\t\t\t  Password		: ***...." << endl;
			cout << "\t\t\t\t  Phone No 	: " << committee->phoneNo << endl;
			cout << "\n\t==============================================================================================" << endl << endl;
		}
		else if (y == 1) {
			system("cls");
			cout << "\t\t\t\tChoose Data to Update.Press 0 to return" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t  Name			: " << committee->name << endl;
			cout << "\t\t\t\t->Password		: ***...." << endl;
			cout << "\t\t\t\t  Phone No 	: " << committee->phoneNo << endl;
			cout << "\n\t==============================================================================================" << endl << endl;
		}
		else if (y == 2) {
			system("cls");
			cout << "\t\t\t\tChoose Data to Update.Press 0 to return" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t  Name			: " << committee->name << endl;
			cout << "\t\t\t\t  Password		: ***...." << endl;
			cout << "\t\t\t\t->Phone No  	: " << committee->phoneNo << endl;
			cout << "\n\t==============================================================================================" << endl << endl;
		}

	}

		system("cls");
		string update;

		if (y == 0) {
			cout << "\t\t\t\tUpdate Name" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t  Name			: ";
			while (update == "") {
				getline(cin, update);
			}
		}
		else if (y == 1) {
			cout << "\t\t\t\tUpdate Password" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t  Password			: ";
			while (update == "") {
				getline(cin, update);
			}
		}
		else if (y == 2) {
			cout << "\t\t\t\tUpdate Phone No" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t  Phone No		: ";
			while (update == "") {
				getline(cin, update);
			}
		}

	if (manage.updateCommittee(committee->committeeID, to_string(y), update)) {
		cout << "\t\t\t\tUPDATE SUCCESS" << endl;
	}
	else {
		cout << "\t\t\t\tUPDATE FAILED" << endl;
	}
	system("pause");
	goto AGAIN;


	return;
}

void deleteCommittee()
{
	system("cls");
	CommitteeManager manage;
	Committee* committee = new Committee();
	string option;
	int y = manage.searchCommittee(lastCommitteeID());
	if (y == 0) {
		return;
	}

	do {
		committee = manage.selectCommitteeNO(y);
		system("cls");
		cout << "\t\t\t\t" << endl << endl;
		cout << endl;
		cout << "\t==============================================================================================" << endl << endl;
		cout << "\t\t\t\t  Name			: " <<committee->name << endl;
		cout << "\t\t\t\t  Password		: ***...." << endl;
		cout << "\t\t\t\t  Telephone Number	: " << committee->phoneNo << endl;
		cout << "\n\t==============================================================================================" << endl << endl;


		cout << "\t\t\tCONFIRM TO DELETE COMMITTEE (Y/N) : ";
		getline(cin, option);
		if (!(option == "N" || option == "n" || option == "y" || option == "Y")) {
			cout << "\n\t\t\t INSERT APPROPIATE INPUT";
			boost::detail::Sleep(1000);
		}

	} while (!(option == "N" || option == "n" || option == "y" || option == "Y"));
	if (option == "N" || option == "n") {
		return;
	}
	int status = manage.deleteCommittee(committee->committeeID);
	if (status) {
		cout << "\n\t\t\tdelete succeed." << endl;
	}
	else {
		cout << "\n\t\t\tdelete failed." << endl;
	}
	system("pause");

}


//Webinar
void showAllWebinar()
{
	system("cls");
	WebinarManager webinar;

	webinar.showAllWebinar();
	cout << endl << endl;
	system("pause");
	system("cls");
}

int lastWebinarID()
{
	system("cls");
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select MAX(NO) from webinar");

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		if (rs->getInt(1) == NULL)
		{
			return 0;
		}
		return rs->getInt(1);
	}

}

void webinarRegister()
{
	system("cls");
	string ID = "2021-002";
	string lastID = to_string(lastWebinarID() + 1);
	int k = 0;
	for (int i = 0; i < ID.size(); i++) {
		if (i > (ID.size() - 1) - lastID.size()) {
			ID[i] = lastID[k++];
		}
	}

	Webinar* newwebinar = new Webinar();

	newwebinar->NO = lastWebinarID() + 1;
	newwebinar->webinarID = ID;

TITLE:
	system("cls");
	cout << "\t\t\t\t\t Maximun character is 100" << endl;
	cout << "\t\t\t\t\t Input 0 to return" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  INSERT WEBINAR			" << endl;
	cout << "\t\t\t 	TITLE			: ";

	newwebinar->NO = lastWebinarID() + 1;
	newwebinar->webinarID = ID;


	getline(cin, newwebinar->title);
	if (newwebinar->title == "0") {
		return;
	}
	if (newwebinar->title.size() > 100) {
		cout << "\t\t\t\t\t MAX CHARACTER IS 100" << endl;
		system("pause");
		goto TITLE;
	}
	else if (newwebinar->title.size() == 0) {
		cout << "\t\t\t\t\t PLEASE INSERT SOMETHING" << endl;
		system("pause");
		goto TITLE;
	}


DESCRIPTION:

	system("cls");
	cout << "\t\t\t\t\t Maximun word is 1000" << endl;
	cout << "\t\t\t\t\t Input 0 to return" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  INSERT WEBINAR			" << endl;
	cout << "\t\t\t 	TITLE			: "<<newwebinar->title<<endl;
	cout << "\t\t\t 	DESCRIPTION	    :          "<<endl;


	getline(cin, newwebinar->description);
	if (newwebinar->description == "0") {
		return;
	}
	if (newwebinar->description.size() > 1000) {
		cout << "\t\t\t\t\t MAX WORD IS 1000" << endl;
		system("pause");
		goto DESCRIPTION;
	}
	else if (newwebinar->description.size() == 0) {
		cout << "\t\t\t\t\t PLEASE INSERT SOMETHING" << endl;
		system("pause");
		goto DESCRIPTION;
	}



	WebinarManager webinarManage;
	int status = webinarManage.insertWebinar(newwebinar);

	if (status != 0)
		cout << "\n\n\t\t\tSuccessfully added a new webinar with no ID = " << ID << endl << endl;
	else
		cout << "\n\n\t\t\tUnable to add a new committee." << endl;
	delete newwebinar;
	system("pause");

}

void deleteWebinar()
{
	system("cls");
	WebinarManager manage;
	Webinar* webinar = new Webinar();
	string option;
	int y = manage.searchWebinar(lastWebinarID());
	if (y == 0) {
		return;
	}

	do {
		webinar = manage.selectWebinarNO(y);
		system("cls");
		cout << "\t\t\t\t" << endl << endl;
		cout << endl;
		cout << "\t==============================================================================================" << endl << endl;
		cout << "\t\t\t\t  Title			: " << webinar->title << endl;
		cout << "\t\t\t\t  Description  	: " << webinar->description << endl;
		cout << "\n\t==============================================================================================" << endl << endl;


		cout << "\t\t\tCONFIRM TO DELETE WEBINAR (Y/N) : ";
		getline(cin, option);
		if (!(option == "N" || option == "n" || option == "y" || option == "Y")) {
			cout << "\n\t\t\t INSERT APPROPIATE INPUT";
			boost::detail::Sleep(1000);
		}

	} while (!(option == "N" || option == "n" || option == "y" || option == "Y"));
	if (option == "N" || option == "n") {
		return;
	}
	int status = manage.deleteWebinar(webinar->webinarID);
	if (status) {
		cout << "\n\t\t\tdelete successfully." << endl;
	}
	else {
		cout << "\n\t\t\tdelete failed." << endl;
	}
	system("pause");
	system("cls");

}

void updateWebinar()
{
	system("cls");
START:
	system("CLS");
	bool stay = false;

	WebinarManager manage;
	Webinar* webinar;
	int y = 1;
	int c = 0;

	int z = manage.searchWebinar(lastWebinarID());

	if (z == 0) {
		return;
	}

AGAIN:

	webinar = manage.selectWebinarNO(z);
	system("cls");
	cout << "\t\t\t\tChoose Data to Update.Press 0 to return" << endl << endl;
	cout << endl;
	cout << "\t==============================================================================================" << endl << endl;
	cout << "\t\t\t\t->Title			: " << webinar->title << endl;
	cout << "\t\t\t\t  Description	    : " << webinar->description << endl;
	cout << "\n\t==============================================================================================" << endl << endl;

	y = 0;
	bool check = true;
	while (check) {
		c = 0;

		switch ((c = _getch())) {
		case KEY_UP:

			y--;

			break;
		case KEY_DOWN:

			y++;

			break;
		case '\r':
			check = false;
		default:
			// not arrow
			break;
		}
		if (c == '0') {
			goto START;
		}
		if (y < 0) {
			y = 0;

		}
		if (y > 2) {
			y = 2;

		}
		if (y == 0) {
			system("cls");
			cout << "\t\t\t\tChoose Data to Update.Press 0 to return" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t->Title			: " << webinar->title << endl;
			cout << "\t\t\t\t  Description  	: " << webinar->description << endl;
			cout << "\n\t==============================================================================================" << endl << endl;
		}
		else if (y == 1) {
			system("cls");
			cout << "\t\t\t\tChoose Data to Update.Press 0 to return" << endl << endl;
			cout << endl;
			cout << "\t==============================================================================================" << endl << endl;
			cout << "\t\t\t\t  Title			: " << webinar->title << endl;
			cout << "\t\t\t\t->Description  	: " << webinar->description << endl;
			cout << "\n\t==============================================================================================" << endl << endl;
		}

		else {}

	}
	system("cls");
	string update;
	if (y == 0) {
		cout << "\t\t\t\tUpdate Title" << endl << endl;
		cout << endl;
		cout << "\t==============================================================================================" << endl << endl;
		cout << "\t\t\t\t  Title			: ";
		while (update == "") {
			getline(cin, update);
		}
	}
	else if (y == 1) {
		cout << "\t\t\t\tUpdate Description" << endl << endl;
		cout << endl;
		cout << "\t==============================================================================================" << endl << endl;
		cout << "\t\t\t\t  Description		: ";
		while (update == "") {
			getline(cin, update);
		}
	}

	if (manage.updateWebinar(webinar->webinarID, to_string(y), update)) {
		cout << "\t\t\t\tUPDATE SUCCESS" << endl;
	}
	else {
		cout << "\t\t\t\tUPDATE FAILED" << endl;
	}
	system("pause");
	goto AGAIN;


	return;
}

//Generate report
void reportGenerate()
{
	system("cls");
	ReportManager report;

	report.reportGenerate();
	cout << endl << endl;
	system("pause");
	system("cls");
}

//Student
bool studentLogin()
{

	system("CLS");
	StudentManager Manager;
	Student* login = new Student;

	bool check = true;
	while (check) {

		system("CLS");

		cout << endl << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t 			LOGIN STUDENT			 " << endl;
		cout << "\t\t\t							" << endl;
		cout << "\t\t\t			Student ID : ";



		getline(cin, login->studentID);
		while (login->studentID == "") {
			getline(cin, login->studentID);
		}
		system("cls");
		cout << endl << endl;
		cout << "\t\t\t#################################################################" << endl;
		cout << "\t\t\t 			LOGIN STUDENT			 " << endl;
		cout << "\t\t\t							" << endl;
		cout << "\t\t\t			Student ID : " << login->studentID << endl;
		cout << "\t\t\t			Password  : ";

		string pass;
		int i = 0;
		char a;
		for (i = 0;;) {
			a = _getch();
			if (a >= 'a' && a <= 'z' || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9')) {

				pass += a;
				++i;
				cout << "*";

			}
			if (a == '\b' && i >= 1) {
				cout << "\b \b";
				--i;
			}
			if (a == '\r') {
				break;
			}

		}


		login->password = pass;
		if (login->password == "0") {
			return "0";
		}

		if (Manager.login(login))
		{
			check = false;
			system("cls");
			cout << "Login success" << endl;

		}
		else
		{
			check = true;
			cout << "Login fail" << endl;
		}
	}


}

int lastStudentID()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("Select MAX(NO) from report");

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		if (rs->getInt(1) == NULL)
		{
			return 0;
		}
		return rs->getInt(1);
	}

}

void studentRegisterWebinar()
{
	system("cls");
	int choice;
	showAllWebinar();
	cout << "==========================================================================================" << endl;
	cout << "Please choose the webinar that you want to register" << endl;
	cin >> choice;

	system("cls");

	string ID = "B0320106";
	string lastID = to_string(lastStudentID() + 1);
	int k = 0;
	for (int i = 0; i < ID.size(); i++) {
		if (i > (ID.size() - 1) - lastID.size()) {
			ID[i] = lastID[k++];
		}
	}

	Report* newreport = new Report();

	newreport->NO = lastStudentID() + 1;
	newreport->studentID = ID;

ANAME:

	system("cls");
	cout << "\t\t\t\t\t Maximun character is 30" << endl;
	cout << "\t\t\t\t\t Input 0 to return" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  WEBINAR REGISTER			" << endl;
	cout << "\t\t\t 	Name			: ";

	newreport->NO = lastStudentID() + 1;
	newreport->studentID = ID;


	getline(cin, newreport->sName);
	if (newreport->sName == "0") {
		return;
	}
	if (newreport->sName.size() > 30) {
		cout << "\t\t\t\t\t MAX CHARACTER IS 30" << endl;
		system("pause");
		goto ANAME;
	}
	else if (newreport->sName.size() == 0) {
		cout << "\t\t\t\t\t PLEASE INSERT SOMETHING" << endl;
		system("pause");
		goto ANAME;
	}

ANOTEL:
	system("cls");
	cout << "\t\t\t\t\t Insert a valid phone number" << endl;
	cout << "\t\t\t\t\t Input 0 to return" << endl;
	cout << "\t\t\t#################################################################" << endl;
	cout << "\t\t\t 			  WEBINAR REGISTER			" << endl;
	cout << "\t\t\t 	Name			: " << newreport->sName << endl;
	cout << "\t\t\t 	Telephone No	: ";

	bool check = false;
	getline(cin, newreport->sPhoneNo);
	if (newreport->sPhoneNo == "0") {
		return;
	}
	if (isdigit(newreport->sPhoneNo[0]) && newreport->sPhoneNo[0] == '0') {
		int intphoneNo = stoi(newreport->sPhoneNo);
		newreport->sPhoneNo = "0" + to_string(intphoneNo);
	}
	else { check = true; }
	if (newreport->sPhoneNo.size() != 10 || check) {
		cout << "\t\t\t\t\t INVALID TELEPHONE NUMBER" << endl;
		cout << "\t\t\t\t\t MUST BE DIGIT" << endl;
		system("pause");
		goto ANOTEL;
	}


	ReportManager reportManage;
	int status = reportManage.studentRegisterWebinar(newreport);

	if (status != 0)
		cout << "\n\n\t\t\tSuccessfully register"<< endl << endl;
	else
		cout << "\n\n\t\t\tUnable register." << endl;
	delete newreport;
	system("pause");

}

//Function header
void committeeInterface();
void studentInterface();


void choiceGo()
{
	system("cls");
MAIN:
	int choices;
	system("cls");
	welcome();
	timeDate();
	cout << "Login as: " << endl << "1. Committee " << endl << "2. Student " << endl << "PRESS 3 TO EXIT THE SYSTEM" << endl;
	cin >> choices;
	system("cls");
CHOICE:
	if (choices == 1)
	{
		committeeLogin();
		committeeInterface();
		system("cls");
	}
	else if (choices == 2)
	{
		studentLogin();
		studentInterface();
	}
	else if (choices == 3)
	{
		exit(0);
	}
	else
	{
		system("cls");
		cout << "Invalid number! Please enter again." << endl;
		goto MAIN;

	}
}

//What committee can do
void committeeInterface()
{
	system("cls");
START:
	system("cls");
	int choice;
	cout << "\t\t\t************************************************************************" << endl;
	cout << "\t\t\t*                                                                      *" << endl;
	cout << "\t\t\t*                     WEBINAR EVENT MANAGEMENT SYSTEM                  *" << endl;
	cout << "\t\t\t*                                                                      *" << endl;
	cout << "\t\t\t************************************************************************" << endl;
	cout << "\t\t\tLogin As Committee:" << endl; 
    cout << "Please choose the following operation:" << endl;
	cout << "1. Add a new committee" << endl;
	cout << "2. Delete committee" << endl;
	cout << "3. Update committee's info" << endl;
	cout << "4. View all committee" << endl;
	cout << "5. Add a new webinar" << endl;
	cout << "6. Delete webinar" << endl;
	cout << "7. Update webinar's info" << endl;
	cout << "8. View all webinar" << endl;
	cout << "9. Generate a report" << endl;
	cout << "10. Logout" << endl;
	cin >> choice;
	CHOICE:
	system("cls");
	switch(choice)
	{
	case 1: 
		system("cls");
		committeeRegister();
		break;

	case 2: 
		system("cls");
		deleteCommittee();
		break;

	case 3: 
		system("cls");
		updateCommittee();
		break;

	case 4: 
		system("cls");
		showAllCommittee();
		break;

	case 5:
		system("cls");
		webinarRegister();
		break;

	case 6:
		system("cls");
		deleteWebinar();
		break;

	case 7:
		system("cls");
		updateWebinar();
		break;

	case 8:
		system("cls");
		showAllWebinar();
		break;

	case 9:
		system("cls");
		reportGenerate();
		break;

	case 10:
		system("cls");
		choiceGo();
		break;

	default: 
		system("cls");
		cout << "Invalid choice! Please choose again." << endl;
		goto START;

	}
	goto START;
}

//What student can do
void studentInterface()
{
	MAIN:
	system("cls");
	int choice;
	cout << "\t\t\t************************************************************************" << endl;
	cout << "\t\t\t*                                                                      *" << endl;
	cout << "\t\t\t*                     WEBINAR EVENT MANAGEMENT SYSTEM                  *" << endl;
	cout << "\t\t\t*                                                                      *" << endl;
	cout << "\t\t\t************************************************************************" << endl;
	cout << "\t\t\tLogin As Student:" << endl;
	cout << "Please choose the following operation:" << endl;
	cout << "1. Register a webinar" << endl;
	cout << "2. Logout" << endl;
	cin >> choice;
	system("cls");
	CHOICE:
	switch (choice)
	{
	case 1:
		system("cls");
		studentRegisterWebinar();
		break;

	case 2:
		system("cls");
		choiceGo();
		break;

	default:
		system("cls");
		cout << "Invalid choice! Please choose again." << endl;
		goto MAIN;

	}
	goto MAIN;
}

int main()
{
	choiceGo();

	return 0;
}