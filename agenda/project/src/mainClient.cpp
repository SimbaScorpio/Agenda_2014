#include "Client.h"  
using namespace std;

void main()
{
	CClientNet client;

	client.Connect(8888, "127.0.0.1");

	//������Ϣ  
	string msg = "";
	while (msg != "q"){
		getline(cin, msg);

		if (client.getNumber() == "-1"){
			client.setUserName(client.getData(msg, 1));
			client.setUserPassword(client.getData(msg, 2));
		}
		while (msg == "game"){
			client.gameStart();
			client.showStart();
			getline(cin, msg);
		}
		client.SendMsg(msg);
	}

	//�ر�socket  
	printf("close\n");
	client.Close();

	system("pause");
}
