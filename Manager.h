#pragma once
#include "Identity.h"
using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include "globalFile.h"
#include <vector>
#include "student.h"
#include "teacher.h"
#include <algorithm>
#include "computerRoom.h"

class Manager :public Identity {
public:
	Manager();
	Manager(string name, string pwd);
	virtual void operMenu();
	void addPerson();
	void showPerson();
	void showComputer();
	void cleanFile();
	void initVector();
	vector<Student> vStu;
	vector<Teacher> vTea;
	bool checkRepeat(int id, int type);//param 1 is the input ID to be check duplicate,param 2 is student/professor
	vector<ComputerRoom> vCom;
};