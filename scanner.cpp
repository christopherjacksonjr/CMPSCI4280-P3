#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sstream>
#include"token.h"
#include"scanner.h"

using namespace std;

vector<Token> tokens;
int lineNumber = 1;

/*Description: takes string and recognizes tokens within that string
 *Parameters: string buffer - appended string from stdin or file.
 *Return: vector<Token> - list of tokens recognized.
 **********************************************/

vector<Token> scanner(string buffer)
{
	//Variable declaractions.
	int i;	
	char c;

	//For loop to loop through appended string.
	for(i = 0; i < buffer.length(); i++)
	{
		c = buffer[i];

		//Conditiopnals will call appropriate function to recognize tokens.
		if(isupper(c) != 0)
		{
			id_tk(buffer, i);
			i--;
		}
		if(c == '=' || '<' || '>' || ':' || '+' || '-' || '*' || '/' || '%' || '.' || '(' || ')' || ',' || '{' || '}' || ';' || '[' || ']')
		{
			operator_tk(buffer, i);
		}
		if(isdigit(c) != 0)
		{
			int_tk(buffer, i);
			i--;
		}
		if(c == '\\')
		{
			comment_tk(buffer, i);
			i--;
		}
		if(c == EOF)
		{
			Token token;

                	token.id = EOF_tk;
                	token.instance = "EOF";
                	token.lineNumber = lineNumber;

                	tokens.push_back(token);
		}
		if(c == '\n')
		{
			lineNumber++;
		}
		/*if(isupper(c) == 0)
                {
                        cout << "Was expecting an uppercase letter but received a lowercase letter." << endl;                
                }*/
		if (isspace(c))
		{

		}
		/*else 
		{
			cout << "Character not allowed" << endl;
		}*/
	}

	return tokens;
}

//Function that recognizes identifier tokens.
void id_tk(string &buffer, int &i)
{
	char c;
	int start = i;
	string word;
	bool keyword;

	for(i = start; i < buffer.length(); i++)
	{
		c = buffer[i];

		if(isspace(c) != 0)
		{
			break;
		}
		else
		{
			word.append(1, c);
		}
	}
		
	//Checks if work is a keyword.
	keyword = isKeyword(word);
	if(keyword == true)
	{
		if(word == "Begin")
		{
			Token token;

			token.id = BEGIN_tk;
			token.instance = word;
			token.lineNumber = lineNumber;

			tokens.push_back(token);
		}
		if(word == "End")
                {
                        Token token;

                        token.id = END_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "Loop")
                {
                        Token token;

                        token.id = LOOP_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "Void")
                {
                        Token token;

                        token.id = VOID_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "INT")
                {
                        Token token;

                        token.id = INT_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "Return")
                {
                        Token token;

                        token.id = RETURN_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "Read")
                {
                        Token token;

                        token.id = READ_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "Output")
                {
                        Token token;

                        token.id = OUTPUT_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "Program")
                {
                        Token token;

                        token.id = PROGRAM_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "IFF")
                {
                        Token token;

                        token.id = IFF_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "Then")
                {
                        Token token;

                        token.id = THEN_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "Let")
                {
                        Token token;

                        token.id = LET_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
	}
	if(keyword == false)
	{	
		Token token;

		token.id = IDENT_tk;
		token.instance = word;
		token.lineNumber = lineNumber;

		tokens.push_back(token);
	}
}

//Function to recognize integer tokens.
void int_tk(string &buffer, int &i)
{
	char c;
        int start = i, j;
	string word;
	bool integer;

        for(i = start; i < buffer.length(); i++)
        {
                c = buffer[i];

                if(isspace(c) != 0)
                {
                        break;
                }
                else
                {
                        word.append(1, c);
                }
        }
	
	//Checks that string contains only numbers.
	integer = isNumber(word);
	if(integer == true)
        {       
                Token token;

                token.id = NUM_tk;
                token.instance = word;
                token.lineNumber = lineNumber;

                tokens.push_back(token);
        }
	if(integer == false)
        {       
		//TODO: what to do if not int token
	}
}

//Function that recognizes operstors.
void operator_tk(string &buffer, int &i)
{
	char c;
        int start = i, j;
        string word;
        int num;
        bool operators;

	word += buffer[i];
	//Checks the operators for appropriate tokens.
        if(word == "=")
      	{
        	Token token;

               	token.id = EQUAL_tk;
                token.instance = word;
                token.lineNumber = lineNumber;

                tokens.push_back(token);
        }
	if(word == "<")
        {
                Token token;

                        token.id = LESS_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == ">")
                {
                        Token token;

                        token.id = GREATER_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == ":")
                {
                        Token token;

                        token.id = COLON_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "+")
                {
                        Token token;

                        token.id = ADDITION_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "-")
                {
                        Token token;

                        token.id = SUBTRACTION_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "*")
                {
                        Token token;

                        token.id = MULTIPLY_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "/")
                {
                        Token token;

                        token.id = DIVIDE_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "%")
                {
                        Token token;

                        token.id = PERCENT_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == ".")
                {
                        Token token;

                        token.id = PERIOD_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "(")
                {
                        Token token;

                        token.id = OPEN_PAREN_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == ")")
                {
                        Token token;

                        token.id = CLOSE_PAREN_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == ",")
                {
                        Token token;

                        token.id = COMMA_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "{")
                {
                        Token token;

                        token.id = OPEN_CURLY_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "}")
                {
                        Token token;

                        token.id = CLOSE_CURLY_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == ";")
                {
                        Token token;

                        token.id = SEMI_COLON_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "[")
                {
                        Token token;

                        token.id = OPEN_BRACKET_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }
		if(word == "]")
                {
                        Token token;

                        token.id = CLOSE_BRACKET_tk;
                        token.instance = word;
                        token.lineNumber = lineNumber;

                        tokens.push_back(token);
                }

}

//Function that recognizes comments.
void comment_tk(string &buffer, int &i)
{
	char c;
        int start = i;
        string word;
	bool comment;

        for(i = start; i < buffer.length(); i++)
        {
                c = buffer[i];

                if(c == '\n' || c == EOF)
                {
                        return;
                }
                /*else
                {
                        word.append(1, c);
                }*/
        }

	//Checking that the comment is valid.
	/*comment = isComment(word);
	if(comment == true)
	{
		Token token;

		token.id = CMNT_tk;
		token.instance = word;
		token.lineNumber = lineNumber;

		tokens.push_back(token);
	}
	if(comment == false)
	{
		//TODO: if comment comes back false
	}*/
}

//Function that checks if identifier is a keyword.
bool isKeyword(string str)
{
	if((str != "Begin") && (str != "End") 
	   && (str != "Loop") && (str != "Void")
	   && (str != "INT") && (str != "Return")
	   && (str != "Read") && (str != "Output")
	   && (str != "Program") && (str != "IFF")
	   && (str != "Then") && (str != "Let"))
	   return(false);
	return(true);
}

//Function that checks that all numbers are in string.
bool isNumber(string str)
{
	for (size_t n = 0; n < str.length(); n++)
  	{
  		if (!isdigit(str[n]))
    		{	
    			return false;
    		}
		else
		{
			return true;
		}
  	}
}

//Function that checks operators.
bool isOperator(string str)
{
        if((str != "=") && (str != "<")
           && (str != ">") && (str != ":")
           && (str != "+") && (str != "-")
           && (str != "*") && (str != "/")
           && (str != "%") && (str != ".")
           && (str != "(") && (str != ")")
	   && (str != ",") && (str != "{")
           && (str != "}") && (str != ";")
	   && (str != "[") && (str != "]"))
           return(false);
        return(true);
}

//Function that validates comments.
bool isComment(string str)
{
	int length = str.length();

	if(str[0] != '\\' && str[length - 1] != '\n')
	{
		return(false);
	}
	return(true);
}

