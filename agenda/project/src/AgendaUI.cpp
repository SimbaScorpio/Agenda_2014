#include"AgendaUI.h"

using namespace std;

AgendaUI::AgendaUI(){
	sudo = false;
	log.setFileName("logUI.data");         //
}

void AgendaUI::OperationLoop(){
	log("Agenda start!");
	startAgenda();                             //
}

void AgendaUI::showMenu(void){
	cout << "------------------------- Agenda -----------------------------" << endl;
	cout << "Action :" << endl;
	cout << "help - show menu" << endl;
	cout << "o   - log out Agenda" << endl;
	cout << "up  - update user Info" << endl;
	cout << "dc  - delete Agenda account" << endl;
	cout << "lu  - list all Agenda user" << endl;
	cout << "cm  - create a meeting" << endl;
	cout << "la  - list all meetings" << endl;
	cout << "las - list all sponsor meetings" << endl;
	cout << "lap - list all participate meetings" << endl;
	cout << "qm  - query meeting by title" << endl;
	cout << "qt  - query meeting by time interval" << endl;
	cout << "dm  - delete meeting by title" << endl;
	cout << "da  - delete all meeting" << endl;
#ifdef WIN32
	cout << "game - play snake and enjoy yourself!" << endl;
#endif
	cout << "--------------------------------------------------------------" << endl << endl;
	executeOperation(getOperation());
}

std::string AgendaUI::getOperation(){
	if (sudo) cout << "Agenda@SuperUser: % ";
	else cout << "Agenda@" << userName_ << " : # ";
	std::string order;
	cin >> order;
	return order;
}

void AgendaUI::startAgenda(){
	log("User is choosing ...");               //
	cout << "------------------------- Agenda -----------------------------" << endl;
	cout << "Action :" << endl;
	cout << "l   - log in Agenda by user name and password" << endl;
	cout << "r   - register an Agenda account" << endl;
	cout << "q   - quit Agenda" << endl;
	cout << "--------------------------------------------------------------" << endl << endl;
	cout << "Agenda : ~$ ";
	std::string order;
	cin >> order;
	if (order == "l"){ log("User select [l] - log in"); userLogIn(); }
	else if (order == "r"){ log("User select [r] - register"); userRegister(); }
	else if (order == "q"){ log("User select [q] - quit"); quitAgenda(); }
	else if (order == "sudo"){ 
		sudo = true;
		userName_ = "SuperUser";
		log("User select [sudo] - super manager");
		showMenu();
	}
	else{
		log("User gives a wrong choice [" + order + "]!");         //
		startAgenda();
	}
}

void AgendaUI::userLogIn(){
	cout << "\n[log in] [user name] [password]" << endl;
	cout << "[log in] ";
	std::string a, b;
	cin >> a >> b;
	if (agendaService_.userLogIn(a, b)){
		userName_ = a;
		userPassword_ = b;
		cout << "[log in] succeed!" << endl << endl;
		log(userName_ + "@ log in!");                            //
		showMenu();
	}
	else{
		cout << "[log in] log in fail!" << endl << endl;
		log("Fail to log in! Previews input: " + a + b);                   //
		startAgenda();
	}
}

void AgendaUI::userRegister(){
	cout << "\n[register] [user name] [password] [email] [phone]" << endl;
	cout << "[register] ";
	std::string a, b, c, d;
	cin >> a >> b >> c >> d;
	if (agendaService_.userRegister(a, b, c, d)){
		cout << "[register] succeed!" << endl << endl;
		log("Regist new user: " + a);                       //
	}
	else{
		cout << "[error] register fail!" << endl << endl;
		log("Fail to regist! Previews input: " + a + " " + b + " " + c + " " + d);           //
	}
	startAgenda();
}

void AgendaUI::updateUser(void){
	if (sudo){
		cout << "\n[update User] [user name] [password] [email] [phone]";
		cout << "\n[update User] ";
		std::string a, b, c, d;
		cin >> a >> b >> c >> d;
		log(userName_ + "@ update user:[" + a + "] pwd:[" + b + "] email:[" + c + "] phone:[" + d + "]!");         //
		if (agendaService_.updateUser(a, b, c, d)){
			cout << "update succeed" << endl;
		}
		else{
			cout << "update fail" << endl;
		}
		executeOperation(getOperation());
	}
	else{
		cout << "\n[update User] [password] [email] [phone]";
		cout << "\n[update User] ";
		std::string a, b, c;
		cin >> a >> b >> c;
		log(userName_ + "@ update with pwd:[" + a + "] email:[" + b + "] phone:[" + c + "]!");         //
		if(agendaService_.updateUser(userName_, a, b, c)){
			cout << "update succeed" << endl;
		}
		else{
			cout << "update fail" << endl;
		}
		executeOperation(getOperation());
	}
}

void AgendaUI::quitAgenda(){
	sudo = false;
	log("Agenda quit!");            //
}

bool AgendaUI::executeOperation(std::string op){
	log(userName_ + "@ is choosing operation...");               //
	if (op == "o"){
		log(userName_ + "@ select [o] - log out");       //
		userLogOut();
	}
	else if (op == "dc"){
		log(userName_ + "@ select [dc] - delete user");       //
		deleteUser();
	}
	else if (op == "up"){
		log(userName_ + "@ select [up] - update user info");       //
		updateUser();
	}
	else if (op == "lu"){
		log(userName_ + "@ select [lu] - list all users");       //
		listAllUsers();
	}
	else if (op == "cm"){
		log(userName_ + "@ select [cm] - create meeting");       //
		createMeeting();
	}
	else if (op == "la"){
		log(userName_ + "@ select [la] - list all meetings");       //
		listAllMeetings();
	}
	else if (op == "las"){
		log(userName_ + "@ select [las] - list all sponsor meetings");       //
		listAllSponsorMeetings();
	}
	else if (op == "lap"){
		log(userName_ + "@ select [lap] - list all participate meetings");       //
		listAllParticipateMeetings();
	}
	else if (op == "qm"){
		log(userName_ + "@ select [qm] - query meeting by title");       //
		queryMeetingByTitle();
	}
	else if (op == "qt"){
		log(userName_ + "@ select [qt] - query meeting by time interval");       //
		queryMeetingByTimeInterval();
	}
	else if (op == "dm"){
		log(userName_ + "@ select [dm] - delete meeting by title");       //
		deleteMeetingByTitle();
	}
	else if (op == "da"){
		log(userName_ + "@ select [da] - delete all meetings");       //
		deleteAllMeetings();
	}
	else if (op == "help"){
		log(userName_ + "@ select [help] - show menu");       //
		showMenu();
	}
#ifdef WIN32
	else if (op == "game"){
		log(userName_ + "@ select [game] - play snake game");       //
		game.start();
		showMenu();
	}
#endif
	else{
		log(userName_ + "@ gives a wrong choice in operation [" + op + "]!");         //
		executeOperation(getOperation());
		return false;
	}
}

void AgendaUI::userLogOut(){
	log(userName_ + "@ log out!");            //
	cout << "log out!" << endl << endl;
	userName_ = "";
	userPassword_ = "";
	sudo = false;
	startAgenda();
}

void AgendaUI::deleteUser(void){
	if (sudo){
		cout << "\n[delete user] [user name] [password]";
		cout << "\n[delete user] ";
		std::string name, pwd;
		cin >> name >> pwd;
		if (agendaService_.deleteUser(name, pwd)){
			log(userName_ + "@ delete user [" + name + "]!");                            //
			cout << "\n[delete agenda account] succeed!" << endl << endl;
			executeOperation(getOperation());
		}
		else{
			log(userName_ + "@ fail to delete user [" + name + "]!");                            //
			cout << "\n[delete agenda account] delete fail!" << endl << endl;
			executeOperation(getOperation());
		}
	}
	else{
		if (agendaService_.deleteUser(userName_, userPassword_)){
			log(userName_ + "@ delete itself!");                            //
			userName_ = userPassword_ = "";
			cout << "\n[delete agenda account] succeed!" << endl << endl;
			startAgenda();
		}
		else{
			log(userName_ + "@ fail to delete itself!");                    //
			cout << "\n[delete agenda account] delete fail!" << endl << endl;
			executeOperation(getOperation());
		}
	}
}

void AgendaUI::listAllUsers(void){
	if (sudo){
		log(userName_ + "@ list all users!");            //
		std::list<User> List;
		List = agendaService_.listAllUsers();
		int max1 = 4, max2 = 8, max3 = 5;
		std::list<User>::iterator it;
		for (it = List.begin(); it != List.end(); it++){
			if (max1 < (it->getName()).length()){ max1 = (it->getName()).length(); }
			if (max2 < (it->getPassword()).length()){ max2 = (it->getPassword()).length(); }
			if (max3<(it->getEmail()).length()){ max3 = (it->getEmail()).length(); }
		}
		cout << "\n[list all users]\n\n";
		cout << left;
		cout << setw(max1 + 2) << "name" << setw(max2 + 2) << "password" << setw(max3 + 2) << "email" << "phone" << endl;
		for (it = List.begin(); it != List.end(); it++){
			cout << setw(max1 + 2) << it->getName();
			cout << setw(max2 + 2) << it->getPassword();
			cout << setw(max3 + 2) << it->getEmail();
			cout << it->getPhone() << endl;
		}
		cout << endl;
		executeOperation(getOperation());
	}
	else{
		log(userName_ + "@ list all users!");            //
		std::list<User> List;
		List = agendaService_.listAllUsers();
		int max1 = 4, max2 = 5;
		std::list<User>::iterator it;
		for (it = List.begin(); it != List.end(); it++){
			if (max1 < (it->getName()).length()){ max1 = (it->getName()).length(); }
			if (max2<(it->getEmail()).length()){ max2 = (it->getEmail()).length(); }
		}
		cout << "\n[list all users]\n\n";
		cout << left;
		cout << setw(max1 + 2) << "name" << setw(max2 + 2) << "email" << "phone" << endl;
		for (it = List.begin(); it != List.end(); it++){
			cout << setw(max1 + 2) << it->getName();
			cout << setw(max2 + 2) << it->getEmail();
			cout << it->getPhone() << endl;
		}
		cout << endl;
		executeOperation(getOperation());
	}
}

void AgendaUI::createMeeting(void){
	cout << "\n[create meeting] [title] [participator] [start time<yyyy-mm-dd/hh:mm>] [end time<yyyy-mm-dd/hh:mm>]" << endl;
	cout << "[create meeting] ";
	std::string a, b, c, d;
	cin >> a >> b >> c >> d;
	if (agendaService_.createMeeting(userName_, a, b, c, d)){
		log(userName_ + "@ create a meeting with [" + b + "] title[" + a + "] start[" + c + "] end[" + d + "]");            //
		cout << "[create meeting] succeed!" << endl << endl;
	}
	else{
		log(userName_ + "@ fail to create a meeting!");                      //
		cout << "[create meeting] create meeting fail!" << endl << endl;
	}
	executeOperation(getOperation());
}

void AgendaUI::listAllMeetings(void){
	log(userName_ + "@ list all meetings!");                     //
	cout << "\n[list all meetings]\n\n";
	if (sudo){
		printMeetings(agendaService_.listMeeting());
		executeOperation(getOperation());
	}
	else{
		printMeetings(agendaService_.listAllMeetings(userName_));
		executeOperation(getOperation());
	}
}
void AgendaUI::listAllSponsorMeetings(void){
	log(userName_ + "@ list all meetings as sponsor!");              //
	cout << "\n[list all sponsor meetings]\n\n";
	if (sudo){
		printMeetings(agendaService_.listMeeting());
		executeOperation(getOperation());
	}
	else{
		printMeetings(agendaService_.listAllSponsorMeetings(userName_));
		executeOperation(getOperation());
	}
}
void AgendaUI::listAllParticipateMeetings(void){
	log(userName_ + "@ list all meetings as participator!");              //
	cout << "\n[list all participate meetings]\n\n";
	if (sudo){
		printMeetings(agendaService_.listMeeting());
		executeOperation(getOperation());
	}
	else{
		printMeetings(agendaService_.listAllParticipateMeetings(userName_));
		executeOperation(getOperation());
	}
}
void AgendaUI::queryMeetingByTitle(void){
	std::string title;
	if (sudo){
		cout << "\n[query meeting] [user name] [title]:";
		cout << "\n[query meeting] ";
		std::string name;
		cin >> name >> title;
		cout << "\n[query meetings]\n";
		printMeetings(agendaService_.meetingQuery(name, title));
		executeOperation(getOperation());
	}
	else{
		cout << "\n[query meeting] [title]:";
		cout << "\n[query meeting] ";
		cin >> title;
		log(userName_ + "@ query meeting by title [" + title + "]");              //
		cout << "\n[query meetings]\n";
		printMeetings(agendaService_.meetingQuery(userName_, title));
		executeOperation(getOperation());
	}
}
void AgendaUI::queryMeetingByTimeInterval(void){
	if (sudo){
		cout << "\n[query meeting] [user name] [start time<yyyy-mm-dd/hh:mm>] [end time<yyyy-mm-dd/hh:mm>]";
		cout << "\n[query meeting] ";
		std::string a, b, c;
		cin >> a >> b >> c;
		cout << "\n[query meetings]\n";
		printMeetings(agendaService_.meetingQuery(a, b, c));
		executeOperation(getOperation());
	}
	else{
		cout << "\n[query meeting] [start time<yyyy-mm-dd/hh:mm>] [end time<yyyy-mm-dd/hh:mm>]";
		cout << "\n[query meeting] ";
		std::string a, b;
		cin >> a >> b;
		log(userName_ + "@ query meeting by time interval start[" + a + "] end[" + b + "]");              //
		cout << "\n[query meetings]\n";
		printMeetings(agendaService_.meetingQuery(userName_, a, b));
		executeOperation(getOperation());
	}
}
void AgendaUI::deleteMeetingByTitle(void){
	if (sudo){
		cout << "\n[delete meeting] [user name] [title]";
		cout << "\n[delete meeting] ";
		std::string name, title;
		cin >> name >> title;
		if (agendaService_.deleteMeeting(name, title)){
			cout << "\n[delete meeting by title] succeed!" << endl << endl;
		}
		else{
			cout << "\n[error] delete meeting fail!" << endl << endl;
		}
		executeOperation(getOperation());
	}
	else{
		cout << "\n[delete meeting] [title]";
		cout << "\n[delete meeting] ";
		std::string title;
		cin >> title;
		if (agendaService_.deleteMeeting(userName_, title)){
			log(userName_ + "@ delete meeting by title [" + title + "] succeed!");              //
			cout << "\n[delete meeting by title] succeed!" << endl << endl;
		}
		else{
			log(userName_ + "@ delete meeting by title [" + title + "] failed!");              //
			cout << "\n[error] delete meeting fail!" << endl << endl;
		}
		executeOperation(getOperation());
	}
}
void AgendaUI::deleteAllMeetings(void){
	if (sudo){
		cout << "\n[delete all meetings] [user name]";
		cout << "\n[delete all meetings] ";
		std::string name;
		cin >> name;
		if (agendaService_.deleteAllMeetings(name)){
			cout << "\n[delete all meetings] succeed!" << endl << endl;
		}
		else{
			cout << "\n[delete all maatings] delete meetings fail!" << endl << endl;
		}
		executeOperation(getOperation());
	}
	else{
		if (agendaService_.deleteAllMeetings(userName_)){
			log(userName_ + "@ delete all meetings succeed!");              //
			cout << "\n[delete all meetings] succeed!" << endl << endl;
		}
		else{
			log(userName_ + "@ delete all meetings failed!");              //
			cout << "\n[delete all maatings] delete meetings fail!" << endl << endl;
		}
		executeOperation(getOperation());
	}
}
void AgendaUI::printMeetings(std::list<Meeting> meetings){
	int max1 = 5, max2 = 7, max3 = 12;
	std::list<Meeting>::iterator it;
	for (it = meetings.begin(); it != meetings.end(); it++){
		if (max1<it->getTitle().length()){ max1 = it->getTitle().length(); }
		if (max2<it->getSponsor().length()){ max2 = it->getSponsor().length(); }
		if (max3<it->getParticipator().length()){ max3 = it->getParticipator().length(); }
	}
	cout << left;
	cout << setw(max1 + 4) << "title" << setw(max2 + 4) << "sponsor" << setw(max3 + 3) << "participator" << setw(18) << "start time" << "end time\n";
	for (it = meetings.begin(); it != meetings.end(); it++){
		cout << left;
		cout << setw(max1 + 4) << it->getTitle();
		cout << setw(max2 + 4) << it->getSponsor();
		cout << setw(max3 + 3) << it->getParticipator();
		cout << setw(18) << Date::dateToString(it->getStartDate());
		cout << Date::dateToString(it->getEndDate()) << endl;
	}
	cout << endl;
}

