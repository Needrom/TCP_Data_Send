#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<unistd.h>
#include"tcp.h"

int main(int argc, char *argv[]){
	struct sockaddr_in server;
	int conn_fd = 0, i = 0;
	int bufRecv_length = 0;
	char dataRecv_buf[2048] = {0};
	const char *Head = "casia_send";

	memset(&server, '0', sizeof(server));
	
	if(argc != 3){
		fprintf(stderr, "usage: %s [server IP] [port] \r\n", argv[0]);
		exit(-1);
	}
	
	conn_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(conn_fd < 0){
		perror("failed to create socket \r\n");
		exit(-1);
	}
	
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	
	int res = inet_pton(AF_INET, argv[1], &server.sin_addr);
	if(res <= 0){
		perror("inet_pton error occured \r\n");
		exit(-1);
	}
	
	if(connect(conn_fd, (struct sockaddr*)&server, sizeof(server)) < 0){
		perror("connect error \r\n");
		exit(-1);
	}
	
	while(1){
        memset(dataRecv_buf, '0', sizeof(dataRecv_buf));
		bufRecv_length = read(conn_fd, dataRecv_buf, sizeof(dataRecv_buf) - 1);
//		printf("bufRecv_length: %u \r\n", bufRecv_length);
  
        printf("\n  %s len: %d \r\n", dataRecv_buf, bufRecv_length);      
        for(i = 0; i < bufRecv_length; i++){
			if(strcmp(dataRecv_buf + i, Head) == 0){
//				printf("send_casia receive \r\n");
			}
		}
	}
	
}
