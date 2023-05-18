#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Committee.h"
#include "CommitteeManager.h"
#include <conio.h>


constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;

bool CommitteeManager::login(Committee* committee)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Committee WHERE Committee_ID = ?");
	ps->setString(1, committee->committeeID);
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
		ps = dbConn.prepareStatement("SELECT * FROM committee WHERE Committee_ID = ? AND Committee_Password = ?");
		ps->setString(1, committee->committeeID);
		ps->setString(2, committee->password);
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

void CommitteeManager::showAllCommittee()
{
	system("cls");
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM committee");



	ResultSet* rs = ps->executeQuery();
	cout << "\t\t\t\t COMMITTEE LIST" << endl;
	cout << "\n\n" << setw(8) << "Committee ID" << setw(40) << "Committee Name" << setw(20) << "Phone Number " << endl;
	cout << "===================================================================" << endl << endl;
	while (rs->next())
	{
		cout << "" << rs->getString(2) << setw(40) << rs->getString(3) << setw(19) << rs->getString(4) << endl;

	}
	cout << "\n===================================================================" << endl << endl;
}


int CommitteeManager::insertCommittee(Committee* committee)
{
	system("cls");
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Committee VALUES (?, ?, ?, ?, ?)");
	
	ps->setInt(1, committee->NO);
	ps->setString(2, committee->committeeID);
	ps->setString(3, committee->name);
	ps->setString(4, committee->phoneNo);
	ps->setString(5, committee->password);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int CommitteeManager::updateCommittee(string ID, string att, string data)
{
	system("cls");
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE committee SET Committee_Name = (?) WHERE Committee_ID = (?) ");

	if (att == "0")
	{
		ps = dbConn.prepareStatement("UPDATE committee SET Committee_Name = (?) WHERE Committee_ID = (?) ");
	}
	else if (att == "1")
	{
		ps = dbConn.prepareStatement("UPDATE committee SET Committee_Password = (?) WHERE Committee_ID = (?) ");
	}
	else if (att == "2")
	{
		ps = dbConn.prepareStatement("UPDATE committee SET Committee_Phone_No = (?) WHERE Committee_ID = (?) ");
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

Committee* CommitteeManager::selectCommittee(string committeeID)
{
	Committee* committee = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM committee WHERE Committee_ID = ?");

	ps->setString(1, committeeID);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		committee = new Committee();

		committee->committeeID = rs->getString(2);
		committee->name = rs->getString(3);
		committee->password = rs->getString(5);
		committee->phoneNo = rs->getString(4);
		delete rs;
		delete ps;
		return committee;
	}
	else
	{
		delete rs;
		delete ps;
		return 0;
	}
}

Committee* CommitteeManager::selectCommitteeNO(int no) {
	Committee* committee = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM committee WHERE NO = ?");

	ps->setInt(1, no);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		committee = new Committee();

		committee->committeeID = rs->getString(2);
		committee->name = rs->getString(3);
		committee->password = rs->getString(5);
		committee->phoneNo = rs->getString(4);
		delete rs;
		delete ps;
		return committee;
	}
	else
	{
		delete rs;
		delete ps;
		return 0;
	}
}

int CommitteeManager::deleteCommittee(string ID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM committee WHERE Committee_ID = ? ");

	ps->setString(1, ID);

	int status = ps->executeUpdate();

	delete ps;
	return status;
}

int CommitteeManager::searchCommittee(int lastCommitteeID) {

	Committee* committee = new Committee();
	DatabaseConnection dbConn;
	PreparedStatement* ps;
	ResultSet* rs;

	bool check = true;
	int y = 1;
	int c = 0;
	int NO = 0;
	string name = "";
	vector <string> arrow;
	for (int i = 0; i <= lastCommitteeID; i++) {
		arrow.push_back("  ");
	}
	if (lastCommitteeID != 0) {
		arrow[1] = "-> ";
	}



	system("cls");
	cout << "\t\t\t\t\t\tType Name to Search" << endl;
	cout << "\t\t\t\t\t\tNAME : " << name << endl << endl;
	cout << "\n\n" << setw(8) << "Committee ID" << setw(40) << "Committee Name" << setw(20) << "Committee Phone No " << endl;
	cout << "===================================================================" << endl << endl;

	for (int i = 1; i <= lastCommitteeID; i++) {
		ps = dbConn.prepareStatement("SELECT NO FROM Committee WHERE Committee_Name LIKE ? AND NO = ?");
		ps->setString(1, "%" + name + "%");
		ps->setInt(2, i);
		rs = ps->executeQuery();

		if (rs->next())
		{
			committee = selectCommitteeNO(rs->getInt(1));
			cout << arrow[i] << committee->committeeID << setw(40) << committee->name << setw(19) << committee->phoneNo << endl;
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
					ps = dbConn.prepareStatement("SELECT NO FROM committee WHERE Committee_Name LIKE ? AND NO = ?");
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
			if (y < lastCommitteeID) {
				arrow[y] = "  ";
				int j = y;
				j++;
				bool c = true;
				while (c) {
					ps = dbConn.prepareStatement("SELECT NO FROM committee WHERE Committee_Name LIKE ? AND NO = ?");
					ps->setString(1, "%" + name + "%");
					ps->setInt(2, j);
					rs = ps->executeQuery();
					if (rs->next()) {
						y = j;
						c = false;
					}
					if (j == lastCommitteeID) {
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
				ps = dbConn.prepareStatement("SELECT MIN(NO) FROM committee WHERE Committee_Name LIKE ?");
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

				ps = dbConn.prepareStatement("SELECT MIN(NO) FROM committee WHERE Committee_Name LIKE ?");
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
			cout << "\n\n" << setw(8) << "Committee ID" << setw(40) << "Committee Name" << setw(20) << "Committee Phone No " << endl;
			cout << "===================================================================" << endl << endl;

			for (int i = 1; i <= lastCommitteeID; i++) {
				ps = dbConn.prepareStatement("SELECT NO FROM committee WHERE Committee_Name LIKE ? AND NO = ?");
				ps->setString(1, "%" + name + "%");
				ps->setInt(2, i);
				rs = ps->executeQuery();

				if (rs->next())
				{
					committee = selectCommitteeNO(rs->getInt(1));
					cout << arrow[i] << committee->committeeID << setw(40) << committee->name << setw(19) << committee->phoneNo << endl;
				}


			}
			cout << "===================================================================" << endl << endl;
		}
	}

	return 1;
}
