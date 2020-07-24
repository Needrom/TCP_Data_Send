#ifndef __MYQUEUE__H
#define __MYQUEUE__H

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct{
    char *Ptr;
    int Rear;
    int Front;
}QueueStruct;

class MyQueue{
    public:
        QueueStruct Queue;
        MyQueue(int size);
        ~MyQueue();
        int Append(char *buf, int size);
};

#endif
