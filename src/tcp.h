#ifndef __TCP_H
#define __TCP_H

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

class TCPmy{
    public:
        struct sockaddr_in server, client;
        int listen_fd, conn_fd, recv_nums;
        
        TCPmy(char* address, int port);
        TCPmy(int port);
        ~TCPmy();
        int Accept();
        int Connect();  
        int Listen(int arg);
        int Recv(void *buf, int buf_size);
        int Send(void *buf, int buf_size);
        int SocketCreate();      
        
    private:

};

#endif

