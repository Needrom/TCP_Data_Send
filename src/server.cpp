#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include"log.h"
#include<arpa/inet.h>
#include<unistd.h>
#include"dataStruct.h"
#include<iostream>

using namespace std;

int main(int argc, char *argv[]){
	struct sockaddr_in server, client;
	int listen_fd, conn_fd, recv_nums = 0, i = 0;
	char dataRecv_buf[2048] = {0};
	const char *Head = "casia_send";
    int yes = 1;

    // set debug level
    SetDebugLevel(4 | 3);
	
	memset(&server, '0', sizeof(server));
	memset(&client, '0', sizeof(client));
	
	if(argc != 2){
		fprintf(stderr, "usage %s [port]", argv[0]);
        exit(-1);
	}
	
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_fd < 0){
		perror("socket create error ");
        exit(-1);
	} else {
//        printf("PORT %d \r\n", atoi(argv[1]));
    }

    server.sin_family = AF_INET;	
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons((u_short)atoi(argv[1]));

    if(setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&yes, sizeof yes)){
        perror("setsockopt");
        exit(-1);   
    }	

	if(bind(listen_fd, (struct sockaddr*)&server, sizeof(server)) < 0){
        perror("bind error ");
        exit(-1);
    }
	
	if(listen(listen_fd, 10) < 0){
        perror("listen error ");
        exit(-1);
    }

	int clientAddr_length = sizeof client;
    conn_fd = accept(listen_fd, (struct sockaddr*)&client, (socklen_t*)&clientAddr_length);
    
	while(1){
		if(conn_fd < 0){
			WriteLog(4, "accpet error \r\n");
			continue;
		} else {
			WriteLog(3, "accept client from %s", inet_ntoa(client.sin_addr));
		}
	
        send(conn_fd, Head, strlen(Head), 0);	
//	    close(conn_fd);
    }
}
