#include"file.h"

OptFile::OptFile(int size){
    StructSize = size;
    fd = 0;
}

OptFile::~OptFile(){
;;
}

FILE* OptFile::open(char* fileName, char *command){  
    fd = fopen(fileName, command);
    return fd;
}

FILE* OptFile::operator<<(void * buf){
    fwrite(buf, sizeof(char), StructSize, fd);
//    printf("%c", *((char*)buf));
    return fd;
}

int OptFile::close(){
    fclose(fd);
    return 0;
}

