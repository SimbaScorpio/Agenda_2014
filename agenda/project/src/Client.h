#pragma once  

#include "SnakeGame.h"
#include <string>
#include <windows.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib") 

class CClientNet
{
public:
	CClientNet();
	int Connect(int port, const char* address); 
	int SendMsg(std::string msg);
	void Close();
	std::string getNumber();
	std::string getSudo();
	void setUserName(std::string name);
	void setUserPassword(std::string password);
	void showMenu();
	void showStart();
	void gameStart();
	std::string getData(std::string str, int num);
private:
	SOCKET m_sock;
	std::string userName_;
	std::string userPassword_;
	std::string sudo;
	std::string number;
	SnakeGame game;
};
