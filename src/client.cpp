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
	cout << c.RecvMsg() << endl;
	c.SendMsg("HELLO\r\n",7);
	cout << c.RecvMsg() << endl;
	c.SendMsg("USER anonymous\r\n", 16);
	cout << c.RecvMsg() << endl;
	c.SendMsg("PASS s165232@dtu.dk\r\n", 21);
	cout << c.RecvMsg() << endl;
	c.SendMsg("PASV\r\n", 6);
	cout << c.RecvMsg() << endl;
	Sleep(36000);
	c.CloseCon();
    return 0;
}

void Client::Connect(int port, char *adr) {
	WSAStartup(0x0101, &wlib);
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	inet_pton(AF_INET, adr, &saddr.sin_addr.s_addr);
	if (connect(fd, (SOCKADDR*)(&saddr), sizeof(saddr)) != 0) {
		cout << "No connection established." << endl;
		exit(1);
	}
	cout << "Connected to server." << endl;
}

void Client::SendMsg(char *pmsg, int size) {
	cout << "Sent to server:" << endl;
	cout << pmsg << endl;
	
	if ((nOk = send(fd, pmsg, size, 0)) == -1) {
        cout << "Kunne ikke sende!" << endl;
        exit(1);
    }
}

char* Client::RecvMsg() {
	cout << "Received from server:" << endl;

	int x;
	char received[1024];
	x = recv(fd, received, 1024, 0);
	received[x] = '\0'; //0 indexing 
 	return received;
}

void Client::CloseCon() {
    closesocket(fd);
    WSACleanup();
	cout << "Closed connection." << endl;
}
