/*
 * log.c
 *
 *  Created on: 2020年7月1日
 *      Author: mego
 */

#include"log.h"

int debug_flag = 0;
void WriteLog(int i,char* va_alist,...)
{
	 va_list args;
	 int level = i;
	 va_start(args ,va_alist);
	 if(debug_flag & 1 << (level - 1))    //注意&和<<优先级
	 {
		 vfprintf(stderr, va_alist, args);
	 }
	 va_end(args);
}

int SetDebugLevel(int debug_level)
{
	if (debug_level >= 1 && debug_level <= 9)
	{
		debug_flag |= 1 << (debug_level - 1);
	}
	else if(debug_level == 10)
	{
		debug_flag = 255;
	}

	return debug_flag;
}
