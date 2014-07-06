#include "Storage.h"

using namespace std;

Storage* Storage::instance_ = NULL;

Storage::Storage(const Storage& s){}

Storage::Storage() {
	readFromFile("agenda.data");
}

Storage::~Storage() {
	sync();
	Storage::instance_ = 0;
}

Storage* Storage::getInstance() {
	if (instance_ == NULL) {
		instance_ = new Storage;
	}
	return instance_;
}

void Storage::createUser(const User& user) {
	userList_.push_back(user);
}

std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) {
	std::list<User> temp;
	if (!userList_.size()) return temp;
	std::list<User>::iterator it;
	for (it = userList_.begin(); it != userList_.end(); it++) {
		if (filter(*it)) {
			temp.push_back(*it);
		}
	}
	return temp;
}

int Storage::updateUser(std::function<bool(const User&)> filter,
	std::function<void(User&)> switcher) {
	if (!userList_.size()) return 0;
	int count = 0;
	std::list<User>::iterator it;
	for (it = userList_.begin(); it != userList_.end(); it++) {
		if (filter(*it)){
			switcher(*it);
			count++;
		}
	}
	return count;
}

int Storage::deleteUser(std::function<bool(const User&)> filter) {
	if (!userList_.size()) return 0;
	int count = 0;
	std::list<User>::iterator it;
	for (it = userList_.begin(); it != userList_.end(); it++) {
		if (filter(*it)) {
			it = userList_.erase(it);
			count++;
		}
		if (!userList_.size())break;
	}
	return count;
}

void Storage::createMeeting(const Meeting& meeting) {
	meetingList_.push_back(meeting);
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting&)> filter) {
	std::list<Meeting> temp;
	if (!meetingList_.size()) return temp;
	std::list<Meeting>::iterator it;
	for (it = meetingList_.begin(); it != meetingList_.end(); it++) {
		if (filter(*it)) {
			temp.push_back(*it);
		}
	}
	return temp;
}

int Storage::updateMeeting(std::function<bool(const Meeting&)> filter,
	std::function<void(Meeting&)> switcher) {
	if (!meetingList_.size()) return 0;
	int count = 0;
	std::list<Meeting>::iterator it;
	for (it = meetingList_.begin(); it != meetingList_.end(); it++) {
		if (filter(*it)) {
			switcher(*it);
			count++;
		}
	}
	return count;
}

int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
	if (!meetingList_.size()) return 0;
	int count = 0;
	std::list<Meeting>::iterator it;
	for (it = meetingList_.begin(); it != meetingList_.end(); it++) {
		if (filter(*it)) {
			it = meetingList_.erase(it);
			count++;
		}
		if (!meetingList_.size())break;
	}
	return count;
}

/* file IO */
std::string safe(std::string a){
	for (int i = 0; i<a.length(); i++){
		a[i] += 20;
	}
	return a;
}

bool Storage::readFromFile(const char *fpath) {
	ifstream input(fpath);
	if (!input.is_open()){
		std::string m(fpath);
		return false;
	}

	//get user number
	char line_1[MAX_DATA_LENGTH];
	std::string temp = "";
	input.getline(line_1, MAX_DATA_LENGTH);

	int flag = 20;
	for (int i = 25; line_1[i] >= '0' + flag &&line_1[i] <= '9' + flag; i++){
		temp += line_1[i] - flag;
	}
	int userTotal;
	stringstream a;
	a << temp;
	a >> userTotal;

	char line_11[MAX_DATA_LENGTH];
	for (int i = 0; i < userTotal; i++){
		int count = 0;
		input.getline(line_11, MAX_DATA_LENGTH);
		//get name
		for (int i = count; line_11[i] != '\"'; i++){
			count = i + 1;
		}
		std::string name = "";
		for (int i = count + 1; line_11[i] != '\"'; i++){
			name += line_11[i] - flag;
			count = i + 1;
		}
		//get password
		for (int i = count + 1; line_11[i] != '\"'; i++){
			count = i + 1;
		}
		std::string password = "";
		for (int i = count + 1; line_11[i] != '\"'; i++){
			password += line_11[i] - flag;
			count = i + 1;
		}
		//get email
		for (int i = count + 1; line_11[i] != '\"'; i++){
			count = i + 1;
		}
		std::string email = "";
		for (int i = count + 1; line_11[i] != '\"'; i++){
			email += line_11[i] - flag;
			count = i + 1;
		}
		//get phone
		for (int i = count + 1; line_11[i] != '\"'; i++){
			count = i + 1;
		}
		std::string phone = "";
		for (int i = count + 1; line_11[i] != '\"'; i++){
			phone += line_11[i] - flag;
			count = i + 1;
		}
		createUser(User(name, password, email, phone));
	}

	//get meeting number
	char line_2[MAX_DATA_LENGTH];
	std::string temp2 = "";
	input.getline(line_2, MAX_DATA_LENGTH);

	for (int i = 28; line_2[i] >= '0' + flag&&line_2[i] <= '9' + flag; i++){
		temp2 += line_2[i] - flag;
	}
	int meetingTotal;
	stringstream b;
	b << temp2;
	b >> meetingTotal;

	char line_22[MAX_DATA_LENGTH];
	for (int i = 0; i<meetingTotal; i++){
		int count = 0;
		input.getline(line_22, MAX_DATA_LENGTH);

		//get sponsor
		for (int i = count; line_22[i] != '\"'; i++){
			count = i + 1;
		}
		std::string sponsor = "";
		for (int i = count + 1; line_22[i] != '\"'; i++){
			sponsor += line_22[i] - flag;
			count = i + 1;
		}
		//get participator
		for (int i = count + 1; line_22[i] != '\"'; i++){
			count = i + 1;
		}
		std::string participator = "";
		for (int i = count + 1; line_22[i] != '\"'; i++){
			participator += line_22[i] - flag;
			count = i + 1;
		}
		//get sdate
		for (int i = count + 1; line_22[i] != '\"'; i++){
			count = i + 1;
		}
		std::string sdate = "";
		for (int i = count + 1; line_22[i] != '\"'; i++){
			sdate += line_22[i] - flag;
			count = i + 1;
		}
		//get edate
		for (int i = count + 1; line_22[i] != '\"'; i++){
			count = i + 1;
		}
		std::string edate = "";
		for (int i = count + 1; line_22[i] != '\"'; i++){
			edate += line_22[i] - flag;
			count = i + 1;
		}
		//get title
		for (int i = count + 1; line_22[i] != '\"'; i++){
			count = i + 1;
		}
		std::string title = "";
		for (int i = count + 1; line_22[i] != '\"'; i++){
			title += line_22[i] - flag;
			count = i + 1;
		}
		Date s = Date::stringToDate(sdate);
		Date e = Date::stringToDate(edate);
		createMeeting(Meeting(sponsor, participator, s, e, title));
	}
	input.close();
	std::string m(fpath);
	return true;
}

bool Storage::writeToFile(const char *fpath) {
	ofstream output(fpath);
	if (!output.is_open()){
		std::string m(fpath);
		return false;
	}

	std::string temp;
	stringstream a;
	a << userList_.size();
	a >> temp;
	temp = safe(temp);
	output << "{collection:\"User\",total:" << temp << "}\n";

	std::list<User>::iterator it;
	for (it = userList_.begin(); it != userList_.end(); it++) {
		output << "{name:\"" << safe(it->getName()) << "\",password:\"" << safe(it->getPassword())
			<< "\",email:\"" << safe(it->getEmail()) << "\",phone:\"" << safe(it->getPhone()) << "\"}\n";
	}

	std::string temp2;
	stringstream b;
	b << meetingList_.size();
	b >> temp2;
	temp2 = safe(temp2);
	output << "{collection:\"Meeting\",total:" << temp2 << "}\n";

	std::list<Meeting>::iterator jt;
	for (jt = meetingList_.begin(); jt != meetingList_.end(); jt++) {
		output << "{sponsor:\"" << safe(jt->getSponsor()) << "\",participator:\""
			<< safe(jt->getParticipator()) << "\",sdate:\"" << safe(Date::dateToString(jt->getStartDate()))
			<< "\",edate:\"" << safe(Date::dateToString(jt->getEndDate())) << "\",title:\"" << safe(jt->getTitle()) << "\"}\n";
	}
	output.close();
	std::string m(fpath);
	return true;
}

bool Storage::sync() {
	return writeToFile("agenda.data");
}
