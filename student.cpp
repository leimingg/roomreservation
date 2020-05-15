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
	if (of.m_Size == 0) {
		cout << "No Reservation!" << endl;
		system("pause");
		system("cls");
		return;
	}
	//string->int: strint->.c_str()->const char*->atoi(const char*)->int
	for (int i = 0;i < of.m_Size;i++) {
		if (this->m_ID == atoi(of.m_orderData[i]["stuId"].c_str())) {
			cout << "Reservation date: " << of.m_orderData[i]["date"];
			cout << " interval: " << (of.m_orderData[i]["interval"] == "1" ? "Morning" : "Afternoon");
			cout << " Computer Room#:" << of.m_orderData[i]["roomId"];
			string status = "Status: ";
			//1 in review 2 Reserved  -1 Failed 0 cancelled
			if (of.m_orderData[i]["status"] == "1") {
				status += "In review";
			} else if(of.m_orderData[i]["status"] == "2") {
				status += "Reserved";
			} else if (of.m_orderData[i]["status"] == "-1") {
				status += "Failed. Reservation was not approved";
			} else if (of.m_orderData[i]["status"] == "0") {
				status += "Reservation Cancelled";
			}
			cout << status << endl;
		}
	}
	cout << " " << endl;
	system("pause");
	system("cls");
}

void Student::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "No Reservation!" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0;i < of.m_Size;i++) {
		cout << i + 1 << ", ";

		cout << "Reservation Date: " << of.m_orderData[i]["date"];
		cout << " interval: " << (of.m_orderData[i]["interval"] == "1" ? "Morning" : "Afternoon");
		cout << " Student ID: " << of.m_orderData[i]["stuId"];
		cout << "Name: " << of.m_orderData[i]["stuName"];
		cout << "Computer Room#" << of.m_orderData[i]["roomId"];
		string status = "Status: ";
		//1 in review 2 Reserved  -1 Failed 0 cancelled
		if (of.m_orderData[i]["status"] == "1") {
			status += "In review";
		} else if (of.m_orderData[i]["status"] == "2") {
			status += "Reserved";
		} else if (of.m_orderData[i]["status"] == "-1") {
			status += "Failed. Reservation was not approved";
		} else if (of.m_orderData[i]["status"] == "0") {
			status += "Reservation Cancelled";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

void Student::cancelOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "No reservation!" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "You have options to cancel the reservation in review or approved reservation." << endl;
	
	vector<int>v;
	int index = 1;
	for (int i = 0;i < of.m_Size;i++) {
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_ID) {
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") {
				v.push_back(i);
				cout << index++ << ", ";
				cout << "Reservation date: " << of.m_orderData[i]["date"];
				cout << " Interval:" << (of.m_orderData[i]["interval"] == "1" ? "Morning" : "Afternoon");
				cout << " Computer Room#" << of.m_orderData[i]["roomId"];
				string status = "Status: ";
				if (of.m_orderData[i]["status"] == "1") {
					status += "In review";
				} else if (of.m_orderData[i]["status"] == "2") {
					status += "Reserved";
				}
				cout << status << endl;
			}
		}
	}

	cout << "Please enter your choice, 0 indicate exit:" << endl;
	int select = 0;
	while (true) {
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			} else {
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "Cancelled reservation" << endl;
				break;
			}
		}
		cout << "Entered wrong information, please try again!" << endl;
	}
	system("pause");
	system("cls");
}