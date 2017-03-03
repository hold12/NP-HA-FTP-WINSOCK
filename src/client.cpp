#include <iostream>
using namespace std;
#include <winsock2.h>
#include "Client.h"

int main(){
    std::cout<< "Hello, World" << std::endl;
    Client c;
    c.Connect(21,"130.226.195.126");
    c.SendMsg("USER anonymous");
    c.CloseCon();
    return 0;
}

void Client::Connect(int port, char *adr)
{
    WSAStartup(0x0101, &wlib);
    fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr(adr);
    connect(fd, (sockaddr *) &saddr, sizeof(saddr));
}

void Client::SendMsg(char *pmsg)
{
    if ((nOk=send(fd, pmsg,100, 0))== -1)
    {
        cout<< "Kunne ikke sende!" <<endl;
        exit(1);
    }
}
 void Client::CloseCon()
 {
   closesocket(fd);
   WSACleanup();
 }


