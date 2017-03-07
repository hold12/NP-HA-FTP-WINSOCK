#ifndef KLIENT_H_INCLUDED
#define KLIENT_H_INCLUDED


#include <winsock2.h>
class Client{
public:
 void Connect(int port, char *adr);
 void SendMsg(char *pmsg, int size);
 char* RecvMsg();
 void CloseCon();
private:
 int fd;
 sockaddr_in saddr;
 WSADATA wlib;
 int nOk;
};


#endif // KLIENT_H_INCLUDED
