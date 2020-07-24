/*
 * log.h
 *
 *  Created on: 2020��7��1��
 *      Author: mego
 */

#ifndef SRC_LOG_H_
#define SRC_LOG_H_

#include<stdio.h>
#include<stdarg.h>

void WriteLog(int, char *va_alist,...);
int SetDebugLevel(int level);

static int debug = 0;

#endif /* SRC_LOG_H_ */
