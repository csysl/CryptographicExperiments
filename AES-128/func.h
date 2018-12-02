//
// Created by sun on 18-11-14.
//

#ifndef AES_FUNC_H
#define AES_FUNC_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define ECB 1
#define CBC 2
#define MAXLEN 1024


void getString(char *str, int len);
/**
 * 从标准输入中读取用户输入的字符串
 */
void readPlainText(char *str, int *len);
/**
 * 把字符串写进文件
 */
void writeStrToFile(char *str, int len, char *fileName);
void aesStrToFile(char *key,int tag);

#endif //AES_FUNC_H
