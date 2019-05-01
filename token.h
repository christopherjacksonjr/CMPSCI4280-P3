#include<stdio.h>
#include<iostream>
#include<vector>
#ifndef TOKEN_H
#define TOKEN_H

using namespace std;

enum tokenID {IDENT_tk, NUM_tk, KW_tk, CMNT_tk, EOF_tk, BEGIN_tk, END_tk, LOOP_tk, VOID_tk, INT_tk, RETURN_tk, READ_tk, OUTPUT_tk, PROGRAM_tk, IFF_tk, THEN_tk, LET_tk, EQUAL_tk, LESS_tk, GREATER_tk, COLON_tk, ADDITION_tk, SUBTRACTION_tk, MULTIPLY_tk, DIVIDE_tk, PERCENT_tk, PERIOD_tk, OPEN_PAREN_tk, CLOSE_PAREN_tk, COMMA_tk, OPEN_CURLY_tk, CLOSE_CURLY_tk, SEMI_COLON_tk, OPEN_BRACKET_tk, CLOSE_BRACKET_tk};

struct Token 
{
	tokenID id;
	string instance;
	int lineNumber;
	bool operator == (const Token& other ){return this->instance == other.instance;};
};

#endif
