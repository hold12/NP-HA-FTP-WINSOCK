#pragma once
#include <winsock2.h>
class FTPClient
{
public:
	void Connect(int port, char *adr);
	void SendMsg(char *pmsg, int size);
	char* RecvMsg();
	void SaveFile(char filename[]);
	void CloseCon();
private:
	int sock;
	sockaddr_in saddr;
	WSADATA wlib;
};

