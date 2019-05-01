#include<stdio.h>
#include<string.h>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include"token.h"
#include"parser.h"
#include"scanner.h"
#ifndef SEMANTICS_H
#define SEMANTICS_H

//Global variables & function prototypes.
extern vector<Token> variables;
void semantics(struct Node_t* root);

#endif
