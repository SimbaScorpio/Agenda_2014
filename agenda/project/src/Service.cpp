#include "Service.h"

using std::cout;
using std::endl;

int CServerNet::Init(const char* address, int port)
{
	log.setFileName("logServer.data");
	int rlt = 0;

	//用于记录错误信息，并输出
	int iErrorMsg;

	//初始化WinSock
	WSAData wsaData;
	iErrorMsg = WSAStartup(MAKEWORD(1, 1), &wsaData);

	if (iErrorMsg != NO_ERROR)
	{
		//初始化WinSock失败
		cout << "wsastartup failed with error : " << iErrorMsg << endl;
		log("wsastartup failed with error");
		rlt = 1;
		return rlt;
	}

	//创建服务端Socket
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sock == INVALID_SOCKET)

	{
		//创建Socket异常
		cout << "socket failed with error : " << WSAGetLastError() << endl;
		log("socket failed with error");
		rlt = 2;
		return rlt;
	}

	//声明信息
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = port;
	serverAddr.sin_addr.s_addr = inet_addr(address);

	//绑定
	iErrorMsg = bind(m_sock, (sockaddr*)&serverAddr, sizeof(serverAddr));
	if (iErrorMsg < 0)
	{
		//绑定失败
		cout << "bind failed with error : " << iErrorMsg << endl;
		log("bind failed with error");
		rlt = 3;
		return rlt;
	}
	return rlt;
}

std::string CServerNet::getData(std::string str, int num){
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

std::string CServerNet::format(std::string str, int width){
	std::string temp(str);
	for (int i = temp.length(); i < width; i++){
		temp += " ";
	}
	return temp;
}

std::string CServerNet::printMeetings(std::list<Meeting> meetings){
	std::string temp = "";
	int max1 = 5, max2 = 7, max3 = 12;
	std::list<Meeting>::iterator it;
	for (it = meetings.begin(); it != meetings.end(); it++){
		if (max1<it->getTitle().length()){ max1 = it->getTitle().length(); }
		if (max2<it->getSponsor().length()){ max2 = it->getSponsor().length(); }
		if (max3<it->getParticipator().length()){ max3 = it->getParticipator().length(); }
	}
	temp += "\n[list meetings]\n";
	temp += format("title", max1 + 4);
	temp += format("sponsor", max2 + 4);
	temp += format("participator", max3 + 3);
	temp += format("start time", 18);
	temp += "end time\n";
	for (it = meetings.begin(); it != meetings.end(); it++){
		temp += format(it->getTitle(), max1 + 4);
		temp += format(it->getSponsor(), max2 + 4);
		temp += format(it->getParticipator(), max3 + 3);
		temp += format(Date::dateToString(it->getStartDate()), 18);
		temp += Date::dateToString(it->getEndDate()) + "\n";
	}
	return temp;
}

void CServerNet::Run()
{
	//公开连接
	listen(m_sock, 5);
	log("server on run");

	sockaddr_in tcpAddr;
	int len = sizeof(sockaddr);
	SOCKET newSocket;
	char buf[1024];
	int rval;

	do
	{
		//接收信息
		newSocket = accept(m_sock, (sockaddr*)&tcpAddr, &len);
		if (newSocket == INVALID_SOCKET)
		{
			//非可用socket
		}
		else
		{
			//新socket连接
			cout << "new socket connect : " << newSocket << endl;
			log("new socket connect");

			flag = "";
			std::string judge = "";
			std::string userName_ = "";
			std::string userPassword_ = "";

			//消息处理
			do
			{
				printf("process...\n");
				//接收数据
				memset(buf, 0, sizeof(buf));
				rval = recv(newSocket, buf, 1024, 0);
				std::string order(buf);
				std::string report = "";

				if (rval == SOCKET_ERROR){
					printf("recv socket error\n");
					log("receive socket error");
					break;
				}

				if (rval == 0){
					//recv返回0表示正常退出
					cout << "ending connection" << endl;
					log("ending connection");
				}
				else{
					log("receive message: " + order);
					cout << "receive: " << order << endl;
					//  Agenda 开始
					if (flag == "" || flag == "start" || flag == "log in fail" || flag == "register succeed" ||
						flag == "register fail" || flag == "log out" || flag == "delete succeed") {
						order = getData(order, 1);
						if (order == "sudo"){
							report = "sudo";
							judge = "1";
							log("manager mod");
						}
						else if (order == "r"){
							report = "register";
						}
						else if (order == "l"){
							report = "log in";
						}
						else if (order == "q"){
							report = "quit";
						}
						else{
							report = "start";
						}
					}

					// 用户登入成功，返回成功信息；登入失败，返回失败信息
					else if (flag == "log in"){
						if (agendaService_.userLogIn(getData(order, 1), getData(order, 2))){
							report = "log in succeed";
							userName_ = getData(order, 1);
							userPassword_ = getData(order, 2);
							judge = "0";
							log(userName_ + " log in");
						}
						else{
							report = "log in fail";
							log("log in fail");
						}
					}

					// 用户注册，返回注册提示
					else if (flag == "register"){
						if (agendaService_.userRegister(getData(order, 1), getData(order, 2), getData(order, 3), getData(order, 4))){
							report = "register succeed";
							log(getData(order, 1) + " " + getData(order, 2) + " " + getData(order, 3) + " " + getData(order, 4) + " register succeed");
						}
						else{
							report = "register fail";
							log("register fail");
						}
					}

					// 用户以普通用户身份进入菜单界面
					if (judge == "0"){
						cout << "ordinary!" << std::endl;
						if (flag == "log in succeed" || flag == "update succeed" ||
							flag == "update fail" || flag == "delete fail" ||
							flag == "create meeting succeed" || flag == "create meeting fail" || flag == "delete meeting title succeed" ||
							flag == "delete meeting title fail" || flag == "delete all meeting succeed" || flag == "delete all meeting fail" ||
							flag == "help" || flag[0] == '\n') {

							order = getData(order, 1);
							if (order == "help"){
								report = "help";
							}
							else if (order == "o"){
								report = "log out";
								log(userName_ + " log out");
								judge = "";
								userName_ = userPassword_ = "";
							}
							else if (order == "up"){
								report = "update user";
							}
							else if (order == "dc"){
								if (agendaService_.deleteUser(userName_, userPassword_)){
									log(userName_ + " delete account succeed");
									userName_ = userPassword_ = "";
									report = "delete succeed";
								}
								else{
									log(userName_ + " delete account fail");
									report = "delete fail";
								}
							}
							else if (order == "lu"){
								std::list<User> List;
								List = agendaService_.listAllUsers();
								int max1 = 4, max2 = 5;
								std::list<User>::iterator it;
								for (it = List.begin(); it != List.end(); it++){
									if (max1 < (it->getName()).length()){ max1 = (it->getName()).length(); }
									if (max2 < (it->getEmail()).length()){ max2 = (it->getEmail()).length(); }
								}
								report += "\n[list all users]\n";
								report += format("name", max1 + 2);
								report += format("email", max2 + 2);
								report += "phone\n";
								for (it = List.begin(); it != List.end(); it++){
									report += format(it->getName(), max1 + 2);
									report += format(it->getEmail(), max2 + 2);
									report += it->getPhone() + "\n";
								}
								log(userName_ + " list all users");
							}
							else if (order == "cm"){
								report = "create meeting";
							}
							else if (order == "la"){
								report = printMeetings(agendaService_.listAllMeetings(userName_));
								log(userName_ + " list all meetings");
							}
							else if (order == "las"){
								report = printMeetings(agendaService_.listAllSponsorMeetings(userName_));
								log(userName_ + " list all sponsor meetings");
							}
							else if (order == "lap"){
								report = printMeetings(agendaService_.listAllParticipateMeetings(userName_));
								log(userName_ + " list all participate meetings");
							}
							else if (order == "qm"){
								report = "query meeting title";
							}
							else if (order == "qt"){
								report = "query meeting time";
							}
							else if (order == "dm"){
								report = "delete meeting title";
							}
							else if (order == "da"){
								if (agendaService_.deleteAllMeetings(userName_)){
									report == "delete all meeting succeed";
									log(userName_ + " delete all meeting succeed");
								}
								else{
									report == "delete all meeting fail";
									log(userName_ + " delete all meeting fail");
								}
							}
							else{
								report = "help";
								log(userName_ + " choose wrong choice");
							}
						}
					}

					// 用户以管理员身份进入菜单界面
					if (judge == "1"){
						cout << "manager!" << std::endl;
						if (flag == "sudo" || flag == "1 update succeed" || flag == "1 update fail" ||
							flag == "1 delete fail" || flag == "1 delete succeed" ||
							flag == "1 delete meeting title succeed" || flag == "1 delete meeting title fail" || 
							flag == "1 delete all meeting succeed" || flag == "1 delete all meeting fail" ||
							flag == "1 help" || flag[0] == '\n') {
							order = getData(order, 1);
							if (order == "help"){
								report = "1 help";
							}
							else if (order == "o"){
								report = "log out";
								judge = "";
								userName_ = userPassword_ = "";
								log("manager log out");
							}
							else if (order == "up"){
								report = "1 update user";
							}
							else if (order == "dc"){
								report = "1 delete user";
							}
							else if (order == "lu"){
								std::list<User> List;
								List = agendaService_.listAllUsers();
								int max1 = 4, max2 = 8, max3 = 5;
								std::list<User>::iterator it;
								for (it = List.begin(); it != List.end(); it++){
									if (max1 < (it->getName()).length()){ max1 = (it->getName()).length(); }
									if (max2 < (it->getPassword()).length()){ max2 = (it->getPassword()).length(); }
									if (max3<(it->getEmail()).length()){ max3 = (it->getEmail()).length(); }
								}
								report += "\n[list all users]\n";
								report += format("name", max1 + 2);
								report += format("password", max2 + 2);
								report += format("email", max3 + 2);
								report += "phone\n";
								for (it = List.begin(); it != List.end(); it++){
									report += format(it->getName(), max1 + 2);
									report += format(it->getPassword(), max2 + 2);
									report += format(it->getEmail(), max3 + 2);
									report += it->getPhone() + '\n';
								}
								log("manager list all users");
							}
							else if (order == "cm"){
								report = "create meeting";
							}
							else if (order == "la"){
								report = printMeetings(agendaService_.listMeeting());
								log("manager list all meetings");
							}
							else if (order == "las"){
								report = printMeetings(agendaService_.listMeeting());
								log("manager list all meetings");
							}
							else if (order == "lap"){
								report = printMeetings(agendaService_.listMeeting());
								log("manager list all meetings");
							}
							else if (order == "qm"){
								report = "1 query meeting title";
							}
							else if (order == "qt"){
								report = "1 query meeting time";
							}
							else if (order == "dm"){
								report = "1 delete meeting title";
							}
							else if (order == "da"){
								report = "1 delete all meeting";
							}
							else{
								report = "1 help";
							}
						}
					}
					// 普通用户修改个人资料
					if (flag == "update user"){
						if (agendaService_.updateUser(userName_, getData(order, 1), getData(order, 2), getData(order, 3))) {
							report = "update succeed";
							userPassword_ = getData(order, 1);
							log(userName_ + " update info succeed");
						}
						else{
							log(userName_ + " update info fail");
							report = "update fail";
						}
					}

					// 管理员修改用户资料
					else if (flag == "1 update user"){
						if (agendaService_.updateUser(getData(order, 1), getData(order, 2), getData(order, 3), getData(order, 4))) {
							report = "1 update succeed";
							log("manager update info succeed");
						}
						else{
							log("manager update info fail");
							report = "1 update fail";
						}
					}

					// 管理员删除用户账号
					else if (flag == "1 delete user"){
						if (agendaService_.deleteUser(getData(order, 1), getData(order, 2))) {
							userName_ = userPassword_ = "";
							report = "1 delete succeed";
							log("manager delete " + getData(order, 1) + " succeed");
						}
						else{
							log("manager delete " + getData(order, 1) + " fail");
							report = "1 delete fail";
						}
					}

					// 普通用户创建会议
					else if (flag == "create meeting"){
						if (agendaService_.createMeeting(userName_, getData(order, 1), getData(order, 2), getData(order, 3), getData(order, 4))){
							report = "create meeting succeed";
							log(userName_ + " create meeting succeed");
						}
						else{
							log(userName_ + " create meeting fail");
							report = "create meeting fail";
						}
					}

					// 普通用户按标题搜寻会议
					else if (flag == "query meeting title"){
						report = printMeetings(agendaService_.meetingQuery(userName_, getData(order, 1)));
						log(userName_ + " query meeting by title " + getData(order, 1));
					}

					// 管理员按用户名和标题搜寻会议
					else if (flag == "1 query meeting title"){
						report = printMeetings(agendaService_.meetingQuery(getData(order, 1), getData(order, 2)));
						log("manager query " + getData(order, 1) + "'s meeting by title " + getData(order, 2));
					}

					// 普通用户按时间段搜寻会议
					else if (flag == "query meeting time"){
						report = printMeetings(agendaService_.meetingQuery(userName_, getData(order, 1), getData(order, 2)));
						log(userName_ + " query meeting by time " + getData(order, 1) + " " + getData(order, 2));
					}

					// 管理员按用户名和时间段搜寻会议
					else if (flag == "1 query meeting time"){
						report = printMeetings(agendaService_.meetingQuery(getData(order, 1), getData(order, 2), getData(order, 2)));
						log("manager query " + getData(order, 1) + "'s meeting by time " + getData(order, 2) + " " + getData(order, 3));
					}

					// 普通用户按标题删除用户会议
					else if (flag == "delete meeting title"){
						if (agendaService_.deleteMeeting(userName_, getData(order, 1))){
							report = "delete meeting title succeed";
							log(userName_ + " delete meeting by title " + getData(order, 1) + " succeed");
						}
						else{
							log(userName_ + " delete meeting by title " + getData(order, 1) + " fail");
							report = "delete meeting title fail";
						}
					}

					// 管理员按用户名和标题删除用户会议
					else if (flag == "1 delete meeting title"){
						if (agendaService_.deleteMeeting(getData(order, 1), getData(order, 2))){
							report = "1 delete meeting title succeed";
							log("manager delete " + getData(order, 1) + "'s meeting by title " + getData(order, 2) + " succeed");
						}
						else{
							log("manager delete " + getData(order, 1) + "'s meeting by title " + getData(order, 2) + " fail");
							report = "1 delete meeting title fail";
						}
					}

					// 管理员按用户名删除用户会议
					else if (flag == "1 delete all meeting"){
						if (agendaService_.deleteAllMeetings(getData(order, 1))){
							log("manager delete " + getData(order, 1) + "'s meeting succeed");
							report == "1 delete all meeting succeed";
						}
						else{
							log("manager delete " + getData(order, 1) + "'s meeting fail");
							report == "1 delete all meeting fail";
						}
					}
					flag = report;
					send(newSocket, report.c_str(), report.length(), 0);
					cout << "flag: " << flag << std::endl;
					cout << "judge: " << judge << std::endl;
					cout << "user: " << userName_ << " password: " << userPassword_ << std::endl;
				}
			} while (rval != 0);

			//关闭对应Accept的socket
			closesocket(newSocket);
			log("Agenda quit");
			agendaService_.quitAgenda();
		}

	} while (1);

	log("server close");
	//关闭自身的Socket
	closesocket(m_sock);
}