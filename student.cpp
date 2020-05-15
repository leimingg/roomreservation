#include "student.h"

Student::Student() {
}

Student::Student(int id, string name, string pwd) {
	this->m_ID = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId&&ifs>>com.m_MaxNum) {
		vCom.push_back(com);
	}
	ifs.close();
}

void Student::operMenu() {
	cout << "Welcome£º" << this->m_Name << " Login£¡" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          1.Make Reservation     |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          2.Check My Reservation |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          3.Check All Reservation|\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          4.Cancel Reservation   |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          0.Log Off              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "Please enter your choice£º " << endl;
}

void Student::applyOrder() {
	cout << "Computer rooms open from Monday to Friday!" << endl;
	cout << "Please enter which day you want to reserve:" << endl;
	cout << "1.Monday" << endl;
	cout << "2.Tuesday" << endl;
	cout << "3.Wesday" << endl;
	cout << "4.Thursday" << endl;
	cout << "5.Friday" << endl;

	int date = 0;
	int interval = 0;//afternoon/morning
	int room = 0;

	while (true) {
		cin >> date;
		if (date >= 1 && date <= 5) {
			break;
		}
		cout << "Entered wrong information, please enter again." << endl;

	}
	cout << "Please enter the time interval you want to reserve: " << endl;
	cout << "1.Morning" << endl;
	cout << "2.Afternoon" << endl;

	while (true) {
		cin >> interval;
		if (interval >= 1 && interval <= 2) {
			break;
		}
		cout << "Entered wrong information, please enter again." << endl;
	}

	cout << "Please enter computer room number: " << endl;
	for (int i = 0;i < vCom.size();i++) {
		cout << vCom[i].m_ComId << " Computer Room Capacity: " << vCom[i].m_MaxNum << endl;
	}
	
	while (true) {
		cin >> room;
		if (room >= 1 && room <= 3) {
			break;
		}
		cout << "Entered wrong information, please enter again." << endl;
	}
	cout << "Made reservation successfully! Your reservation is under review." << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
		ofs << "date:" << date << " ";
		ofs << "interval:" << interval << " ";
		ofs << "stuId:" << this->m_ID << " ";
		ofs << "stuName:" << this->m_Name << " ";
		ofs << "roomId:" << room << " ";
		ofs << "status:" << 1 << " " << endl;
		ofs.close();
		system("pause");
		system("cls");
	
}

void Student::showMyOrder() {
	OrderFile of;
}

void Student::showAllOrder() {
}

void Student::cancelOrder() {

}