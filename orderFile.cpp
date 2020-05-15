#include "orderFile.h"

OrderFile::OrderFile() {
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	
	string date;
	string interval;
	string stuId;
	string stuName;
	string roomId;
	string status;

	this->m_Size = 0;
	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName
		&& ifs >> roomId && ifs >> status) {
		/*cout << date << endl;
		cout << interval << endl;
		cout << stuId << endl;
		cout << stuName << endl;
		cout << roomId << endl;
		cout << status << endl;*/
		string key;
		string value;
		map<string, string> m;
		int pos=date.find(":");//4
		if (pos != -1) {
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(make_pair(key, value));
		
		}

		pos = interval.find(":");//4
		if (pos != -1) {
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		
		pos = stuId.find(":");//4
		if (pos != -1) {
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = stuName.find(":");//4
		if (pos != -1) {
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = roomId.find(":");//4
		if (pos != -1) {
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = status.find(":");//4
		if (pos != -1) {
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
	}
	ifs.close();
	//test map
	for (map<int, map<string, string>>::iterator it = m_orderData.begin();it != m_orderData.end();it++) {
		cout << "Index=" << it->first << " value=" << endl;
		for (map<string, string>::iterator mit = (*it).second.begin();mit != it->second.end();mit++) {
			cout << "key=" << mit->first << " value=" << mit->second << " ";
		}
		cout << endl;
	}
}
void OrderFile::updateOrder() {

}