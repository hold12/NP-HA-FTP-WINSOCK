#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include "Client.h"
#include "Ws2tcpip.h"
#pragma comment(lib, "Ws2_32.lib") //Winsock Library

int main() {
	char ip[] = "130.226.195.126";
	char *ip_pointer = ip; //Casting ip-address to a char-pointer
	Client c;

	//Establishing connection
	c.Connect(21, ip_pointer);
	printf(c.RecvMsg());
	c.SendMsg("HELLO\r\n",7);
	printf(c.RecvMsg());
	
	//Logging in
	c.SendMsg("USER anonymous\r\n", 16);
	printf(c.RecvMsg());
	c.SendMsg("PASS s165232@dtu.dk\r\n", 21);
	printf(c.RecvMsg());
	
	//Entering Passive Mode
	c.SendMsg("PASV\r\n", 6);
	int a1,a2,a3,a4,p1,p2;
	sscanf_s(c.RecvMsg(),"227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n",&a1,&a2,&a3,&a4,&p1,&p2);
	int dataPort = (p1 * 256) + p2;
	cout << "New portnumber received: " << dataPort << endl;
	
	//Opening data connection for 1st file
	Client data;
	data.Connect(dataPort, ip_pointer);
	c.SendMsg("RETR file.txt\r\n", 15);
	printf(c.RecvMsg());
	printf(c.RecvMsg());
	data.SaveFile("file.txt");
	data.CloseCon();

	//Opening new data connection for 2nd file
	c.SendMsg("PASV\r\n", 6);
	sscanf_s(c.RecvMsg(), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", &a1, &a2, &a3, &a4, &p1, &p2);
	dataPort = (p1 * 256) + p2;
	Client data2;
	data2.Connect(dataPort, ip_pointer);
	c.SendMsg("CWD /pub/62501/HOWTOs/NAT-HOWTO\r\n", 33);
	printf(c.RecvMsg());
	c.SendMsg("RETR NAT-HOWTO-3.html\r\n", 23);
	data2.SaveFile("NAT-HOWTO-3.html");
	cin.get();
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
	cout << "Sent to server:\t\t";
	cout << pmsg;

	if ((nOk = send(fd, pmsg, size, 0)) == -1) {
        cout << "Kunne ikke sende!" << endl;
        exit(1);
    }
}

char* Client::RecvMsg() {
	cout << "Received from server:\t";

	int x;
	char received[1024];
	x = recv(fd, received, 1024, 0);
	received[x] = '\0'; //0 indexing
 	return received;
}

void Client::SaveFile(char filename[]) {
	ofstream file;
	file.open(filename);
	char buffer[1];
	int bytes(0);
	while (recv(fd, buffer, sizeof(buffer), 0)) {
		if (bytes <= 1024)
			cout << buffer[0];
		file << buffer[0];
		bytes++;
	}
	file.close();
}

void Client::CloseCon() {
    closesocket(fd);
    WSACleanup();
	cout << "Closed connection." << endl;
}
