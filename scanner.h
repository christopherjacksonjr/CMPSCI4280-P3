#ifndef SCANNER_H
#define SCANNER_H
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include"token.h"

//Function declarations
vector<Token> scanner(string buffer);
void id_tk(string &buffer, int &i);
void int_tk(string &buffer, int &i);
void operator_tk(string &buffer, int &i);
void comment_tk(string &buffer, int &i);
bool isKeyword(string str);
bool isNumber(string str);
bool isOperator(string str);

#endif
