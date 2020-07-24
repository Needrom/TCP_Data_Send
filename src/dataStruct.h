/*
 * author: Liangguoyu
 */

#ifndef __DATASTRUCT__H
#define __DATASTRUCT__H

typedef struct{
    char Head[11];
    int Lenght;
    int PreCounter;
    int Data[256][2];
    int AfterCounter;
}DataFrame;

DataFrame frame = {
    .Head = "casia_send",
};

#endif
