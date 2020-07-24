#ifndef __FILE_H
#define __FILE_H

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

class OptFile{
    public:
        FILE* fd;
        int StructSize;
        OptFile(int);
        ~OptFile();
        FILE* open(char *, char *);
        int close();
        FILE* operator<<(void* buf);        
};

#endif
