#include "Client.h"  

using namespace std;

CClientNet::CClientNet(){
	userName_ = userPassword_ = "";
	sudo = "0";
	number = "1";
}

int CClientNet::Connect(int port, const char* address)
{
	int rlt = 0;
	int iErrMsg;

	WSAData wsaData;
	iErrMsg = WSAStartup(MAKEWORD(1, 1), &wsaData);
	if (iErrMsg != NO_ERROR)
	{
		cout << "failed with wsaStartup error : " << iErrMsg << endl;
		rlt = 1;
		return rlt;
	}
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sock == INVALID_SOCKET)
	{
		cout << "socket failed with error : " << WSAGetLastError() << endl;
		rlt = 2;
		return rlt;
	}

	sockaddr_in sockaddrServer;
	sockaddrServer.sin_family = AF_INET;
	sockaddrServer.sin_port = port;
	sockaddrServer.sin_addr.s_addr = inet_addr(address);

	iErrMsg = connect(m_sock, (sockaddr*)&sockaddrServer, sizeof(sockaddrServer));
	if (iErrMsg < 0)
	{
		cout << "connect failed with error : " << iErrMsg << endl;
		rlt = 3;
		return rlt;
	}
	showStart();
	return rlt;
}

std::string CClientNet::getData(std::string str, int num){
	std::string temp = "";
	if (num == 1){
		for (int i = 0; i < str.length(); i++){
			if (str[i] == ' ' || i == str.length()) return temp;
			temp += str[i];
		}
	}
	int count = 1;
	for (int i = 0; i < str.length(); i++){
		if (str[i] == ' '){
			if (++count == num){
				temp.clear();
				for (int j = i + 1; str[j] != ' ' && j != str.length(); j++){
					temp += str[j];
				}
				return temp;
			}
		}
	}
	return temp;
}

int CClientNet::SendMsg(std::string msg)
{
	int rlt = 0;
	int iErrMsg = 0;
	msg += " " + number + " " + sudo + " ";
	//发送消息，指定sock发送消息  
	iErrMsg = send(m_sock, msg.c_str(), msg.length(), 0);
	if (iErrMsg < 0)
	{
		cout << "send msg failed with error : " << iErrMsg << endl;
		rlt = 1;
		return rlt;
	}
	char buf[1024];
	std::string report = "";
	int rval;
	if (msg != "q")
	do{
		memset(buf, 0, sizeof(buf));
		rval = recv(m_sock, buf, 1024, 0);
		if (rval == SOCKET_ERROR){
			cout << "recv socket error" << endl;
			break;
		}
		else{
			report = buf;
			if (report == "sudo"){
				cout << "Super manager mod!"<<endl;
				sudo = "1";
				showMenu();
				cout << "Agenda@~~: ";
			}
			else if (report == "help" || report == "1 help"){
				showMenu();
				if (sudo == "1")cout << "Agenda@~~: ";
				else cout << "Agenda@" << userName_ << ":# ";
			}
			else if (report == "start"){
				showStart();
			}
			else if (report == "log in"){
				cout << "[log in] [user name] [password]\n";
				cout << "[log in] ";
				number = "-1";
			}
			else if (report == "log in succeed"){
				cout << "[log in] succeed!" << endl;
				showMenu();
				if (sudo == "1")cout << "Agenda@~~: ";
				else cout << "Agenda@" << userName_ << ":# ";
				number = "1";
			}
			else if (report == "log in fail"){
				cout << "[log in] log in fail!" << endl;
				showStart();
				number = "1";
			}
			else if (report == "log out"){
				cout << "log out!" << endl;
				showStart();
				userName_ = "";
				userPassword_ = "";
				sudo = "0";
				number = "1";
			}
			else if (report == "quit"){
				break;
			}
			else if (report == "register"){
				cout << "[register] [user name] [password] [email] [phone]\n";
				cout << "[register] ";
				number = "4";
			}
			else if (report == "register succeed"){
				cout << "[register] succeed!" << endl;
				showStart();
				number = "1";
			}
			else if (report == "register fail"){
				cout << "[error] register fail!" << endl;
				showStart();
				number = "1";
			}
			else if (report == "1 update user"){
				cout << "[update User] [user name] [password] [email] [phone]\n";
				cout << "[update User] ";
				number = "4";
			}
			else if (report == "update user"){
				cout << "[update User] [password] [email] [phone]\n";
				cout << "[update User] ";
				number = "3";
			}
			else if (report == "update succeed" || report == "1 update succeed"){
				cout << "update succeed" << endl;
				if (sudo == "1")cout << "Agenda@~~: ";
				else cout << "Agenda@" << userName_ << ":# ";
				number = "1";
			}
			else if (report == "update fail" || report == "1 update fail"){
				cout << "update fail" << endl;
				if (sudo == "1")cout << "Agenda@~~: ";
				else cout << "Agenda@" << userName_ << ":# ";
				number = "1";
			}
			else if (report == "1 delete user"){
				cout << "[delete user] [user name] [password]\n";
				cout << "[delete user] ";
				number = "2";
			}
			else if (report == "delete succeed" || report == "1 delete succeed"){
				cout << "[delete agenda account] succeed!" << endl;
				userName_ = userPassword_ = "";
				if (sudo == "1")cout << "Agenda@~~: ";
				else cout << "Agenda@" << userName_ << ":# ";
				number = "1";
			}
			else if (report == "delete fail" || report == "1 delete fail"){
				cout << "[delete agenda account] delete fail!" << endl;
				if (sudo == "1")cout << "Agenda@~~: ";
				else cout << "Agenda@" << userName_ << ":# ";
				number = "1";
			}
			else if (report[0] == '\n'){
				cout << report;
				if (sudo == "1")cout << "Agenda@~~: ";
				else cout << "Agenda@" << userName_ << ":# ";
				number = "1";
			}
			else if (report == "create meeting"){
				cout << "[create meeting] [title] [participator] [start time<yyyy-mm-dd/hh:mm>] [end time<yyyy-mm-dd/hh:mm>]";
				cout << "\n[create meeting] ";
				number = "4";
			}
			else if (report == "create meeting succeed"){
				cout << "[create meeting] succeed!" << endl;
				if (sudo == "1")cout << "Agenda@~~: ";
				else cout << "Agenda@" << userName_ << ": # ";
				number = "1";
			}
			else if (report == "create meeting fail"){
				cout << "[create meeting] create meeting fail!" << endl;
				if (sudo == "1")cout << "Agenda@~~: ";
				else cout << "Agenda@" << userName_ << ": # ";
				number = "1";
			}
			else if (report == "1 query meeting title"){
				cout << "[query meeting] [user name] [title]";
				cout << "\n[query meeting] ";
				number = "2";
			}
			else if (report == "query meeting title"){
				cout << "[query meeting] [title]";
				cout << "\n[query meeting] ";
				number = "1";
			}
			else if (report == "1 query meeting time"){
				cout << "[query meeting] [user name] [start time<yyyy-mm-dd/hh:mm>] [end time<yyyy-mm-dd/hh:mm>]";
				cout << "\n[query meeting] ";
				number = "3";
			}
			else if (report == "query meeting time"){
				cout << "[query meeting] [start time<yyyy-mm-dd/hh:mm>] [end time<yyyy-mm-dd/hh:mm>]";
				cout << "\n[query meeting] ";
				number = "2";
			}
			else if (report == "1 delete meeting title"){
				cout << "[delete meeting] [user name] [title]";
				cout << "\n[delete meeting] ";
				number = "2";
			}
			else if (report == "delete meeting title"){
				cout << "[delete meeting] [title]";
				cout << "\n[delete meeting] ";
				number = "1";
			}
			else if (report == "delete meeting title succeed" || report == "1 delete meeting title succeed"){
				cout << "[delete meeting by title] succeed!" << endl;
				if (sudo == "1")cout << "Agenda@~~: ";
				else cout << "Agenda@" << userName_ << ": # ";
				number = "1";
			}
			else if (report == "delete meeting title fail" || report == "1 delete meeting title fail"){
				cout << "[delete meeting by title] delete meeting fail!" << endl;
				if (sudo == "1")cout << "Agenda@~~: ";
				else cout << "Agenda@" << userName_ << ": # ";
				number = "1";
			}
			else if (report == "1 delete all meeting"){
				cout << "[delete all meetings] [user name]";
				cout << "\n[delete all meetings] ";
				number = "1";
			}
			else if (report == "delete all meeting succeed" || report == "1 delete all meeting succeed"){
				cout << "[delete all meetings] succeed!" << endl;
				if (sudo == "1")cout << "Agenda@~~: ";
				else cout << "Agenda@" << userName_ << ": # ";
				number = "1";
			}
			else if (report == "delete all meeting fail" || report == "1 delete all meeting fail"){
				cout << "[delete all meetings] delete meeting fail!" << endl;
				if (sudo == "1")cout << "Agenda@~~: ";
				else cout << "Agenda@" << userName_ << ": # ";
				number = "1";
			}
			else{
				cout << "unrecognized order!\n";
				if (sudo == "1")cout << "Agenda@~~: ";
				else cout << "Agenda@" << userName_ << ": # ";
			}
		}
	} while (report.length() == 0);

	return rlt;
}

void CClientNet::Close()
{
	closesocket(m_sock);
}

std::string CClientNet::getNumber(){
	return number;
}

std::string CClientNet::getSudo(){
	return sudo;
}

void CClientNet::setUserName(std::string name){
	userName_ = name;
}

void CClientNet::setUserPassword(std::string pwd){
	userPassword_ = pwd;
}

void CClientNet::showMenu(){
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
	number = "1";
}

void CClientNet::showStart(){
	cout << "------------------------- Agenda -----------------------------" << endl;
	cout << "Action :" << endl;
	cout << "l   - log in Agenda by user name and password" << endl;
	cout << "r   - register an Agenda account" << endl;
	cout << "q   - quit Agenda" << endl;
	cout << "--------------------------------------------------------------" << endl << endl;
	cout << "Agenda : ~$ ";
	number = "1";
}

void CClientNet::gameStart(){
	game.start();
}