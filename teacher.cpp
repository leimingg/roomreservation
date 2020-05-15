#include "teacher.h"

Teacher::Teacher() {
}

Teacher::Teacher(int empId, string name, string pwd) {
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

void Teacher::operMenu() {
	cout << "Welcome Professor£º" << this->m_Name << " Login£¡" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.Check All Reservations|\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.Review Reservation    |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.Log off               |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "Please enter your choice: " << endl;
}

void Teacher::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "No Reservation" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_Size;i++) {
		cout << i + 1 << ", ";
		cout << "Reservation date: " << of.m_orderData[i]["date"];
		cout << " interval: " << (of.m_orderData[i]["interval"] == "1" ? "Morning" : "Afternoon");
		cout << " Student ID: " << of.m_orderData[i]["stuId"];
		cout << " Name:" << of.m_orderData[i]["stuName"];
		cout << " Computer Room#" << of.m_orderData[i]["roomId"];
		string status = " Status: ";
		if (of.m_orderData[i]["status"] == "1") {
			status += "In Review";
		} else if (of.m_orderData[i]["status"] == "2") {
			status += "Reserved";
		} else if (of.m_orderData[i]["status"] == "-1") {
			status += "Failed. Your reservation was not approved";
		} else {
			status += "Reservation Cancelled";
		}
		cout << status << endl;

	}
	system("pause");
	system("cls");
}

void Teacher::validOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "No Reservation" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "Pending reservation record:" << endl;

	vector<int> v;
	int index = 0;
	for (int i = 0;i < of.m_Size;i++) {
		if (of.m_orderData[i]["status"] == "1") {
			v.push_back(i);
			cout << ++index << "¡¢ ";
			cout << "Reservation: day " << of.m_orderData[i]["date"];
			cout << " Interval£º" << (of.m_orderData[i]["interval"] == "1" ? "Morning" : "Afternoon");
			cout << " Computer Room#" << of.m_orderData[i]["roomId"];
			string status = " status£º ";  
			if (of.m_orderData[i]["status"] == "1") {
				status += "In review";
			}
			cout << status << endl;
		}
	}
	cout << "Please review the pending reservation and select the number of reservation. 0 indicates exit"<<endl;
	int select = 0;
	int ret = 0;
	while (true) {
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			} else {
				cout << "Please enter review result" << endl;
				cout << "1. Approve" << endl;
				cout << "2. Not Approve" << endl;
				cin >> ret;
				if (ret == 1) {
					of.m_orderData[v[select - 1]]["status"] = "2";
				} else {
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "Review completed!" << endl;
				break;
			}
		}
		cout << "Entered wrong information, please try again." << endl;
	}
}