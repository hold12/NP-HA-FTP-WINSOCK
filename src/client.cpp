#include <iostream>

using namespace std;

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include "Client.h"
#include "Ws2tcpip.h"
#pragma comment(lib, "Ws2_32.lib") //Winsock Library

int main() {
	Client c;
	c.Connect(21, "130.226.195.126");
	Sleep(1000);
	c.SendMsg("USER anonymous\r\n");
	Sleep(1000);
	c.SendMsg("PASS bhupjit@dtu.dk\r\n");
	Sleep(1000);
	c.SendMsg("PASV\r\n");
	c.CloseCon();
    return 0;
}

void Client::Connect(int port, char *adr) {
	cout << "Connect started" << endl;
	WSAStartup(0x0101, &wlib);
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	inet_pton(AF_INET, adr, &saddr.sin_addr.s_addr);
	if (connect(fd, (SOCKADDR*)(&saddr), sizeof(saddr)) != 0) {
		cout << "No connection established." << endl;
		cin.get();
	}
	cout << "Connect ended" << endl;
}

void Client::SendMsg(char *pmsg) {
	cout << "SendMsg started" << endl;
	
	if ((nOk = send(fd, pmsg, 100, 0)) == -1) {
        cout << "Kunne ikke sende!" << endl;
		cin.get();
        exit(1);
    }

	cout << "SendMsg ended" << endl;
}

void Client::CloseCon() {
	cout << "CloseCon started" << endl;
    closesocket(fd);
    WSACleanup();
	cout << "CloseCon ended" << endl;
}
