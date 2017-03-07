#include <iostream>

using namespace std;

#include <winsock2.h>
#include "Client.h"
#pragma comment(lib, "Ws2_32.lib") //Winsock Library

int main() {
	Client c;
	c.Connect(21, "130.226.195.126");
	c.SendMsg("USER anonymous");
	c.SendMsg("PASS s165232@student.dtu.dk");
	c.SendMsg("PASV");
	c.CloseCon();
    return 0;
}

void Client::Connect(int port, char *adr){
	cout << "Connect started" << endl;
    WSAStartup(0x0101, &wlib);
    fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr(adr);
    connect(fd, (sockaddr *) &saddr, sizeof(saddr));
	cout << "Connect ended" << endl;
}

void Client::SendMsg(char *pmsg) {
	cout << "SendMsg started" << endl;
	char answer;
	
	if ((nOk = send(fd, pmsg, 100, 0)) == -1) {
        cout << "Kunne ikke sende!" << endl;
        exit(1);
    }
	else {
		recv(fd, &answer, 100, 0);
		cout << answer << endl;
	}

	cout << "SendMsg ended" << endl;
}

void Client::CloseCon() {
	cout << "CloseCon started" << endl;
    closesocket(fd);
    WSACleanup();
	cout << "CloseCon ended" << endl;
}
