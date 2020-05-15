#include <iostream>
using namespace std;
#include "Identity.h"
#include <fstream>
#include <string>
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "Manager.h"

//enter student's operation menu
void studentMenu(Identity* &student) {
	while (true) {
		student->operMenu();
		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1) {//make reservation
			stu->applyOrder();
		} else if (select == 2) {//check Your Reservation
			stu->showMyOrder();
		} else if (select == 3) {//check all reservations
			stu->showAllOrder();
		} else if (select == 4) {//Cancel Reservation
			stu->cancelOrder();
		} else {
			delete student;
			cout << "Log off Successfully" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//enter administrator's operation menu
void managerMenu(Identity*& manager) {
	while (true) {
		manager->operMenu();
		Manager* man = (Manager*)manager;
		int select = 0;
		cin >> select;
		if (select == 1) {//Add new account
			cout << "Add Account" << endl;
			man->addPerson();
		} else if (select == 2) {//Check account
			cout << "Check Account" << endl;
			man->showPerson();
		} else if (select == 3) {//check Room
			cout << "Check Room" << endl;
			man->showComputer();
		} else if (select == 4) {//empty reservations
			cout << "Empty Reservations" << endl;
			man->cleanFile();
		} else {
			delete manager;
			cout << "Log off successfully" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void LoginIn(string fileName, int type) {
	Identity* person = NULL;

	ifstream ifs;
	ifs.open(fileName, ios::in);

	if (!ifs.is_open()) {
		cout << "File not exist!" << endl;
		ifs.close();
		return;
	}

	int id = 0;
	string name;
	string pwd;

	if (type == 1) {//student
		cout << "Please enter your student ID: " << endl;
		cin >> id;
	}
	else if(type==2){
		cout << "Please enter your employee ID: " << endl;
		cin >> id;
	}

	cout << "Please enter your username: " << endl;
	cin >> name;

	cout << "Please enter password: " << endl;
	cin >> pwd;

	if (type == 1) {
		int fId;//read from file
		string fName;//read from file
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (fId == id && fName == name && fPwd == pwd){
				cout << "Login successfully as student." << endl;
				system("pause");
				system("cls");
				person = new Student(id,name,pwd);
				//enter next level menu
				studentMenu(person);
				return;
			}
		}

	} else if (type == 2) {
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName&&ifs >> fPwd) {
			if (fId == id && fName == name && fPwd == pwd) {
				cout << "Login successfully as Professor."<<endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//enter teacher's next level menu

				return;
			}
		}
	
	} else if (type == 3) {
		string fName;//read from txt file
		string fPwd;
		while (ifs >> fName && ifs >> fPwd) {
			if (name == fName && pwd == fPwd) {
				cout << "Login successfully as administrator." << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				//enter administrator's next level menu
				managerMenu(person);
				return;
			}
		}
	}

	cout << "Failed to log in!" << endl;
	system("pause");
	system("cls");
	return;


}
int main() {
	int select = 0;

	while (true) {
		cout << "======================  Welcome to Room Reservation System  ====================="
			<< endl;
		cout << endl << "Please enter your choice" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.Student            |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.Professor          |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.Administrator      |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.Exist		|\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "Enter your choice: ";

		cin >> select;
		switch (select) {
		case 1://student
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://professor
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://administrator
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://exist
			cout << "Looking forward to see you next time!" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "Entered wrong information, please try again!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	
	system("pause");
	return 0;
}