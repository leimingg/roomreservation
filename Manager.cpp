#include "Manager.h"

Manager::Manager() {
}

Manager::Manager(string name, string pwd) {
	this->m_Name = name;
	this->m_Pwd = pwd;

	this->initVector();
}

void Manager::operMenu() {
	cout << "Welcome Administrator£º" << this->m_Name << "Login£¡" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.Add Account         |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.Check Account       |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.Check Room          |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.Empty Reservation   |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.Log off             |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "Please enter your choice: " << endl;
}
void Manager::addPerson() {
	cout << "Please enter the type of account you want to add:" << endl;
	cout << "1. Add student" << endl;
	cout << "2. Add professor" << endl;

	string fileName;//txt file to handle
	string tip;//remind id#
	string errorTip;
	ofstream ofs;//file object to handle

	int select = 0;
	cin >> select;//take user choice

	if (select == 1) {//add student
		fileName = STUDENT_FILE;
		tip = "Please enter your student ID: ";
		errorTip = "This ID is duplicate. Pleas try again!";

	} else {
		fileName = TEACHER_FILE;
		tip = "Please enter employee ID: ";
		errorTip = "This ID is duplicate. Pleas try again!";
	}
	//append the content to file
	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;

	while (true) {
		cin >> id;
		bool ret=checkRepeat(id,select);
		if (ret) {//duplicate
			cout << errorTip << endl;
		} else {
			break;
		}
	}
	
	cout << "Please enter name: " << endl;
	cin >> name;
	cout << "Please enter password: " << endl;
	cin >>pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "Added successfully!" << endl;

	system("pause");
	system("cls");
	ofs.close();

	this->initVector();
}
void printStudent(Student& s) {
	cout << "Student ID: " << s.m_ID << " Name: " << s.m_Name << " Password: " << s.m_Pwd << endl;
}

void printTeacher(Teacher& t) {
	cout << "Professor ID: " << t.m_EmpId << " Name: " << t.m_Name << " Password: " << t.m_Pwd << endl;
}

void Manager::showPerson() {
	cout << "Please enter the choice to check contents: " << endl;
	cout << "1. Check All students" << endl;
	cout << "2. Check All professors" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		cout << "All students information: " << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	} else {
		cout << "All professors information: " << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

void Manager::showComputer() {

}

void Manager::cleanFile() {

}

void Manager::initVector() {
	vStu.clear();
	vTea.clear();
	//read student and professor information
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "Failed to read file." << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_ID&& ifs >> s.m_Name&& ifs >> s.m_Pwd) {
		vStu.push_back(s);

	}
	cout << "Current Number of students: " << vStu.size() << endl;
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while (ifs >> t.m_EmpId&& ifs >> t.m_Name&& ifs >> t.m_Pwd) {
		vTea.push_back(t);
	}
	cout << "Current Number of professors: " << vTea.size() << endl;
	ifs.close();
}

bool Manager::checkRepeat(int id, int type) {
	if (type == 1) {//student
		for (vector<Student>::iterator it = vStu.begin();it != vStu.end();it++) {
			if (id == it->m_ID) {
				return true;
			}
		}
	} else {//professor
		for (vector<Teacher>::iterator it = vTea.begin();it != vTea.end();it++) {
			if (id == it->m_EmpId) {
				return true;
			}
		}
	}
	return false;
}
