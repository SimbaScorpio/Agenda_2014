#include "AgendaService.h"

using namespace std;

AgendaService::AgendaService() {
	startAgenda();
}

AgendaService::~AgendaService() {
	quitAgenda();
}

void AgendaService::startAgenda() {
	storage_=Storage::getInstance();
}

void AgendaService::quitAgenda(){
	storage_->sync();
}

std::function<bool(const User&)> filterU = [](const User& user) {
	return true;
};

bool AgendaService::userLogIn(std::string userName, std::string password) {
	std::list<User> userList;
	userList = storage_->queryUser(filterU);
	std::list<User>::iterator it;
	for (it = userList.begin(); it != userList.end(); it++) {
		if (userName == it->getName() && password == it->getPassword()) {
			return true;
		}
	}
	return false;
}

bool AgendaService::userRegister(std::string userName, std::string password,
	std::string email, std::string phone) {
	std::list<User> userList;
	userList = storage_->queryUser(filterU);
	std::list<User>::iterator it;
	for (it = userList.begin(); it != userList.end(); it++) {
		if (userName == it->getName()) {
			return false;
		}
	}
	storage_->createUser(User(userName, password, email, phone));
	return true;
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
	deleteAllMeetings(userName);
	return storage_->deleteUser([userName, password](const User& user)
	      {return user.getName() == userName && user.getPassword() == password;});
	return false;
}

bool AgendaService::updateUser(std::string userName, std::string password, std::string email, std::string phone){      //update
	function<bool(const User&)> filter = [=](const User &u){return u.getName()==userName;};
	function<void(User&)> update = [=](User &u){
				u.setPassword(password);
				u.setEmail(email);
				u.setPhone(phone);
			};
	return storage_->updateUser(filter,update);
}

std::list<User> AgendaService::listAllUsers(void) {
	return storage_->queryUser(filterU);
}

std::function<bool(const Meeting&)> filterM = [](const Meeting& meeting) {
	return true;
};

std::list<Meeting> AgendaService::listMeeting(void){
	return storage_->queryMeeting(filterM);
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName) {
	return storage_->queryMeeting([userName](const Meeting& meeting)
	{return meeting.getParticipator() == userName;});
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
	return storage_->queryMeeting([userName](const Meeting& meeting)
	{return meeting.getSponsor() == userName; });
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
	return storage_->queryMeeting([userName](const Meeting& meeting)
	{return meeting.getParticipator() == userName || meeting.getSponsor() == userName;});
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string title) {
	std::list<Meeting> meetingList;
	meetingList = listAllMeetings(userName);
	std::list<Meeting>::iterator it;
	for (it = meetingList.begin(); it != meetingList.end(); it++) {
		if (it->getTitle() != title) {
			it = meetingList.erase(it);
		}
	}
	if(meetingList.size()==1&&meetingList.front().getTitle()!=title) meetingList.clear();
	return meetingList;
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string startDate,
	std::string endDate) {
	std::list<Meeting> meetingList;
	meetingList = listAllMeetings(userName);
	std::list<Meeting>::iterator it;
	for (it = meetingList.begin(); it != meetingList.end(); it++) {
		if (it->getStartDate()>Date::stringToDate(endDate)||
		it->getEndDate()<Date::stringToDate(startDate)) {
			it = meetingList.erase(it);
		}
	}

	return meetingList;
}

bool AgendaService::createMeeting(std::string userName, std::string title, std::string participator,
	std::string startDate, std::string endDate) {
	if (userName == participator) return false;
	if(!Date::isValid(Date::stringToDate(startDate))) return false;
	if(!Date::isValid(Date::stringToDate(endDate))) return false;
	if(Date::stringToDate(startDate)>=Date::stringToDate(endDate)) return false;
	bool flag1=false, flag2=false;
	std::list<User> all;
	std::list<User>::iterator t;
	all = listAllUsers();
	for(t=all.begin();t!=all.end();t++){
		if(t->getName() == userName) {flag1 = true;}
		if(t->getName() == participator) {flag2 = true;}
	}
	if(flag1==false||flag2==false) return false;

	std::list<Meeting> sponsorList, partiList;
	std::list<Meeting>::iterator it;

	sponsorList = listAllMeetings(userName);
	partiList = listAllMeetings(participator);

	for (it = sponsorList.begin(); it != sponsorList.end(); it++) {
		Date sdate=it->getStartDate();
		Date edate=it->getEndDate();
		if(Date::stringToDate(startDate)<sdate &&
		   Date::stringToDate(endDate)>sdate ||
		   Date::stringToDate(startDate)<edate &&
		   Date::stringToDate(endDate)>edate ||
		   Date::stringToDate(startDate)>sdate &&
		   Date::stringToDate(endDate)<edate ||
		   title == it->getTitle()) {
			return false;
		}
	}
	for (it = partiList.begin(); it != partiList.end(); it++) {
		Date sdate=it->getStartDate();
		Date edate=it->getEndDate();
		if(Date::stringToDate(startDate)<sdate &&
		   Date::stringToDate(endDate)>sdate ||
		   Date::stringToDate(startDate)<edate &&
		   Date::stringToDate(endDate)>edate ||
		   Date::stringToDate(startDate)>sdate &&
		   Date::stringToDate(endDate)<edate ||
		   title == it->getTitle()) {
			return false;
		}
	}
	Meeting temp(userName,participator,Date::stringToDate(startDate),
                     Date::stringToDate(endDate),title);
	storage_->createMeeting(temp);
	return true;
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
	int flag = storage_->deleteMeeting([userName,title](const Meeting& m){
		if(m.getTitle()==title){
			if(m.getSponsor()==userName||m.getParticipator()==userName){
				return true;
			}
		}
		return false;
		});
	if (flag == 0) return false;
	else return true;
}

bool AgendaService::deleteAllMeetings(std::string userName) {
	int flag = storage_->deleteMeeting([userName](const Meeting& m){
		if(m.getSponsor()==userName||m.getParticipator()==userName){
			return true;
		}
		return false;
		});
	if (flag == 0) return false;
	else return true;
}





