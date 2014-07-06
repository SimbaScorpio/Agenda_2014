#pragma once

#include "AgendaService.h"
#include "LogMessage.h"
#include <iostream>
#include <iomanip>
#include <winsock.h>
#include <string>

#pragma comment (lib,"ws2_32.lib")

class CServerNet
{
public:
	//��ʼ��������,����0��ʾ�ɹ�
	int Init(const char* address, int port);
	//��������
	void Run();
	std::string getData(std::string str, int num);
	std::string format(std::string str, int width);
	std::string printMeetings(std::list<Meeting> meetings);
private:
	SOCKET m_sock;
	std::string flag;
	AgendaService agendaService_;
	LogMessage log;
};