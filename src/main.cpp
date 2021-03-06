/*
main.cpp
*/
#include <iostream>
#include "FTPClient.h"

using namespace std;

int main() {
	char ip[] = "130.226.195.126";
	char *ip_pointer = ip; //Casting ip-address to a char-pointer
	FTPClient c, data;
	int dataPort;
	int a1, a2, a3, a4, p1, p2;

	//Establishing connection
	c.Connect(21, ip_pointer);
	c.RecvMsg();
	c.SendMsg("HELLO\r\n", 7);
	c.RecvMsg();

	//Logging in
	c.SendMsg("USER anonymous\r\n", 16);
	c.RecvMsg();
	c.SendMsg("PASS s165232@dtu.dk\r\n", 21);
	c.RecvMsg();


	//Entering Passive Mode
	c.SendMsg("PASV\r\n", 6);
	sscanf_s(c.RecvMsg(), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", &a1, &a2, &a3, &a4, &p1, &p2);
	dataPort = (p1 * 256) + p2;

	//Opening new data connection to appempt to STOR file in server root dir.
	data.Connect(dataPort, ip_pointer);
	c.SendMsg("LIST\r\n", 6);
	c.RecvMsg();

	data.RecvMsg();
	c.RecvMsg();
	
	c.SendMsg("STOR CMakeLists.txt\r\n", 21);
	c.RecvMsg();
	data.CloseCon();


	//Entering Passive Mode again
	c.SendMsg("PASV\r\n", 6);
	sscanf_s(c.RecvMsg(), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", &a1, &a2, &a3, &a4, &p1, &p2);
	dataPort = (p1 * 256) + p2;

	//Opening data connection to RETR 1st file
	data.Connect(dataPort, ip_pointer);
	c.SendMsg("RETR file.txt\r\n", 15); //small file of 12 bytes
	c.RecvMsg();
	c.RecvMsg();
	data.SaveFile("file.txt");
	data.CloseCon();

	//Entering Passive Mode again
	c.SendMsg("PASV\r\n", 6);
	sscanf_s(c.RecvMsg(), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", &a1, &a2, &a3, &a4, &p1, &p2);
	dataPort = (p1 * 256) + p2;

	//Opening new data connection to CWD and LIST
	data.Connect(dataPort, ip_pointer);
	c.SendMsg("CWD /pub/62501/HOWTOs/NAT-HOWTO\r\n", 33);
	c.RecvMsg();
	
	c.SendMsg("LIST\r\n", 6);
	c.RecvMsg();
	data.RecvMsg();
	c.RecvMsg();
	data.CloseCon();
	
	//Entering Passive Mode again
	c.SendMsg("PASV\r\n", 6);
	sscanf_s(c.RecvMsg(), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", &a1, &a2, &a3, &a4, &p1, &p2);
	dataPort = (p1 * 256) + p2;

	//Opening new data connection to RETR 2nd file
	data.Connect(dataPort, ip_pointer);
	c.SendMsg("RETR NAT-HOWTO-3.html\r\n", 23);//bigger file of 1359 bytes
	c.RecvMsg();
	c.RecvMsg();
	data.SaveFile("NAT-HOWTO-3.html");
	data.CloseCon();

	cin.get();
	c.CloseCon();
	return 0;
}
