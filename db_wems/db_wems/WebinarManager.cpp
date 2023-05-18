#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Webinar.h"
#include "webinarManager.h"
#include <conio.h>

constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;

void WebinarManager::showAllWebinar()
{
	system("cls");
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM webinar");



	ResultSet* rs = ps->executeQuery();
	cout << "\t\t\t\t WEBINAR LIST" << endl;
	cout << "\n\n" << setw(8) << "Webinar ID" << setw(25) << "Webinar Title" << setw(45) << "Webinar Description" << endl;
	cout << "=============================================================================================================" << endl << endl;
	while (rs->next())
	{
		cout << "" << rs->getString(2) << setw(30) << rs->getString(3) << setw(20) <<""<<rs->getString(4)<< endl;

	}
	cout << "\n=============================================================================================================" << endl << endl;
}

int WebinarManager::insertWebinar(Webinar* webinar)
{
	system("cls");
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO webinar VALUES (?, ?, ?, ?)");

	ps->setInt(1, webinar->NO);
	ps->setString(2, webinar->webinarID);
	ps->setString(3, webinar->title);
	ps->setString(4, webinar->description);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}

Webinar* WebinarManager::selectWebinar(string webinarID)
{
	Webinar* webinar = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM webinar WHERE Webinar_ID = ?");

	ps->setString(1, webinarID);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		webinar = new Webinar();

		webinar->webinarID = rs->getString(2);
		webinar->title = rs->getString(3);
		webinar->description = rs->getString(4);

		delete rs;
		delete ps;
		return webinar;
	}
	else
	{
		delete rs;
		delete ps;
		return 0;
	}
}

Webinar* WebinarManager::selectWebinarNO(int no) {
	Webinar* webinar = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM webinar WHERE NO = ?");

	ps->setInt(1, no);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		webinar = new Webinar();

		webinar->webinarID = rs->getString(2);
		webinar->title = rs->getString(3);
		webinar->description = rs->getString(4);
		delete rs;
		delete ps;
		return webinar;
	}
	else
	{
		delete rs;
		delete ps;
		return 0;
	}
}

int WebinarManager::deleteWebinar(string ID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM webinar WHERE Webinar_ID = ? ");

	ps->setString(1, ID);

	int status = ps->executeUpdate();

	delete ps;
	return status;
}

int WebinarManager::searchWebinar(int lastWebinarID) {

	Webinar* webinar = new Webinar();
	DatabaseConnection dbConn;
	PreparedStatement* ps;
	ResultSet* rs;

	bool check = true;
	int y = 1;
	int c = 0;
	int NO = 0;
	string name = "";
	vector <string> arrow;
	for (int i = 0; i <= lastWebinarID; i++) {
		arrow.push_back("  ");
	}
	if (lastWebinarID != 0) {
		arrow[1] = "-> ";
	}



	system("cls");
	cout << "\t\t\t\t\t\tType Name to Search" << endl;
	cout << "\t\t\t\t\t\tName : " << name << endl << endl;
	cout << "\n\n" << setw(8) << "Webinar ID" << setw(25) << "Webinar Name" << setw(45) << "Webinar Description " << endl;
	cout << "=============================================================================================================" << endl << endl;

	for (int i = 1; i <= lastWebinarID; i++) {
		ps = dbConn.prepareStatement("SELECT NO FROM Webinar WHERE Webinar_Title LIKE ? AND NO = ?");
		ps->setString(1, "%" + name + "%");
		ps->setInt(2, i);
		rs = ps->executeQuery();

		if (rs->next())
		{
			webinar = selectWebinarNO(rs->getInt(1));
			cout << arrow[i] << webinar->webinarID << setw(30) << webinar->title << setw(20) <<""<< webinar->description << endl;
		}


	}
	cout << "=============================================================================================================" << endl << endl;


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
					ps = dbConn.prepareStatement("SELECT NO FROM webinar WHERE Webinar_Title LIKE ? AND NO = ?");
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
			if (y < lastWebinarID) {
				arrow[y] = "  ";
				int j = y;
				j++;
				bool c = true;
				while (c) {
					ps = dbConn.prepareStatement("SELECT NO FROM webinar WHERE Webinar_Title LIKE ? AND NO = ?");
					ps->setString(1, "%" + name + "%");
					ps->setInt(2, j);
					rs = ps->executeQuery();
					if (rs->next()) {
						y = j;
						c = false;
					}
					if (j == lastWebinarID) {
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
				ps = dbConn.prepareStatement("SELECT MIN(NO) FROM webinar WHERE Webinar_Title LIKE ?");
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

				ps = dbConn.prepareStatement("SELECT MIN(NO) FROM webinar WHERE Webinar_Title LIKE ?");
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
			cout << "\n\n" << setw(8) << "Webinar ID" << setw(25) << "Webinar Name" << setw(45) << "Webinar Description" << endl;
			cout << "===========================================================================================================" << endl << endl;

			for (int i = 1; i <= lastWebinarID; i++) {
				ps = dbConn.prepareStatement("SELECT NO FROM webinar WHERE Webinar_Title LIKE ? AND NO = ?");
				ps->setString(1, "%" + name + "%");
				ps->setInt(2, i);
				rs = ps->executeQuery();

				if (rs->next())
				{
					webinar = selectWebinarNO(rs->getInt(1));
					cout << arrow[i] << webinar->webinarID << setw(30) << webinar->title << setw(20)<<"" << webinar->description << endl;
				}


			}
			cout << "===========================================================================================================" << endl << endl;
		}
	}

	return 1;
}

int WebinarManager::updateWebinar(string ID, string att, string data)
{
	system("cls");
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE webinar SET Webinar_Title = (?) WHERE Webinar_ID = (?) ");

	if (att == "0")
	{
		ps = dbConn.prepareStatement("UPDATE webinar SET Webinar_Title = (?) WHERE Webinar_ID = (?) ");
	}
	else if (att == "1")
	{
		ps = dbConn.prepareStatement("UPDATE webinar SET Webinar_Description = (?) WHERE Webinar_ID = (?) ");
	}
	else
	{
		cout << "the attribute is not exist." << endl;
		system("pause");
		return 0;
	}
	ps->setString(1, data);
	ps->setString(2, ID);


	int status = ps->executeUpdate();

	delete ps;

	return status;
}
