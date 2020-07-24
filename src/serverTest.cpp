#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include"tcp.h"
#include"dataStruct.h"

int test_buf[2048] = {0};

void InitTestData(){
    int i = 0;
    for(i = 0; i < 256; i++){
        frame.Data[i][0] = i;           
        printf("%d \r\n", frame.Data[i][0]);
    }
}

int main(int argc, char *argv[]){
    InitTestData();

    if(argc < 2){
        fprintf(stderr, "usage: %s [port] \r\n", argv[0]);
        exit(-1);    
    }

    TCPmy tcp = TCPmy(atoi(argv[1]));

    if(tcp.Listen(10) < 0){
        perror("tcp listen error");
        exit(-1);
    }
        
    char *buf = (char *)malloc(sizeof(frame));
    memcpy(buf, &frame, sizeof(frame)); 
    if(tcp.Accept() < 0){
        perror("tcp accpet error \r\n");
        //close(tcp.conn_fd);
    }

   while(1){
        ((DataFrame*)buf)->PreCounter++;
        ((DataFrame*)buf)->AfterCounter++;
        tcp.Send(buf, sizeof(frame));
        printf("%d \r\n",((DataFrame*)buf)->PreCounter);
    }
}

