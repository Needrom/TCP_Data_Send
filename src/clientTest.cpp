#include"tcp.h"
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include"myqueue.h"
#include"dataStruct.h"
#include"file.h"
#include<fstream>
#include <csignal>
#include<sys/time.h>
using namespace std;

MyQueue queue = MyQueue(2058);
OptFile myfile = OptFile(sizeof(DataFrame));

void* HeadCheck_thread(void* args){
    struct timeval start;
    struct timeval curr;
    unsigned long time;
    gettimeofday(&start, NULL);
    while(1){
        gettimeofday(&curr, NULL);
        time = 1000000 * (curr.tv_sec-start.tv_sec)+ curr.tv_usec-start.tv_usec;
        printf("\rsecond:[%ld]", time);
        fflush(stdout);
    }
}

void sig_handler( int sig )
{
    if ( sig == SIGINT)
    {
        printf("app end");
        myfile.close();
        exit(-1);
    }
}

void OnRecvData(char* buf, int size){
    DataFrame *Data = (DataFrame *)buf;
    
//    printf("PreCounter is %d \r\n", Data->PreCounter);
    myfile<<buf;
};

int main(int argc, char* argv[]){
    char dataRecv_buf[sizeof(DataFrame)] = {0};
    pthread_t threadID = 0;
    myfile.open("./data/test.dat", "w+");

    if(argc < 3){
        printf("usage: %s [ip address] [port] \r\n", argv[0]);
        exit(-1);
    }

    signal( SIGINT, sig_handler );

    TCPmy tcp = TCPmy(argv[1], (int)atoi(argv[2]));

    if(pthread_create(&threadID, NULL, HeadCheck_thread, NULL) != 0){
        perror("thread create error");
    }
    tcp.SocketCreate();
    if(tcp.Connect() < 0){
        perror("fialed to connected");
        exit(-1);
    }

    while(1){
        memset(dataRecv_buf, '0', sizeof(dataRecv_buf));
        int ReadLength = tcp.Recv(dataRecv_buf, 
                                    sizeof(dataRecv_buf));
        OnRecvData(dataRecv_buf, ReadLength);      
    }

    myfile.close();
}
